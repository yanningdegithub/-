/**********************************************
*FileName: relay.h
*Description: �̵���IO�ĳ�ʼ���ӿ�ʵ��
*Author: xb
*CreateDate: 2018-7-14
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
**********************************************/

#include <stm32f10x.h>

#ifndef __RELAY_H__
#define __RELAY_H__

//��ʼ��GPIO���ŵĺ����ӿ�
void relayInit(void);

//���������ӿ�
void setLeftRelay(u8 set);
void setRightRelay(u8 set);

#endif
