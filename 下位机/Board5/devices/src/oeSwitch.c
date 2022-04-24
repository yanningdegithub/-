/**********************************************
*FileName: oeSwitch.c
*Description: 
			光电开关的初始化函数接口定义
			通过轮询的方式返回光电开关状态
			通过中断的方式检测光电开关状态
*Author: xb
*CreateDate: 2018-7-13
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
**********************************************/

#include "oeSwitch.h"
#include "briupDelay.h"
#include "protocol.h"
#include "alarm.h"

//反射PB0 对射PB1
//光电开关的初始化接口
void oeSwitchInit(void) {
	NVIC_InitTypeDef nvicInit;
	
	//初始化光电开关IO引脚
	RCC->APB2ENR |= 1<<3; // PB时钟
	RCC->APB2ENR |= 1<<0; // AFIO时钟
	
	//PB0 PB1 上拉输入
	GPIOB->CRL &= ~0x000000ff;
	GPIOB->CRL |= 0x00000088;
	GPIOB->ODR |= 1<<1 | 1<<0;
	
	//外部中断线的端口设置
	AFIO->EXTICR[0] |= 0x0011;
	
	//外部中断的触发模式与使能-_-
	EXTI->RTSR &= ~(1<<1 | 1<<0);
	EXTI->FTSR |= 1<<1 | 1<<0;
	EXTI->IMR |= 1<<1 | 1<<0;
	
	//配置外部中断线0的NVIC优先级
	nvicInit.NVIC_IRQChannel = EXTI0_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 1;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
	
	//配置外部中断线1的NVIC优先级
	nvicInit.NVIC_IRQChannel = EXTI1_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 2;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
	
}

//返回对射开关的当前状态
u8 currSwitchStat(void) {
	if(GPIOB->IDR & (1<<1))
		return 1;
	else
		return 0;
}

//返回反射开关的当前状态
u8 refSwitchStat(void) {
	if(GPIOB->IDR & (1<<0))
		return 1;
	else
		return 0;
}

//===================外部中断服务函数===================//
void EXTI0_IRQHandler(void) {
	_delay_ms(10);
	//响应并清除中断标志位
	if( !(GPIOB->IDR & 0x01) ) {
		EXTI->PR |= 1<<0;
//		rvseSwitchAlarm();
		alarmAction();
	}
}

void EXTI1_IRQHandler(void) {
	_delay_ms(10);
	//响应并清除中断标志位
	if( !(GPIOB->IDR & 0x02) ) {
		EXTI->PR |= 1<<1;
//		oppoSwitchAlarm();
		alarmAction();
	}
}
