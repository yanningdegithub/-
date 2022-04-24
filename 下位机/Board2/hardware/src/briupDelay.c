/**********************************************
*FileName: briupDelay.c
*Description: 
						ͨ��SysTick��ʱ��ʵ����ʱ����
						������ʱ�ĳ�ʼ�������ӿ�
						��us��ʱ����ms��ʱ����sec��ʱ
*Author: xb
*CreateDate: 2018-7-12
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
**********************************************/

#include "briupDelay.h"

//΢��ͺ����Ӧ��SysTick��������
static u16 frac_us, frac_ms;

//��ʱ�����ĳ�ʼ���ӿ�
//Input��pclk -> оƬ����ʱ�� MHz
void _delay_init(u8 pclk) {
	frac_us = pclk / 8;
	frac_ms = frac_us * 1000;
	//����SysTick��ʱ��
	SysTick->CTRL = 0;
}

//��ʱ����
void _delay_us(u32 us) {
	volatile u32 temp = 0;
	us *= frac_us;
	//�رն�ʱ��
	SysTick->CTRL &= ~(1<<0);
	//������װ��ֵ
	SysTick->LOAD = us;
	//��յ�ǰ����ֵ
	SysTick->VAL = 0;
	SysTick->CTRL |= 1<<0;
	do {
		temp = SysTick->CTRL;
	} while( ! (temp & (1<<16)) && (temp & (1<<0)) );
	//�ر�SysTick��ʱ��
	SysTick->CTRL &= ~(1<<0);
}
void _delay_ms(u32 ms) {
	volatile u32 temp = 0;
	if (ms > 1800)
		ms = 1800; // ����return
	ms *= frac_ms;
	//�رն�ʱ��
	SysTick->CTRL &= ~(1<<0);
	//������װ��ֵ
	SysTick->LOAD = ms;
	//��յ�ǰ����ֵ
	SysTick->VAL = 0;
	SysTick->CTRL |= 1<<0;
	do {
		temp = SysTick->CTRL;
		//����0��16λ��Ϊ1��CTRL���ٵ���1
	} while( ! (temp & (1<<16)) && (temp & (1<<0)) );
	//�ر�SysTick��ʱ��
	SysTick->CTRL &= ~(1<<0);
}

//�����sec������λС��
// N sec -> N*1000 ms
void _delay_sec(double sec) {
	u32 count = sec * 1000.0;
	while (count > 1800) {
		_delay_ms(1800);
		count -= 1800;
	}
	_delay_ms(count);
}

//ʱ����
