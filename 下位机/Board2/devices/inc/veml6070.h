/********************
* FileName: 	veml6070.h
* Description: 	
			������ǿ�ȼ�⺯�������ļ�
* Author:		Dennis Chen
* CreateDate:	2018-7-9
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-9	����	��ӳ�ʼ���ӿ�����
*********************/
#ifndef __VEML6070_H__
#define __VEML6070_H__

#include <stm32f10x.h>

/*******************************
��������VEML6070_Set
�������ܣ�	��ʼ��������ǿ�ȴ�����
��������ֵ���ɹ�����0
*******************************/
unsigned char VEML6070Init(void);

/*******************************
��������VEML6070_Measure
�������ܣ���ȡ������ǿ������
��������ֵ���ɹ�����0
*******************************/
unsigned char VEML6070Measure(u16* Result);

#endif
