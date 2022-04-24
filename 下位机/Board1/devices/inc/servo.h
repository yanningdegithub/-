/********************
* FileName: 	servo.h
* Description: 	
			��ʼ�������Ӧ�Ķ�ʱ��
			����Ŀ����͹رպ����ӿ�����
* Author:		Dennis Chen
* CreateDate:	2018-7-10
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-10	����	��ӳ�ʼ���ӿ�����
*********************/
#ifndef __SERVO_H__
#define __SERVO_H__

#include <stm32f10x.h>

void Servo_Init(u16 arr, u16 psc);
//բ����
void Servo_ON(void);
//բ���ر�
void Servo_OFF(void);

#endif
