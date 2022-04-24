/********************
* FileName: 	alarm.h
* Description: 	报警灯和报警器函数接口实现
* Author:		xb
* CreateDate:	2018-7-16
* Copyright:	6014109852qq.com
* Update:	更改日期  更改人  更改内容
*********************/

#ifndef __ALARM_H__
#define __ALARM_H__

#include <stm32f10x.h>

void alarmInit(void);

void alarmSet(u8 led, u8 beep);

void alarmAction(void);

#endif
