/********************
* FileName: 	alarm.c
* Description: 	报警灯和报警器函数接口实现
* Author:		xb
* CreateDate:	2018-7-16
* Copyright:	6014109852qq.com
* Update:	更改日期  更改人  更改内容
*********************/

#include "alarm.h"
#include "briupDelay.h"

//beep pb8 led pb9
void alarmInit(void) {
	RCC->APB2ENR |= 1<<3;
	GPIOB->CRH &= ~(0x000000ff);
	GPIOB->CRH |= 0x00000033;

	GPIOB->ODR &= ~(1<<8 | 1<<9);
}

void alarmSet(u8 led, u8 beep) {
	if(led == 1) {
		GPIOB->ODR |= 1<<9;
	} else {
		GPIOB->ODR &= ~(1<<9);
	}
	
	if(beep == 1) {
		GPIOB->ODR |= 1<<8;
	} else {
		GPIOB->ODR &= ~(1<<8);
	}
}

void alarmAction() {
	alarmSet(1, 1);
	_delay_ms(10);
	alarmSet(0, 0);
	_delay_ms(500);
	
	alarmSet(1, 1);
	_delay_ms(10);
	alarmSet(0, 0);
	_delay_ms(500);
	
	alarmSet(1, 1);
	_delay_ms(10);
	alarmSet(0, 0);
	_delay_ms(500);
}
