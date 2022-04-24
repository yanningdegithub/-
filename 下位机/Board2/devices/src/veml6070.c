/********************
* FileName: 	veml6070.c
* Description: 	
			������ǿ�ȼ�⺯�������ļ�
* Author:		Dennis Chen
* CreateDate:	2018-7-9
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-9	����	��ӳ�ʼ���ӿ�����
*********************/
#include "veml6070.h"
#include "briupI2C.h"


#define VEML6070_ADDR	0X70	//������ַ
#define VEML6070_DH		0X73	//���¶�
#define VEML6070_DL		0X71	//��ʪ��
/*******************************
��������VEML6070_Set
�������ܣ���ʼ�������ߴ�����
��������ֵ���ɹ�����0
*******************************/
unsigned char VEML6070Init(void)
{
	IIC_Start();
  IIC_Send_Byte(0X70);
  if (IIC_Wait_Ack()) 
		{
      IIC_Stop();
      return 1;
		}
	IIC_Send_Byte(0X0E);//�˴�ģʽ���ã��ر�ACK���� IT����Ϊ4T
	if (IIC_Wait_Ack()) 
		{
      IIC_Stop();
      return 1;
		}
	IIC_Stop();
	return  0;
}
/*******************************
��������VEML6070_Measure
�������ܣ���ȡ������ǿ��
��������ֵ���ɹ�����0
*******************************/
unsigned char VEML6070Measure(u16* Result)
{
	u8 tempH,tempL;
	/*********��ȡ��8λ����*********/
	IIC_Start();
  IIC_Send_Byte(0X73);
  if (IIC_Wait_Ack()) 
		{
      IIC_Stop();
      return 1;
		}
	tempH=IIC_Read_Byte(1);//��ȡ��������
	IIC_Stop();
	/*********��ȡ��8λ����*********/
	IIC_Start();
  IIC_Send_Byte(0X71);
  if (IIC_Wait_Ack()) 
		{
      IIC_Stop();
      return 1;
		}
	tempL=IIC_Read_Byte(1);//��ȡ��������
	IIC_Stop();
	*Result = (tempH<<8)|tempL;
	return 0;
}


