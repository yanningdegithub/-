/**********************************************
*FileName: briupZigbee.c
*Description: 
					Zigbee Usart2 初始化的接口
					通过DMA发送数据的函数接口
					通过Usart2中断接收数据
*Author: xb
*CreateDate: 2018-7-15
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
**********************************************/

#include "briupZigbee.h"

//循环队列
static volatile u8 zbBuffer[256];
static volatile u16 zbHead, zbTail;
static volatile u16 zbCount;

//Zigbee串口初始化
void zigbeeInit(u8 pclk, u32 baud) {
	
	NVIC_InitTypeDef nvicInit;
	
	double div = (pclk * 1000000) / (16 * baud);
	u16 mant = (u16)div;
	u16 frac = (div - mant) * 16;
	mant = mant << 4 | (frac & 0x0f);
	
	//1 RCC -> 开启GPIOA外设时钟
	RCC->APB2ENR |= 1<<2;
	RCC->APB1ENR |= 1<<17; //U2时钟
	RCC->AHBENR |= 1<<0; // DMA时钟使能

	//2 配置PA2 TX PA3 RX 引脚工作模式
	GPIOA->CRL &= ~(0x0000ff00);
	GPIOA->CRL |= 0x00008B00;
	GPIOA->ODR |= 1<<3;
	
	//3 配置Usart2
	// 配置串口波特率
	USART2->BRR = mant;
	//开启U2接收、发送、串口、接收中断、DMA发送使能
	USART2->CR1 |= 1<<13 | 1<<5 | 1<<3 | 1<<2;
	USART2->CR3 |= 1<<7;
	
	//初始化DMA U2.Tx -> DMA1 Channel 7
	DMA1_Channel7->CCR = 0;
	DMA1_Channel7->CPAR = (u32) &USART2->DR;
	DMA1_Channel7->CMAR = 0;
	DMA1_Channel7->CNDTR = 0;
	// 1<<13 优先级
	DMA1_Channel7->CCR |= 1<<13 | 1<<7 | 1<<4;
	
	nvicInit.NVIC_IRQChannel = USART2_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 2;
	nvicInit.NVIC_IRQChannelSubPriority = 3;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
	
}

//通过DMA发送一个Buf数组
void zigbeeSendBuf(u8* buf, u16 len){
	
	//关闭DMA的USART1通道
	DMA1_Channel7->CCR &= ~0x01;
	
	DMA1_Channel7->CMAR = (u32) buf;
	DMA1_Channel7->CNDTR = len;
	DMA1_Channel7->CCR |= 0x01;
	
}
//获取Zigbee数据
u16 zigbeeGetData(u8* buf, u8 flag) {
	u16 temp = zbCount, i, ck;
	if(zbCount == 0)
		return 0;
	if (!flag) {
		zbCount = 0; // 清空，给下一个人用
		for (i = 0; i < temp; i++) {
			*buf = zbBuffer[zbHead];
			buf ++;
			zbHead ++;
			zbHead %= 256;
		}
		return temp;
	}
	else {
		ck = 0;
		for(i = zbHead; ; i++){
			
			i %= 256;
			
			//收到两个ff
			if (zbBuffer[i] == 0xee && zbBuffer[i + 1] == 0xff) {
				ck = 1;
				break;
			}
			if(i == zbTail) { // over 256
				break;
			}
			
		}
		if(ck == 0)
			return 0;
		
		//防止中间插入？？？？
		temp = zbCount;
		zbCount = 0;
		
		for(i = 0; i < temp; i ++) {
			*buf = zbBuffer[zbHead];
			buf ++;
			zbHead ++;
			zbHead %= 256;
		}
		return temp;
	}
	return 0;
}


//==============================IRQHandler
void USART2_IRQHandler(void) {
	if(USART2->SR & (1<<5)) {
		zbBuffer[zbTail] = USART2->DR;
		zbTail ++;
		zbTail %= 256;
		zbCount ++;
		
	}
}
