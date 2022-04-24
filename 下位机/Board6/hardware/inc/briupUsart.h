/**********************************************
*FileName: briupUsart.h
*Description: 
						初始化Debug串口 -> usart1的函数接口
						声明串口发送数据：char / str / buffer
						声明串口接收数据：char / str
*Author: xb
*CreateDate: 2018-7-12
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
*20180713   xb     加上串口接收中断、循环队列、串口DMA发送
**********************************************/

#ifndef __USART1_H__
#define __USART1_H__

#include <stm32f10x.h>

//初始化usart1的函数接口
//plck：工作时钟
//baud：要设置的波特率
void usart1Init(u8 pclk, u32 baud);

//发送函数声明
void putChar(u8 ch);      //发送1Byte数据
void putStr(char * str);  //发送String数据 ‘\0’
void putBuffer(u8 * buf, u16 length); //发送一个数组

void putDataDma(u8 * buf, u16 len);//通过DMA发送一段数据

//接收函数声明
u8 getChar(void);
u8 getStr(char * str);  //返回接收到的数据长度

//通过循环队列获取一段数据
//flag：
//    0    直接获取最近接收到的数据
//    1    判断获取到完整的一帧协议数据再返回
u16 getBuffer(u8 * buf, u8 flag);

#endif
