/********************
* FileName: 	briupTim.h
* Description: 	��ʱ����ʼ���ӿ�����
* Author:		Dennis Chen
* CreateDate:	2018-7-6
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-6	����	��ӳ�ʼ���ӿ�����
*********************/

#ifndef __TIM_H__
#define __TIM_H__

#include <stm32f10x.h>

//��ʱ����ʼ�������ӿ�
// pclk Ƶ��	arr �Զ�װ��ֵ
void timInit(u8 pclk, u16 arr);

#endif
