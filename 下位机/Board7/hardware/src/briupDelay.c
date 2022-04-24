/**********************************************
*FileName: briupDelay.c
*Description: 
						通过SysTick定时器实现延时功能
						包括延时的初始化函数接口
						按us延时、按ms延时、按sec延时
*Author: xb
*CreateDate: 2018-7-12
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
**********************************************/

#include "briupDelay.h"

//微秒和毫秒对应的SysTick计数次数
static u16 frac_us, frac_ms;

//延时函数的初始化接口
//Input：pclk -> 芯片工作时钟 MHz
void _delay_init(u8 pclk) {
	frac_us = pclk / 8;
	frac_ms = frac_us * 1000;
	//配置SysTick定时器
	SysTick->CTRL = 0;
}

//延时函数
void _delay_us(u32 us) {
	volatile u32 temp = 0;
	us *= frac_us;
	//关闭定时器
	SysTick->CTRL &= ~(1<<0);
	//设置重装载值
	SysTick->LOAD = us;
	//清空当前计数值
	SysTick->VAL = 0;
	SysTick->CTRL |= 1<<0;
	do {
		temp = SysTick->CTRL;
	} while( ! (temp & (1<<16)) && (temp & (1<<0)) );
	//关闭SysTick定时器
	SysTick->CTRL &= ~(1<<0);
}
void _delay_ms(u32 ms) {
	volatile u32 temp = 0;
	if (ms > 1800)
		ms = 1800; // 不如return
	ms *= frac_ms;
	//关闭定时器
	SysTick->CTRL &= ~(1<<0);
	//设置重装载值
	SysTick->LOAD = ms;
	//清空当前计数值
	SysTick->VAL = 0;
	SysTick->CTRL |= 1<<0;
	do {
		temp = SysTick->CTRL;
		//数到0后16位变为1，CTRL不再等于1
	} while( ! (temp & (1<<16)) && (temp & (1<<0)) );
	//关闭SysTick定时器
	SysTick->CTRL &= ~(1<<0);
}

//传入的sec保留两位小数
// N sec -> N*1000 ms
void _delay_sec(double sec) {
	u32 count = sec * 1000.0;
	while (count > 1800) {
		_delay_ms(1800);
		count -= 1800;
	}
	_delay_ms(count);
}

//时分秒
