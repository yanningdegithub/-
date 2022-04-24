/**********************************************
*FileName: protocol.h
*Description:��1Э�麯���ӿ�
*Author: xb
*CreateDate: 2018-7-16
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
**********************************************/

#ifndef __PROTOCOl_H__
#define __PROTOCOl_H__

#include <stm32f10x.h>
#include <string.h>
#include <stdlib.h>

//�豸ID��
#define HIGHLIGHT_ID 0x01
#define COLOR_ID 0x02
#define INFRARED_ID 0x03
#define RGB_ID 0x04
#define BEEP_ID 0x05

//�Զ���Data֡���ֽṹ��
typedef struct{
	u8 uBoardId; // ��ͬ���ܰ�Ĭ��ָ��
	u8 uFrameType;
	u8 uDevId;
	u8 uDataLen;
	u8 uData[30];
	u8 uCheck;
	u8 uEnd;
}UserProt;

//Э����صĺ����ӿ�
//1���ϴ�����  2�������ϴ�ָ��

//u8 protocolSend(u8 devId, u8 type, u8 len, u8 * buf);

u8 protocolRes(UserProt * cmd);

#endif
