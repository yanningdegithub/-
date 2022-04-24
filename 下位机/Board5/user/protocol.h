#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stm32f10x.h>
#include <string.h>
#include <stdlib.h>

//֡ͷ
#define upStream { frame[0] = 0xAA; frame[1] = 0xBB; }
#define downStream { frame[0] = 0xBB; frame[1] = 0xAA; }

//���ܰ�ID��
#define BOARD_ID 0x05

//�豸ID��



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

void oppoSwitchAlarm(void);
void rvseSwitchAlarm(void);

u8 protocolSend(u8 devId, u8 type, u8 len, u8 * buf);

u8 protocolRes(UserProt * cmd);

#endif
