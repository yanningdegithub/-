/**********************************************
*FileName: basePeripheral.h
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

#ifndef __BASEPERIPH_H__
#define __BASEPERIPH_H__

#include <stm32f10x.h>

//R 8 G 11 B 12
#define LED_RED     1
#define LED_GREEN   2
#define LED_BLUE    3
#define LED_YELLOW  4
#define LED_PURPLE  5
#define LED_CYAN    6
#define LED_WHITE   7
#define LED_BLACK   0

//声明LED灯的操作接口
void baseLedSet(u8 led);
//声明BEEP的操作接口
void baseBeepSet(u8 set);

#endif
