/**********************************************
*FileName: miniFan.h
*Description: �������IO�ĳ�ʼ���ӿ�ʵ��
*Author: xb
*CreateDate: 2018-7-14
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
**********************************************/

#include <stm32f10x.h>

#ifndef __MINIFAN_H__
#define __MINIFAN_H__

//��ʼ��GPIO���ŵĺ����ӿ�
void miniFanInit(void);

//���������ӿ�
void setMiniFan(u8 set);
#endif
