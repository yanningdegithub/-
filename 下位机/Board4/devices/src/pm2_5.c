/********************
* FileName: 	pm2_5.c
* Description: 	PM2.5���ӿ�
* Author:		Dennis Chen
* CreateDate:	2018-7-10
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-10	����	��ӳ�ʼ���ӿ�����
*********************/
#include "pm2_5.h"
#include "briupUsart3.h"

//����ֵΪPM2.5��ֵ ug/m3
u16 pm25Value(void)
{
	u16 len, pm25 = 0;
	u8 buf[30];
	len = usart3GetBuffer( buf);
	if( len != 0)
		pm25 = buf[2] | (buf[3]<<8);
	return pm25;
}
