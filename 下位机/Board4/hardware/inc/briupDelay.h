/**********************************************
*FileName: briupDelay.h
*Description: 
						ͨ��SysTick��ʱ��ʵ����ʱ����
						������ʱ�ĳ�ʼ�������ӿ�
						��us��ʱ����ms��ʱ����sec��ʱ
*Author: xb
*CreateDate: 2018-7-12
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
**********************************************/

#ifndef __DELAY_H__
#define __DELAY_H__

#include <stm32f10x.h>

//��ʱ�����ĳ�ʼ���ӿ�
//Input��pclk -> оƬ����ʱ��
void _delay_init(u8 pclk);

//��ʱ����
void _delay_us(u32 us);
void _delay_ms(u32 ms);
void _delay_sec(double sec);

#endif
