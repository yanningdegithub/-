/*******************************************************
器件型号：---------
通信方式：串口
文件功能：获取二氧化碳浓度数据
获取二氧化碳数据（被动式）数据帧：
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
	//发送获取数据指令
	usart3PutDataDma(CO2_R_COM, 7);
	do {
		len = usart3GetBuffer(buf);
		_delay_ms(10);
	} while(len == 0);
	*CO2_Value_H = buf[4];
	*CO2_Value_L = buf[5];
}
