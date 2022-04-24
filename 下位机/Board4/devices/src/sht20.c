/********************
* FileName: 	sht20.c
* Description: 	
			��ʪ�ȼ�⺯��ʵ���ļ�
* Author:		Dennis Chen
* CreateDate:	2018-7-9
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-9	����	��ӳ�ʼ���ӿ�����
*********************/
#include "briupI2C.h"
#include "sht20.h"

#define SHT20_ADDR	0X80	//������ַ
#define SHT20_RT		0XF3	//���¶�
#define SHT20_RH		0XF5	//��ʪ��
/*******************************
��������SHT20_Measure
�������ܣ���ȡ��ʪ������
��������ֵ���ɹ�����0
*******************************/
unsigned char SHT20_Measure(float* Temperature, float* Humidity)
{
	unsigned char temp[2]={0};
	u16 ST=0;
	if(!Single_Read_Len(SHT20_ADDR,SHT20_RT,2,temp))
	{
		ST = (temp[0]<<8)|temp[1];
		ST&=~0X0003;
		*Temperature = ((float)ST * 0.00268127)-46.85;
	}
	else
	{
		*Temperature = 0;
		return 1;
	}
/******************��ȡʪ��***************/
	if(!Single_Read_Len(SHT20_ADDR,SHT20_RH,2,temp))
	{
		ST = (temp[0]<<8)|temp[1];
		ST&=~0X0003;
		*Humidity = ((float)ST * 0.00190735)-6;
	}
	else
	{
		*Humidity = 0;
		return 1;
	}
	return 0;
}
/*******************************
��������SHT20_Original_TEMP
�������ܣ���ȡԭʼ�¶�����
��������ֵ���ɹ�����0
*******************************/
unsigned char SHT20_Original_TEMP(u16* Temperature)
{
	unsigned char temp[2]={0};

	if(!Single_Read_Len(SHT20_ADDR,SHT20_RT,2,temp))
	{
		*Temperature = (temp[0]<<8)|temp[1];
		*Temperature&=~0X0003;
	}
	else
	{
		*Temperature = 0;
		return 1;
	}
	return 0;
}
/*******************************
��������SHT20_Original_HUM
�������ܣ���ȡԭʼʪ������
��������ֵ���ɹ�����0
*******************************/
unsigned char SHT20_Original_HUM(u16* Humidity)
{
	unsigned char temp[2]={0};

/******************��ȡʪ��***************/
	if(!Single_Read_Len(SHT20_ADDR,SHT20_RH,2,temp))
	{
		*Humidity = (temp[0]<<8)|temp[1];
		*Humidity&=~0X0003;
	}
	else
	{
		*Humidity = 0;
		return 1;
	}
	return 0;
}

