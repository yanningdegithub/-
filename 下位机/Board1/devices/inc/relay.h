/**********************************************
*FileName: relay.h
*Description: 继电器IO的初始化接口实现
*Author: xb
*CreateDate: 2018-7-14
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
**********************************************/

#include <stm32f10x.h>

#ifndef __RELAY_H__
#define __RELAY_H__

//初始化GPIO引脚的函数接口
void relayInit(void);

//操作函数接口
void setLeftRelay(u8 set);
void setRightRelay(u8 set);

#endif
