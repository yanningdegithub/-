/**********************************************
*FileName: briupZigbee.h
*Description: 
					Zigbee Usart2 初始化的接口
					通过DMA发送数据的函数接口
					通过Usart2中断接收数据
*Author: xb
*CreateDate: 2018-7-15
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
**********************************************/

#ifndef __ZIGBEE_H__
#define __ZIGBEE_H__

#include <stm32f10x.h>

//Zigbee串口初始化
void zigbeeInit(u8 pclk, u32 baud);

//通过DMA发送一个Buf数组
void zigbeeSendBuf(u8* buf, u16 len);

//获取Zigbee数据
u16 zigbeeGetData(u8* buf, u8 flag);
#endif
