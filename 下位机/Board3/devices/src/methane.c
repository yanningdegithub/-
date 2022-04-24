/**********************************************
*FileName: methane.c
*Description: 甲烷传感器函数接口实现
*Author: xb
*CreateDate: 2018-7-14
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
**********************************************/

#include "methane.h"
#include "briupDelay.h"
#include "briupUsart.h"
#include "protocol.h"

void methaneInit(void) {
	NVIC_InitTypeDef nvicInit;
	
	RCC->APB2ENR |= 1<<3;
	RCC->APB2ENR |= 1<<0;

	GPIOB->CRL &= ~0x000000f0;
	GPIOB->CRL |= 0x00000080;
	GPIOB->ODR |= 1<<1;
	
	AFIO->EXTICR[0] |= 0x0010;
	
	//下降沿触发-_-
	EXTI->RTSR &= ~(1<<1);
	EXTI->FTSR |= 1<<1;
	
	EXTI->IMR |= 1<<1;
	
	nvicInit.NVIC_IRQChannel = EXTI1_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 2;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
	
}

u8 methaneStat(void) {
	if(GPIOB->IDR & (1<<1))
		return 1;
	else
		return 0;
}

//=================IRQ Handler===================//
void EXTI1_IRQHandler(void) {
		u8 buf = 0x01, jw[2] = {0xD6, 0x03};
	_delay_ms(10);
	//响应并清除中断标志位
	if( !(GPIOB->IDR & (1<<1)) ) {
		EXTI->PR |= 1<<1;
	//putStr("Methane\r\n");
		protocolSend(0x05, 0x01, 0x01, &buf);
		protocolSend(0x07, 0x03, 0x01, &buf);
		_delay_ms(500);
		protocolSendToRaspi(0x02, 0x06, 0x02, jw);
		_delay_ms(500);
	}
}
