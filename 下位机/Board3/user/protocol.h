#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stm32f10x.h>
#include <string.h>
#include <stdlib.h>

//֡ͷ
#define HEAD_1 0xAA
#define HEAD_2 0xBB

//���ܰ�ID��
#define BOARD_ID 0x03

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

u8 protocolSend(u8 BoardId, u8 devId, u8 len, u8 * buf);
u8 protocolSendToRaspi(u8 devId, u8 type, u8 len, u8 * buf);

#endif
