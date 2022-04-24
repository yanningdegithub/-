/**********************************************
*FileName: briupUsart.c
*Description: 
						��ʼ��Debug���� -> usart1�ĺ����ӿ�
						�������ڷ������ݣ�char / str / buffer
						�������ڽ������ݣ�char / str
*Author: xb
*CreateDate: 2018-7-12
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
*20180713   xb     ���ϴ��ڽ����жϡ�ѭ�����С�����DMA����
**********************************************/

#include "briupUsart.h"

//�������ڽ��յ�ѭ�����л�����
static volatile u8 Usart1Buf[256];
//�������ס���β���
static volatile u16 u1Head, u1Tail;
//ͳ�����һ�ν��յ������ݳ���
static volatile u16 u1Count;


//��ʼ��usart1�ĺ����ӿ�
//plck������ʱ��
//baud��Ҫ���õĲ�����
void usart1Init(u8 pclk, u32 baud) {
	NVIC_InitTypeDef nvicInit;
	
	
	//���㲨���ʷ�Ƶ���ӵ�����������С������
	double temp = (pclk * 1000000.0 / (16 * baud));
	u16 mant, frac;
	mant = (u16) temp;
	frac = (temp - mant) * 16;
	//������ -> ���������ʷ�����
	mant = mant << 4 | (frac & 0x0f);
	
	//ʹ��USART1��ʱ��
	RCC->APB2ENR |= 1<<14 | 1<<2;
	
	//ʹ��DMA1��ʱ��
	RCC->AHBENR |= 1<<0;
	
	//PA9 -> TX ���츴����� PA10 -> ��������
	GPIOA->CRH &= ~(0x00000FF0);
	GPIOA->CRH |= 0x000008B0;
	GPIOA->ODR |= 1<<10;
	
	//���ô���
	USART1->BRR = mant;
	//ʹ�ܴ��ڷ��������
	USART1->CR1 |= 1<<3 | 1<<2;
	//ʹ�ܴ���
	USART1->CR1 |= 1<<13;
	
	//ʹ�ܴ��ڽ����ж�
	USART1->CR1 |= 1<<5;
	
	//ʹ�ܴ���DMA����
	USART1->CR3 |= 1<<7;
	
	//ʹ�ܴ���DMA����
	//USART1 Tx��Ӧ��DMAͨ��
	DMA1_Channel4->CPAR = (u32)&USART1->DR;
	DMA1_Channel4->CMAR = 0;
	DMA1_Channel4->CNDTR = 0;
	DMA1_Channel4->CCR = 0;
	DMA1_Channel4->CCR |= 1<<12 | 1<<7 | 1<<4;
	
	
	//ע���ж����ȼ����жϱ��
	nvicInit.NVIC_IRQChannel = USART1_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 3;
	nvicInit.NVIC_IRQChannelSubPriority = 3;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
	
}

//���ͺ�������
//����1Byte����
void putChar(u8 ch) {
	//��cache�ճ���
	while (!(USART1->SR & (1<<7)));
	USART1->DR = ch;
}
//����String���� ��\0��
void putStr(char * str) {
	while(*str != '\0') {
		putChar(*str);
		str++;
	}
}
//����һ������
void putBuffer(u8 * buf, u16 length) {
	u16 i;
	for(i = 0; i < length; i++) {
		putChar(*buf);
		buf++;
	}
}

//ͨ��DMA����һ������
void putDataDma(u8 * buf, u16 len) {
	
	//�ر�DMA��USART1ͨ��
	DMA1_Channel4->CCR &= ~0x01;
	
	DMA1_Channel4->CMAR = (u32) buf;
	DMA1_Channel4->CNDTR = len;
	DMA1_Channel4->CCR |= 0x01;
	
}

//���պ�������
u8 getChar(void) {
	while(!(USART1->SR & (1<<5)));
	return USART1->DR;
}

//���ؽ��յ������ݳ���
u8 getStr(char * str) {
	u8 len = 0;
	do {
		*str = getChar();
		str++;
		len++;
	} while (*(str - 1) != '\0');
	return len; // �����ַ����ĳ���
}

//ͨ��ѭ�����л�ȡһ������
//flag��
//    0    ֱ�ӻ�ȡ������յ�������
//    1    �жϻ�ȡ��������һ֡Э�������ٷ���
u16 getBuffer(u8 * buf, u8 flag) {
	u16 temp, i, ck;
	temp = u1Count;
	if(u1Count == 0)
		return 0;
	if (!flag) { // flag == 0
		u1Count = 0;
		for (i = 0; i < temp; i++) {
			*buf = Usart1Buf[u1Head];
			buf ++;
			u1Head ++;
			u1Head %= 256;
		}
		return temp;
	}
	else { // ��Э����ж�
		ck = 0;
		for(i = u1Head; ; i++){
			
			i %= 256;
			
			//�յ�����ff
			if (Usart1Buf[i] == 0xee && Usart1Buf[i + 1] == 0xff) {
				ck = 1;
				break;
			}
			if(i == u1Tail) {
				break;
			}
			
		}
		if(ck == 0)
			return 0;
		
		//��ֹ�м���룿������
		temp = u1Count;
		u1Count = 0;
		
		for(i = 0; i < temp; i ++) {
			*buf = Usart1Buf[u1Head];
			buf ++;
			u1Head ++;
			u1Head %= 256;
		}
		return temp;
	}
}

//===================�жϷ�����===================//
void USART1_IRQHandler(void) {
	//�ж��Ƿ���յ�����
	if(USART1->SR & (1<<5)) {
		Usart1Buf[u1Tail] = USART1->DR;
		u1Tail ++;
		u1Tail %= 256;
		u1Count ++;
		
	}
}
