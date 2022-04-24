/**********************************************
*FileName: protocol.h
*Description:板1协议函数接口
*Author: xb
*CreateDate: 2018-7-16
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
**********************************************/

#ifndef __PROTOCOl_H__
#define __PROTOCOl_H__

#include <stm32f10x.h>
#include <string.h>
#include <stdlib.h>

//设备ID号
#define HIGHLIGHT_ID 0x01
#define COLOR_ID 0x02
#define INFRARED_ID 0x03
#define RGB_ID 0x04
#define BEEP_ID 0x05

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

u8 protocolSendToRaspi(u8 devId, u8 type, u8 len, u8 * buf);
u8 protocolSendToBoard(u8 BoardId, u8 devId, u8 len, u8 * buf);

//u8 protocolRes(UserProt * cmd);

#endif
