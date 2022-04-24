/********************
* FileName: 	a4988.h
* Description: 	
		��������ĳ�ʼ�������������ӿ�
		�Լ����ŵĶ���
* Author:		Dennis Chen
* CreateDate:	2018-7-10
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-10	����	��ӳ�ʼ���ӿ�����
*********************/
#ifndef __A4988_H__
#define __A4988_H__

#include <stm32f10x.h>

//���ù�������Ϊ�ߵ�ƽ
#define A4988_EN_H()	GPIOB->ODR |= (1<<0)
#define A4988_MS1_H()   GPIOB->ODR |= (1<<1)
#define A4988_MS2_H()	GPIOB->ODR |= (1<<5)
#define A4988_MS3_H()   GPIOB->ODR |= (1<<6)
#define A4988_RESET_H()	GPIOB->ODR |= (1<<7)
#define A4988_SLEEP_H()	GPIOB->ODR |= (1<<8)
#define A4988_DIR_H()	GPIOB->ODR |= (1<<13)
//���ù�������Ϊ�͵�ƽ
#define A4988_EN_L()	GPIOB->ODR &= ~(1<<0)
#define A4988_MS1_L()   GPIOB->ODR &= ~(1<<1)
#define A4988_MS2_L()	GPIOB->ODR &= ~(1<<5)
#define A4988_MS3_L()   GPIOB->ODR &= ~(1<<6)
#define A4988_RESET_L()	GPIOB->ODR &= ~(1<<7)
#define A4988_SLEEP_L()	GPIOB->ODR &= ~(1<<8)
#define A4988_DIR_L()	GPIOB->ODR &= ~(1<<13)


/******************************************
��������TIM4_TIM3_Init
�������ܣ�ͨ������TIM4 TIM3Ϊ����ģʽʵ��
					׼ȷ����������
					�˷�ʽ�����ڲ���������ŷ��������
*******************************************/
void  TIM4_TIM3_Init(void);

/*********************************************************
���ƣ�Motor_Control(u16 cycle, u16 pulse_num)
˵��������ָ���������壬ÿ����������Ϊcycle΢�룬����������ɵĸ���
      �͵�����ߵ�ƽʱ���й�ϵ������������ɸߵ�ƽʱ����ȷ��
����cycle��ΪTIM3һ����������,��λ(us)
����pulse_num��Ϊ������������������������
����ֵ����
*********************************************************/
void Motor_Control(u16 cycle, u16 pulse_num, u8 dir);

/******************************************
��������A4988_Init
�������ܣ���ʼ��A4988�����������оƬ
*******************************************/
void  A4988_Init(void);

#endif
