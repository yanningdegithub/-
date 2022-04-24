/********************
* FileName: 	briupTim.c
* Description: 	��ʱ����ʼ���ӿ�ʵ��
* Author:		Dennis Chen
* CreateDate:	2018-7-6
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-6	����	��ӳ�ʼ���ӿ�����
*********************/

#include "briupTim.h"


//��ʱ����ʼ�������ӿ�
// pclk ��Ƶϵ��	arr �Զ�װ��ֵ
void timInit(u8 pclk, u16 arr)
{
	//PA6 PB0 PB1 PB6
	//TIM3 CH1 CH3 CH4  TIM4 CH1
	//����GPIOA/GPIOB/TIM3/TIM4��RCCʱ��
	RCC->APB2ENR |= 1<<2 | 1<<3;
	RCC->APB1ENR |= 1<<1 | 1<<2;
	
	GPIOA->CRL &= ~0x0F000000;
	GPIOA->CRL |=  0x0B000000;
	
	GPIOB->CRL &= ~0x0F0000FF;
	GPIOB->CRL |=  0x0B0000BB;
	
	TIM3->PSC = pclk - 1;	//��Ƶϵ��
	TIM4->PSC = pclk - 1;
	TIM3->ARR = arr;		//�Զ�װ��ֵ
	TIM4->ARR = arr;
	
	TIM3->CCMR1 |= 0x68;	//CH1
	TIM3->CCMR2 |= 0x6868;	//CH4 CH3
	TIM4->CCMR1 |= 0x68;
	
	TIM3->CCR1 = 0;		//�ȽϼĴ�����0
	TIM3->CCR3 = 0;		//��ʾռ�ձ� 0%
	TIM3->CCR4 = 0;
	TIM4->CCR1 = 0;
	
	//ʹ��������ߵ�ƽ��Ч
	TIM3->CCER |= 0x1101;
	TIM4->CCER |= 0x01;
	
	//ʹ���Զ�װ�ع��ܺ�ʹ�ܶ�ʱ��
	TIM3->CR1 |= 1<<7 | 1<<0;
	TIM4->CR1 |= 1<<7 | 1<<0;
}
