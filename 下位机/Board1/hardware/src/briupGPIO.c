/**********************************************
*FileName: briupGPIO.c
*Description: 基础IO的初始化接口实现
*Author: xb
*CreateDate: 2018-7-11
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
*2018-7-11  xb     添加初始化函数声明
**********************************************/

#include "briupGPIO.h"

//初始化GPIO引脚的函数接口
void briupGPIOInit(void) {
	//三色LED         蜂鸣器BEEP
	//PA8 PA11 PA12   PA15
	
	//开启外设GPIOA、AFIO的时钟
	RCC -> APB2ENR |= 1 << 2 | 1 << 0;
	
	//修改PA15的复用功能，使PA15作为通用功能
	AFIO -> MAPR |= 0x02 << 24;
	
	//将四个引脚配置为通用推挽输出50MHz
	GPIOA -> CRH &= 0x0FF00FF0;
	GPIOA -> CRH |= 0x30033003;
	
	//默认关闭
	//Beep 0
	GPIOA -> ODR &= ~(1 << 15);
	//RGB LED 1
	GPIOA -> ODR |= (1 << 8 | 1 << 11 | 1 << 12);
}
