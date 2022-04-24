/**********************************************
*FileName: relay.c
*Description: 继电器IO的初始化接口实现
*Author: xb
*CreateDate: 2018-7-14
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
**********************************************/

#include "relay.h"

//初始化GPIO引脚的函数接口
void relayInit(void) {
	//PA4 左边继电器  PA5 右边继电器
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRL &= ~(0x00ff0000);
	GPIOA->CRL |= 0x00330000;
	GPIOA->ODR &= ~(1<<4 | 1<<5);
}

//操作函数接口
void setLeftRelay(u8 set) {
	if (set) {
		GPIOA->ODR |= 1<<4;
	} else {
		GPIOA->ODR &= ~(1<<4);
	}
}

void setRightRelay(u8 set) {
	if (set) {
		GPIOA->ODR |= 1<<5;
	} else {
		GPIOA->ODR &= ~(1<<5);
	}
}
