/********************
* FileName: 	sht20.h
* Description: 	
			��ʪ�ȼ�⺯�������ļ�
* Author:		Dennis Chen
* CreateDate:	2018-7-9
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-9	����	��ӳ�ʼ���ӿ�����
*********************/
#ifndef __SHT20_H__
#define __SHT20_H__

#include <stm32f10x.h>

/*******************************
��������SHT20_Measure
�������ܣ���ȡ��ʪ������
��������ֵ���ɹ�����0
*******************************/
unsigned char SHT20_Measure(float* Temperature, float* Humidity);
/*******************************
��������SHT20_Original_TEMP
�������ܣ���ȡԭʼ�¶�����
��������ֵ���ɹ�����0
*******************************/
unsigned char SHT20_Original_TEMP(u16* Temperature);
/*******************************
��������SHT20_Original_HUM
�������ܣ���ȡԭʼʪ������
��������ֵ���ɹ�����0
*******************************/
unsigned char SHT20_Original_HUM(u16* Humidity);


#endif
