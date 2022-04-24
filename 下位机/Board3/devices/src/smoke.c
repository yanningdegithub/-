#include "smoke.h"
#include "briupDelay.h"
#include "briupUsart.h"

//PB6

void smokeInit(void) {
	NVIC_InitTypeDef nvicInit;
	
	RCC->APB2ENR |= 1<<3; // PB时钟
	RCC->APB2ENR |= 1<<0; // AFIO时钟
	
	GPIOB->CRL &= ~0x0f000000;
	GPIOB->CRL |= 0x08000000;
	
	//下拉输入，ODR相应位置0
	GPIOB->ODR &= ~(1<<6);
	
	AFIO->EXTICR[1] |= 0x0100;
	
	//上升沿触发_-_
	EXTI->RTSR |= 1<<6;
	EXTI->FTSR &= ~(1<<6);
	
	EXTI->IMR |= 1<<6;
	
	nvicInit.NVIC_IRQChannel = EXTI9_5_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 2;
	nvicInit.NVIC_IRQChannelSubPriority = 1;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
}

u8 smokeStat(void) {
	if(GPIOB->IDR & (1<<6))
		return 1;
	else
		return 0;
}


//=================IRQ Handler===================//
//void EXTI9_5_IRQHandler(void) {
//	_delay_ms(10);
//	//响应并清除中断标志位
//	if( GPIOB->IDR & (1<<6) ) {
//		EXTI->PR |= 1<<6;
//	putStr("Smoke\r\n");
//	}
//}
