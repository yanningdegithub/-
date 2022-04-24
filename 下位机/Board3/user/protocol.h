#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stm32f10x.h>
#include <string.h>
#include <stdlib.h>

//帧头
#define HEAD_1 0xAA
#define HEAD_2 0xBB

//功能板ID号
#define BOARD_ID 0x03

//自定义Data帧部分结构体

typedef struct{
	u8 uBoardId; // 不同功能板默认指定
	u8 uFrameType;
	u8 uDevId;
	u8 uDataLen;
	u8 uData[30];
	u8 uCheck;
	u8 uEnd;
}UserProt;

//协议相关的函数接口
//1、上传数据  2、处理上传指令

u8 protocolSend(u8 BoardId, u8 devId, u8 len, u8 * buf);
u8 protocolSendToRaspi(u8 devId, u8 type, u8 len, u8 * buf);

#endif
