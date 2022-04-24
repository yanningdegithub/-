/*******************************************************
�����ͺţ�---------
ͨ�ŷ�ʽ������
�ļ����ܣ���ȡ������̼Ũ������
��ȡ������̼���ݣ�����ʽ������֡��
	0X42 0X4D 0XE3 0X00 0X00 0X01 0X72
*******************************************************/
#include "CO2.h"
#include "briupUsart3.h"
#include "briupDelay.h"
#include "briupUsart.h"

u8 buf[15];
u8 CO2_R_COM[7]={0X42,0X4D,0XE3,0X00,0X00,0X01,0X72};
u16 len;

void CO2_Measure(u8* CO2_Value_H, u8* CO2_Value_L)
{
	//���ͻ�ȡ����ָ��
	usart3PutDataDma(CO2_R_COM, 7);
	do {
		len = usart3GetBuffer(buf);
		_delay_ms(10);
	} while(len == 0);
	*CO2_Value_H = buf[4];
	*CO2_Value_L = buf[5];
}
