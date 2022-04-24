/**********************************************
*FileName: miniFan.c
*Description: �������IO�ĳ�ʼ���ӿ�ʵ��
*Author: xb
*CreateDate: 2018-7-14
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
**********************************************/

#include "miniFan.h"

void miniFanInit(void) {
	RCC -> APB2ENR |= 1 << 2;
	GPIOA->CRL &= ~(0x0f000000);
	GPIOA->CRL |= 0x03000000;
	GPIOA->ODR &= ~(1<<6);
	
}

//���������ӿ�
void setMiniFan(u8 set) {
	if(set) {
		GPIOA->ODR |= 1<<6;
	} else {
		GPIOA->ODR &= ~(1<<6);
	}
}
