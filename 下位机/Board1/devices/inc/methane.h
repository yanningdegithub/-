/**********************************************
*FileName: methane.h
*Description: 甲烷传感器函数接口实现
*Author: xb
*CreateDate: 2018-7-14
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
**********************************************/

#include <stm32f10x.h>

#ifndef __METHANE_H__
#define __METHANE_H__

void methaneInit(void);

u8 methaneStat(void);

#endif
