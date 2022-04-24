/**********************************************
*FileName: briupZigbee.h
*Description: 
					Zigbee Usart2 ��ʼ���Ľӿ�
					ͨ��DMA�������ݵĺ����ӿ�
					ͨ��Usart2�жϽ�������
*Author: xb
*CreateDate: 2018-7-15
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
**********************************************/

#ifndef __ZIGBEE_H__
#define __ZIGBEE_H__

#include <stm32f10x.h>

//Zigbee���ڳ�ʼ��
void zigbeeInit(u8 pclk, u32 baud);

//ͨ��DMA����һ��Buf����
void zigbeeSendBuf(u8* buf, u16 len);

//��ȡZigbee����
u16 zigbeeGetData(u8* buf, u8 flag);
#endif
