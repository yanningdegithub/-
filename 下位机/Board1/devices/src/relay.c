/**********************************************
*FileName: relay.c
*Description: �̵���IO�ĳ�ʼ���ӿ�ʵ��
*Author: xb
*CreateDate: 2018-7-14
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
**********************************************/

#include "relay.h"

//��ʼ��GPIO���ŵĺ����ӿ�
void relayInit(void) {
	//PA4 ��߼̵���  PA5 �ұ߼̵���
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRL &= ~(0x00ff0000);
	GPIOA->CRL |= 0x00330000;
	GPIOA->ODR &= ~(1<<4 | 1<<5);
}

//���������ӿ�
void setLeftRelay(u8 set) {
	if (set) {
		GPIOA->ODR |= 1<<4;
	} else {
		GPIOA->ODR &= ~(1<<4);
	}
}

void setRightRelay(u8 set) {
	if (set) {
		GPIOA->ODR |= 1<<5;
	} else {
		GPIOA->ODR &= ~(1<<5);
	}
}
