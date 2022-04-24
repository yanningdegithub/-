/**********************************************
*FileName: oeSwitch.c
*Description: 
			��翪�صĳ�ʼ�������ӿڶ���
			ͨ����ѯ�ķ�ʽ���ع�翪��״̬
			ͨ���жϵķ�ʽ����翪��״̬
*Author: xb
*CreateDate: 2018-7-13
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
**********************************************/

#include "oeSwitch.h"
#include "briupDelay.h"
#include "protocol.h"
#include "alarm.h"

//����PB0 ����PB1
//��翪�صĳ�ʼ���ӿ�
void oeSwitchInit(void) {
	NVIC_InitTypeDef nvicInit;
	
	//��ʼ����翪��IO����
	RCC->APB2ENR |= 1<<3; // PBʱ��
	RCC->APB2ENR |= 1<<0; // AFIOʱ��
	
	//PB0 PB1 ��������
	GPIOB->CRL &= ~0x000000ff;
	GPIOB->CRL |= 0x00000088;
	GPIOB->ODR |= 1<<1 | 1<<0;
	
	//�ⲿ�ж��ߵĶ˿�����
	AFIO->EXTICR[0] |= 0x0011;
	
	//�ⲿ�жϵĴ���ģʽ��ʹ��-_-
	EXTI->RTSR &= ~(1<<1 | 1<<0);
	EXTI->FTSR |= 1<<1 | 1<<0;
	EXTI->IMR |= 1<<1 | 1<<0;
	
	//�����ⲿ�ж���0��NVIC���ȼ�
	nvicInit.NVIC_IRQChannel = EXTI0_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 1;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
	
	//�����ⲿ�ж���1��NVIC���ȼ�
	nvicInit.NVIC_IRQChannel = EXTI1_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 2;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
	
}

//���ض��俪�صĵ�ǰ״̬
u8 currSwitchStat(void) {
	if(GPIOB->IDR & (1<<1))
		return 1;
	else
		return 0;
}

//���ط��俪�صĵ�ǰ״̬
u8 refSwitchStat(void) {
	if(GPIOB->IDR & (1<<0))
		return 1;
	else
		return 0;
}

//===================�ⲿ�жϷ�����===================//
void EXTI0_IRQHandler(void) {
	_delay_ms(10);
	//��Ӧ������жϱ�־λ
	if( !(GPIOB->IDR & 0x01) ) {
		EXTI->PR |= 1<<0;
//		rvseSwitchAlarm();
		alarmAction();
	}
}

void EXTI1_IRQHandler(void) {
	_delay_ms(10);
	//��Ӧ������жϱ�־λ
	if( !(GPIOB->IDR & 0x02) ) {
		EXTI->PR |= 1<<1;
//		oppoSwitchAlarm();
		alarmAction();
	}
}
