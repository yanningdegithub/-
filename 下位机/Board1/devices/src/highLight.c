/********************
* FileName: 	highLight.c
* Description: 	��������LED�Ƶĺ����ӿ�
* Author:		Dennis Chen
* CreateDate:	2018-7-6
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-6	����
*********************/

#include "highLight.h"
//����LED��������
//	row ָ����		ratio ���Ȱٷֱ�
void lightSet( u8 row, u8 ratio)
{
	row &= 0x0f;
	ratio = ratio > 100 ? 100:ratio;
	if( row & ROW_1)
		TIM3->CCR1 = ratio * 10;
	
	if( row & ROW_2)
		TIM4->CCR1 = ratio * 10;
	
	if( row & ROW_3)
		TIM3->CCR3 = ratio * 10;
	
	if( row & ROW_4)
		TIM3->CCR4 = ratio * 10;
}


