/**********************************************
*FileName: infrared.c
*Description: ���⴫������ʼ���ӿ�
*Author: xb
*CreateDate: 2018-7-14
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
*2018-7-11  xb     ��ӳ�ʼ����������
**********************************************/

#include "infrared.h"
#include "briupDelay.h"
#include "briupUsart.h"

void infraredInit(void) {
	NVIC_InitTypeDef nvicInit;
	
	RCC->APB2ENR |= 1<<4; // PBʱ��
	RCC->APB2ENR |= 1<<0; // AFIOʱ��
	
	GPIOC->CRH &= ~0x00f00000;
	GPIOC->CRH |= 0x00800000;
	
	//�������룬ODR��Ӧλ��0
	GPIOC->ODR &= ~(1<<13);
	
	AFIO->EXTICR[3] |= 0x0020;
	
	//�����ش���_-_
	EXTI->RTSR |= 1<<13;
	EXTI->FTSR &= ~(1<<13);
	
	EXTI->IMR |= 1<<13;
	
	nvicInit.NVIC_IRQChannel = EXTI15_10_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 1;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
}

u8 infraredStat(void) {
	if(GPIOC->IDR & (1<<13))
		return 1;
	else
		return 0;
}


//=================IRQ Handler===================//
void EXTI15_10_IRQHandler(void) {
	_delay_ms(10);
	//��Ӧ������жϱ�־λ
	if( GPIOC->IDR & (1<<13) ) {
		EXTI->PR |= 1<<13;
//	putStr("Infrared\r\n");
	}
}

