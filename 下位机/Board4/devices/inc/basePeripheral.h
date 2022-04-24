/**********************************************
*FileName: basePeripheral.h
*Description: 
           ��ɫLED�Ƶ���ɫ�궨��
					 LED�Ʋ����ӿ�
					 �����������ӿ�����
*Author: xb
*CreateDate: 2018-7-11
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
*2018-7-11  xb     ��ӳ�ʼ����������
**********************************************/

#ifndef __BASEPERIPH_H__
#define __BASEPERIPH_H__

#include <stm32f10x.h>

//R 8 G 11 B 12
#define LED_RED     1
#define LED_GREEN   2
#define LED_BLUE    3
#define LED_YELLOW  4
#define LED_PURPLE  5
#define LED_CYAN    6
#define LED_WHITE   7
#define LED_BLACK   0

//����LED�ƵĲ����ӿ�
void baseLedSet(u8 led);
//����BEEP�Ĳ����ӿ�
void baseBeepSet(u8 set);

#endif
