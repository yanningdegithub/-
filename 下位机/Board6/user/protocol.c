/**********************************************
*FileName: protocol.c
*Description:板1协议函数接口
*Author: xb
*CreateDate: 2018-7-16
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
**********************************************/

#include "protocol.h"
#include "briupZigbee.h"
#include "briupUsart.h"

static u8 cmdCheck(UserProt * cmd);

//协议相关的函数接口
//1、上传数据  2、处理上传指令
//u8 protocolSend(u8 devId, u8 type, u8 len, u8 * buf) {
//	u8 frame[50], i, check; // zigbee帧一共50字节
//	check = BOARD_ID ^ devId ^ type ^ len;
//	frame[0] = FRAME_HEAD1;
//	frame[1] = FRAME_HEAD2;
//	frame[2] = 0;
//	frame[3] = 0xff;
//	frame[4] = 0xff;
//	//======================Data======================//
//	frame[5] = BOARD_ID;
//	frame[6] = type;
//	frame[7] = devId;//////校验位要在后面
//	frame[8] = len;
//	for(i = 0; i < len; i++) {
//		frame[9 + i] = *buf;
//		check ^= *buf;
//		buf++;
//	}
//	frame[9 + i] = check;
//	frame[10 + i] = 0xEE;
//	//======================DataEnd===================//
//	frame[11 + i] = 0xFF;
//	

////	zigbeeSendBuf(frame, 12 + i);

//	putDataDma(frame, 12 + i);

//	
//	return 0;
//}

//判断是否接收到一帧数据
u8 protocolRes(UserProt * cmd) {
	u8 len, buf[50];

	len = zigbeeGetData(buf, 1);
	
//	len = getBuffer(buf, 1);

	if(len == 0)
		return 1; // 未接收到有效数据
	//putBuffer(buf, len);
	if(buf[0] != 0xbb || buf[1] != 0xaa)
		return 2; // 数据帧头校验失败
	if(buf[5] != 0x06)
		return 3; // 数据不是给该功能板的
	
	memset(cmd, 0, sizeof(UserProt));
	memcpy(cmd, (buf + 5), len - 3);
	cmd->uCheck = buf[len - 3];
	cmd->uEnd = buf[len - 2];
	
	if(cmdCheck(cmd))
		return 4; // 检验未通过
	
	return 0;
}

//======================内部处理函数======================//
static u8 cmdCheck(UserProt * cmd) {
	u8 check = cmd -> uBoardId;
	u8 len, i, *cp = (u8*)cmd;
	len = cmd->uDataLen + 4;
	cp++; // 有个BUG，要先++指向cmd第一个东西，？？？？？？
	for(i = 0; i < len - 1; i++) {
		check ^= *cp;
		cp ++;
	}
	if(check == cmd -> uCheck)
		return 0; // 校验成功
	else
		putChar(check);	// debug achieve check
		return 1; // 检验失败
}
