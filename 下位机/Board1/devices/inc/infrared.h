/**********************************************
*FileName: infrared.h
*Description: 红外传感器初始化接口
*Author: xb
*CreateDate: 2018-7-14
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
*2018-7-11  xb     添加初始化函数声明
**********************************************/

#include <stm32f10x.h>

#ifndef __INFRARED_H__
#define __INFRARED_H__

void infraredInit(void);

u8 infraredStat(void);

#endif
