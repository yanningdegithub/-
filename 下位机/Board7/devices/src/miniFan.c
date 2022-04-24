/**********************************************
*FileName: miniFan.c
*Description: 迷你风扇IO的初始化接口实现
*Author: xb
*CreateDate: 2018-7-14
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
**********************************************/

#include "miniFan.h"

void miniFanInit(void) {
	RCC -> APB2ENR |= 1 << 2;
	GPIOA->CRL &= ~(0x0f000000);
	GPIOA->CRL |= 0x03000000;
	GPIOA->ODR &= ~(1<<6);
	
}

//操作函数接口
void setMiniFan(u8 set) {
	if(set) {
		GPIOA->ODR |= 1<<6;
	} else {
		GPIOA->ODR &= ~(1<<6);
	}
}
