/**********************************************
*FileName: oeSwitch.h
*Description: 
			��翪�صĳ�ʼ�������ӿڶ���
			ͨ����ѯ�ķ�ʽ���ع�翪��״̬
			ͨ���жϵķ�ʽ����翪��״̬
*Author: xb
*CreateDate: 2018-7-13
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
**********************************************/

#ifndef __OESWITCH_H__
#define __OESWITCH_H__

#include <stm32f10x.h>

//��翪�صĳ�ʼ���ӿ�
void oeSwitchInit(void);

//���ض��俪�صĵ�ǰ״̬
u8 currSwitchStat(void);

//���ط��俪�صĵ�ǰ״̬
u8 refSwitchStat(void);




#endif
