/**********************************************
*FileName: briupZigbee.c
*Description: 
					Zigbee Usart2 ��ʼ���Ľӿ�
					ͨ��DMA�������ݵĺ����ӿ�
					ͨ��Usart2�жϽ�������
*Author: xb
*CreateDate: 2018-7-15
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
**********************************************/

#include "briupZigbee.h"

//ѭ������
static volatile u8 zbBuffer[256];
static volatile u16 zbHead, zbTail;
static volatile u16 zbCount;

//Zigbee���ڳ�ʼ��
void zigbeeInit(u8 pclk, u32 baud) {
	
	NVIC_InitTypeDef nvicInit;
	
	double div = (pclk * 1000000) / (16 * baud);
	u16 mant = (u16)div;
	u16 frac = (div - mant) * 16;
	mant = mant << 4 | (frac & 0x0f);
	
	//1 RCC -> ����GPIOA����ʱ��
	RCC->APB2ENR |= 1<<2;
	RCC->APB1ENR |= 1<<17; //U2ʱ��
	RCC->AHBENR |= 1<<0; // DMAʱ��ʹ��

	//2 ����PA2 TX PA3 RX ���Ź���ģʽ
	GPIOA->CRL &= ~(0x0000ff00);
	GPIOA->CRL |= 0x00008B00;
	GPIOA->ODR |= 1<<3;
	
	//3 ����Usart2
	// ���ô��ڲ�����
	USART2->BRR = mant;
	//����U2���ա����͡����ڡ������жϡ�DMA����ʹ��
	USART2->CR1 |= 1<<13 | 1<<5 | 1<<3 | 1<<2;
	USART2->CR3 |= 1<<7;
	
	//��ʼ��DMA U2.Tx -> DMA1 Channel 7
	DMA1_Channel7->CCR = 0;
	DMA1_Channel7->CPAR = (u32) &USART2->DR;
	DMA1_Channel7->CMAR = 0;
	DMA1_Channel7->CNDTR = 0;
	// 1<<13 ���ȼ�
	DMA1_Channel7->CCR |= 1<<13 | 1<<7 | 1<<4;
	
	nvicInit.NVIC_IRQChannel = USART2_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 2;
	nvicInit.NVIC_IRQChannelSubPriority = 3;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
	
}

//ͨ��DMA����һ��Buf����
void zigbeeSendBuf(u8* buf, u16 len){
	
	//�ر�DMA��USART1ͨ��
	DMA1_Channel7->CCR &= ~0x01;
	
	DMA1_Channel7->CMAR = (u32) buf;
	DMA1_Channel7->CNDTR = len;
	DMA1_Channel7->CCR |= 0x01;
	
}
//��ȡZigbee����
u16 zigbeeGetData(u8* buf, u8 flag) {
	u16 temp = zbCount, i, ck;
	if(zbCount == 0)
		return 0;
	if (!flag) {
		zbCount = 0; // ��գ�����һ������
		for (i = 0; i < temp; i++) {
			*buf = zbBuffer[zbHead];
			buf ++;
			zbHead ++;
			zbHead %= 256;
		}
		return temp;
	}
	else {
		ck = 0;
		for(i = zbHead; ; i++){
			
			i %= 256;
			
			//�յ�����ff
			if (zbBuffer[i] == 0xee && zbBuffer[i + 1] == 0xff) {
				ck = 1;
				break;
			}
			if(i == zbTail) { // over 256
				break;
			}
			
		}
		if(ck == 0)
			return 0;
		
		//��ֹ�м���룿������
		temp = zbCount;
		zbCount = 0;
		
		for(i = 0; i < temp; i ++) {
			*buf = zbBuffer[zbHead];
			buf ++;
			zbHead ++;
			zbHead %= 256;
		}
		return temp;
	}
	return 0;
}


//==============================IRQHandler
void USART2_IRQHandler(void) {
	if(USART2->SR & (1<<5)) {
		zbBuffer[zbTail] = USART2->DR;
		zbTail ++;
		zbTail %= 256;
		zbCount ++;
		
	}
}
