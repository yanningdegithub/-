#include "protocol.h"
#include "briupZigbee.h"
#include "briupUsart.h"

//协议相关的函数接口
//1、上传数据  2、处理上传指令
u8 protocolSend(u8 BoardId, u8 devId, u8 len, u8 * buf) {
	u8 frame[50], i, check; // zigbee帧一共50字节
	check = BoardId ^ devId ^ 0x03 ^ len;
	frame[0] = 0xBB;
	frame[1] = 0xAA;
	frame[2] = 0;
	frame[3] = 0xff;
	frame[4] = 0xff;
	//======================Data======================//
	frame[5] = BoardId;
	frame[6] = 0x03;
	frame[7] = devId;
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

u8 protocolSendToRaspi(u8 devId, u8 type, u8 len, u8 * buf) {
u8 frame[50], i, check; // zigbee帧一共50字节
	check = 0x05 ^ devId ^ type ^ len;
	frame[0] = 0xAA;
	frame[1] = 0xBB;
	frame[2] = 0;
	frame[3] = 0xff;
	frame[4] = 0xff;
	//======================Data======================//
	frame[5] = 0x03;
	frame[6] = type;
	frame[7] = devId;
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
//	putBuffer(frame, 12 + i);
	
	return 0;
}
