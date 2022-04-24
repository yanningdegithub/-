/*******************************************************
�����ͺţ�12V�����
ͨ�ŷ�ʽ��IO���� �뵥Ƭ����PB9����������
�ļ����ܣ�
*******************************************************/

#include "lock.h"
#include "briupDelay.h"

void Lock_Init() {
	RCC->APB2ENR |= 1<<3;//ʹ��GPIOBʱ��
	GPIOB->CRH &= 0XFFFFFF0F;
	GPIOB->CRH |= 0X00000030;
}

void Lock_Open_Once() {
	GPIOB->ODR |=1<<9;
	_delay_sec(1.5);
	GPIOB->ODR &= ~(1<<9);
}
