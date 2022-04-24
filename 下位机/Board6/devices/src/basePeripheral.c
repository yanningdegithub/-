/**********************************************
*FileName: basePeripheral.c
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

#include "basePeripheral.h"

//����LED�ƵĲ����ӿ�
void baseLedSet(u8 led) {
	if( led > 7)
		return;
	switch(led) {
		case LED_BLACK:
			GPIOA -> ODR |= (1 << 8 | 1 << 11 | 1 << 12);
			break;
		case LED_RED:
			GPIOA -> ODR |= (1 << 11 | 1 << 12);
			GPIOA -> ODR &= ~(1 << 8);
			break;
		case LED_GREEN:
			GPIOA -> ODR |= (1 << 8 | 1 << 12);
			GPIOA -> ODR &= ~(1 << 11);
			break;
		case LED_BLUE:
			GPIOA -> ODR |= (1 << 8 | 1 << 11);
			GPIOA -> ODR &= ~(1 << 12);
			break;
		case LED_YELLOW:
			GPIOA -> ODR |= (1 << 12);
			GPIOA -> ODR &= ~(1 << 8 | 1 << 11);
			break;
		case LED_PURPLE:
			GPIOA -> ODR |= (1 << 11);
			GPIOA -> ODR &= ~(1 << 8 | 1 << 12);
			break;
		case LED_CYAN:
			GPIOA -> ODR |= (1 << 8);
			GPIOA -> ODR &= ~(1 << 11 | 1 << 12);
			break;
		case LED_WHITE:
			GPIOA -> ODR &= ~(1 << 8 | 1 << 11 | 1 << 12);
			break;
	}
}

//����BEEP�Ĳ����ӿ�
void baseBeepSet(u8 set) {
	if (set != 0)
		GPIOA -> ODR |= 1 << 15;
	else
		GPIOA -> ODR &= ~(1 << 15);
}
