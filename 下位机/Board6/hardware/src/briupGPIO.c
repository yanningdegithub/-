/**********************************************
*FileName: briupGPIO.c
*Description: ����IO�ĳ�ʼ���ӿ�ʵ��
*Author: xb
*CreateDate: 2018-7-11
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
*2018-7-11  xb     ��ӳ�ʼ����������
**********************************************/

#include "briupGPIO.h"

//��ʼ��GPIO���ŵĺ����ӿ�
void briupGPIOInit(void) {
	//��ɫLED         ������BEEP
	//PA8 PA11 PA12   PA15
	
	//��������GPIOA��AFIO��ʱ��
	RCC -> APB2ENR |= 1 << 2 | 1 << 0;
	
	//�޸�PA15�ĸ��ù��ܣ�ʹPA15��Ϊͨ�ù���
	AFIO -> MAPR |= 0x02 << 24;
	
	//���ĸ���������Ϊͨ���������50MHzģʽ
	GPIOA -> CRH &= 0x0FF00FF0;
	GPIOA -> CRH |= 0x30033003;
	
	//Ĭ�Ϲر�LED�ͷ�����
	GPIOA -> ODR &= ~(1 << 15);
	GPIOA -> ODR |= (1 << 8 | 1 << 11 | 1 << 12);
	
}
