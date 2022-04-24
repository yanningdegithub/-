#include "protocol.h"
#include "briupZigbee.h"
#include "briupUsart.h"

//协议相关的函数接口
//1、上传数据  2、处理上传指令

u8 protocolSendToRaspi(u8 devId, u8 len, u8 * buf) {
	u8 frame[50], i, check; // zigbee帧一共50字节
	check = 0x04 ^ devId ^ 0x04 ^ len;
	frame[0] = 0xaa;
	frame[1] = 0xbb;
	frame[2] = 0;
	frame[3] = 0xff;
	frame[4] = 0xff;
	//======================Data======================//
	frame[5] = 0x04; // Board ID
	frame[6] = 0x04; // Frame Type
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
