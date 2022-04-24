/**********************************************
*FileName: basePeripheral.c
*Description: 
           三色LED灯的颜色宏定义
					 LED灯操作接口
					 蜂鸣器操作接口声明
*Author: xb
*CreateDate: 2018-7-11
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
*2018-7-11  xb     添加初始化函数声明
**********************************************/

#include "basePeripheral.h"

//声明LED灯的操作接口
void baseLedSet(u8 led) {
	if( led > 7)
		return;
	switch(led) {
		case LED_BLACK:
			GPIOA -> ODR |= (1 << 8 | 1 << 11 | 1 << 12);
			break;
		case LED_RED:
			GPIOA -> ODR |= (1 << 11 | 1 << 12);
			GPIOA -> ODR &= ~(1 << 8);
			break;
		case LED_GREEN:
			GPIOA -> ODR |= (1 << 8 | 1 << 12);
			GPIOA -> ODR &= ~(1 << 11);
			break;
		case LED_BLUE:
			GPIOA -> ODR |= (1 << 8 | 1 << 11);
			GPIOA -> ODR &= ~(1 << 12);
			break;
		case LED_YELLOW:
			GPIOA -> ODR |= (1 << 12);
			GPIOA -> ODR &= ~(1 << 8 | 1 << 11);
			break;
		case LED_PURPLE:
			GPIOA -> ODR |= (1 << 11);
			GPIOA -> ODR &= ~(1 << 8 | 1 << 12);
			break;
		case LED_CYAN:
			GPIOA -> ODR |= (1 << 8);
			GPIOA -> ODR &= ~(1 << 11 | 1 << 12);
			break;
		case LED_WHITE:
			GPIOA -> ODR &= ~(1 << 8 | 1 << 11 | 1 << 12);
			break;
	}
}

//声明BEEP的操作接口
void baseBeepSet(u8 set) {
	if (set != 0)
		GPIOA -> ODR |= 1 << 15;
	else
		GPIOA -> ODR &= ~(1 << 15);
}
