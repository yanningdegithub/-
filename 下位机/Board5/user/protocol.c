/**********************************************
*FileName: B1Protocol.h
*Description:��1Э�麯���ӿ�
*Author: xb
*CreateDate: 2018-7-16
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
**********************************************/

#include "protocol.h"
#include "briupZigbee.h"
#include "briupUsart.h"
#include "briupDelay.h"

static u8 cmdCheck(UserProt * cmd);

void oppoSwitchAlarm() {
	u8 frame[50] = { \
		0xaa, 0xbb, 0x00, 0xff, 0xff, \
		0x05, 0x06, 0x03, \
		0x02, 0xd6, 0x06, \
		0x00, 0xee, 0xff
	};

	u8 check = \
		frame[5] ^ \
		frame[6] ^ \
		frame[7] ^ \
		frame[8] ^ \
		frame[9] ^ \
		frame[10];
	frame[11] = check;

	zigbeeSendBuf(frame, 14);
}

void rvseSwitchAlarm() {
	u8 frame[50] = { \
		0xaa, 0xbb, 0x00, 0xff, 0xff, \
		0x05, 0x06, 0x04, \
		0x02, 0xd6, 0x07, \
		0x00, 0xee, 0xff
	};

	u8 check = \
		frame[5] ^ \
		frame[6] ^ \
		frame[7] ^ \
		frame[8] ^ \
		frame[9] ^ \
		frame[10];
	frame[11] = check;

	zigbeeSendBuf(frame, 14);
}

//Э����صĺ����ӿ�
//1���ϴ�����  2�������ϴ�ָ��
u8 protocolSend(u8 devId, u8 type, u8 len, u8 * buf) {
	u8 frame[50], i, check; // zigbee֡һ��50�ֽ�
	check = BOARD_ID ^ devId ^ type ^ len;
	upStream;
	frame[2] = 0;
	frame[3] = 0xff;
	frame[4] = 0xff;
	//======================Data======================//
	frame[5] = BOARD_ID;
	frame[6] = type;
	frame[7] = devId;//////У��λҪ�ں���
	frame[8] = len;
	for(i = 0; i < len; i++) {
		frame[9 + i] = *buf;
		check ^= *buf;
		buf++;
	}
	frame[9 + i] = check;
	frame[10 + i] = 0xEE;
	//======================DataEnd===================//
	frame[11 + i] = 0xFF;
	

	zigbeeSendBuf(frame, 12 + i);

//	putDataDma(frame, 12 + i);

	
	return 0;
}

u8 protocolRes(UserProt * cmd) {
		//�ж��Ƿ���յ�һ֡����
	u8 len, buf[50];


	len = zigbeeGetData(buf, 1);

//	len = getBuffer(buf, 1);

	if(len == 0)
		return 1; // δ���յ���Ч����
	//zigbeeSendBuf(buf, len);
	if(buf[0] != 0xBB || buf[1] != 0xAA)
		return 2; // ����֡ͷУ��ʧ��
	if(buf[5] != BOARD_ID)
		return 3; // ���ݲ��Ǹ��ù��ܰ��
	
	memset(cmd, 0, sizeof(UserProt));
	memcpy(cmd, (buf + 5), len - 3);
	cmd->uCheck = buf[len - 3];
	cmd->uEnd = buf[len - 2];
	
	//putBuffer(buf, len);
	
	if(cmdCheck(cmd))
		return 4; // ����δͨ��
	
	return 0;
}

//======================�ڲ�������======================//
static u8 cmdCheck(UserProt * cmd) {
	u8 check = cmd -> uBoardId;
	u8 len, i, *cp = (u8*)cmd;
	len = cmd->uDataLen + 4;
	cp++;
	for(i = 0; i < len - 1; i++) {
		check ^= *cp;
		cp ++;
	}
	if(check == cmd -> uCheck)
		return 0; // У��ɹ�
	else
		//zigbeeSendBuf((u8*)"nonono", 6); // debug achieve check
		//putBuffer((u8*)"01234567", 8);
		//putChar(check);
		return 1; // ����ʧ��
}
