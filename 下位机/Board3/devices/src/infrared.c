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
#include "protocol.h"

void infraredInit(void) {
	NVIC_InitTypeDef nvicInit;
	
	RCC->APB2ENR |= 1<<3; // PB时钟
	RCC->APB2ENR |= 1<<0; // AFIO时钟
	
	GPIOB->CRL &= ~0xf0000000;
	GPIOB->CRL |= 0x80000000;
	
	//下拉输入，ODR相应位置0
	GPIOB->ODR &= ~(1<<7);
	
	AFIO->EXTICR[1] |= 0x1000;
	
	//上升沿触发_-_
	EXTI->RTSR |= 1<<7;
	EXTI->FTSR &= ~(1<<7);
	
	EXTI->IMR |= 1<<7;
	
	nvicInit.NVIC_IRQChannel = EXTI9_5_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 1;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
}

u8 infraredStat(void) {
	if(GPIOB->IDR & (1<<7))
		return 1;
	else
		return 0;
}


//=================IRQ Handler===================//
void EXTI9_5_IRQHandler(void) {
	u8 buf = 0x01, yw[2] = {0xD6, 0x02}; //  hw[2] = {0xD6, 0x04},

	_delay_ms(10);

	//响应并清除中断标志位
	if( GPIOB->IDR & (1<<7) ) {
		EXTI->PR |= 1<<7;
		//putStr("Infrared\r\n");
//		protocolSendToBoard(0x01, 0x03, 0x01, &buf);
//		_delay_ms(500);
//		protocolSendToRaspi(0x03, 0x06, 0x02, hw);
//		_delay_ms(500);
	}
	else if( GPIOB->IDR & (1<<6) ) {
		EXTI->PR |= 1<<6;
		//putStr("Smoke\r\n");
		protocolSend(0x05, 0x01, 0x01, &buf);
		_delay_ms(500);
		protocolSendToRaspi(0x01, 0x06, 0x02, yw);
		_delay_ms(500);
	}
}

