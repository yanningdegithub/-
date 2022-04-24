/**********************************************
*FileName: infrared.c
*Description: 红外传感器初始化接口
*Author: xb
*CreateDate: 2018-7-14
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
*2018-7-11  xb     添加初始化函数声明
**********************************************/

#include "infrared.h"
#include "briupDelay.h"
#include "briupUsart.h"

void infraredInit(void) {
	NVIC_InitTypeDef nvicInit;
	
	RCC->APB2ENR |= 1<<4; // PB时钟
	RCC->APB2ENR |= 1<<0; // AFIO时钟
	
	GPIOC->CRH &= ~0x00f00000;
	GPIOC->CRH |= 0x00800000;
	
	//下拉输入，ODR相应位置0
	GPIOC->ODR &= ~(1<<13);
	
	AFIO->EXTICR[3] |= 0x0020;
	
	//上升沿触发_-_
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
	//响应并清除中断标志位
	if( GPIOC->IDR & (1<<13) ) {
		EXTI->PR |= 1<<13;
//	putStr("Infrared\r\n");
	}
}

