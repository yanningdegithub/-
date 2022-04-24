/********************
* FileName: 	highLight.h
* Description: 	��������LED�Ƶĺ����ӿ�����
* Author:		Dennis Chen
* CreateDate:	2018-7-6
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-6	����
*********************/

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <stm32f10x.h>

#define ROW_1	0x01
#define ROW_2	0x02
#define ROW_3	0x04
#define ROW_4	0x08
#define ROW_ALL 0x0F
//����LED��������
//	row ָ����		ratio ���Ȱٷֱ�
void lightSet( u8 row, u8 ratio);

#endif
