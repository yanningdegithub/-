/**********************************************
*FileName: oeSwitch.h
*Description: 
			光电开关的初始化函数接口定义
			通过轮询的方式返回光电开关状态
			通过中断的方式检测光电开关状态
*Author: xb
*CreateDate: 2018-7-13
*Coptright: 601410985@qq.com
*Update:    修改人 修改内容
**********************************************/

#ifndef __OESWITCH_H__
#define __OESWITCH_H__

#include <stm32f10x.h>

//光电开关的初始化接口
void oeSwitchInit(void);

//返回对射开关的当前状态
u8 currSwitchStat(void);

//返回反射开关的当前状态
u8 refSwitchStat(void);




#endif
