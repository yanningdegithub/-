#include "fire.h"
#include "briupDelay.h"
#include "briupUsart.h"
#include "protocol.h"

void fireInit(void) {
	NVIC_InitTypeDef nvicInit;
	
	RCC->APB2ENR |= 1<<3;
	RCC->APB2ENR |= 1<<0;

	GPIOB->CRL &= ~0x0000000f;
	GPIOB->CRL |= 0x00000008;
	GPIOB->ODR |= 1<<0;
	
	AFIO->EXTICR[0] |= 0x0001;
	
	//下降沿触发-_-
	EXTI->RTSR &= ~(1<<0);
	EXTI->FTSR |= 1<<0;
	
	EXTI->IMR |= 1<<0;
	
	nvicInit.NVIC_IRQChannel = EXTI0_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 2;
	nvicInit.NVIC_IRQChannelSubPriority = 2;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
}

u8 fireStat(void) {
	if(GPIOB->IDR & (1<<0))
		return 1;
	else
		return 0;
}

//=================IRQ Handler===================//
void EXTI0_IRQHandler(void) {
		u8 buf = 0x01, hg[2] = {0xD6, 0x05};
	_delay_ms(10);
	//响应并清除中断标志位
	if( !(GPIOB->IDR & (1<<0)) ) {
		EXTI->PR |= 1<<0;
	//putStr("Fire\r\n");
		protocolSend(0x05, 0x01, 0x01, &buf);
		_delay_ms(500);
		protocolSendToRaspi(0x04, 0x06, 0x02, hg);
		_delay_ms(500);
	}
}
