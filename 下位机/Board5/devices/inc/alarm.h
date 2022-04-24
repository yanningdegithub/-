/********************
* FileName: 	alarm.h
* Description: 	�����ƺͱ����������ӿ�ʵ��
* Author:		xb
* CreateDate:	2018-7-16
* Copyright:	6014109852qq.com
* Update:	��������  ������  ��������
*********************/

#ifndef __ALARM_H__
#define __ALARM_H__

#include <stm32f10x.h>

void alarmInit(void);

void alarmSet(u8 led, u8 beep);

void alarmAction(void);

#endif
