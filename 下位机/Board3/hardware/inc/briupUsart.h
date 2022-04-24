/**********************************************
*FileName: briupUsart.h
*Description: 
						��ʼ��Debug���� -> usart1�ĺ����ӿ�
						�������ڷ������ݣ�char / str / buffer
						�������ڽ������ݣ�char / str
*Author: xb
*CreateDate: 2018-7-12
*Coptright: 601410985@qq.com
*Update:    �޸��� �޸�����
*20180713   xb     ���ϴ��ڽ����жϡ�ѭ�����С�����DMA����
**********************************************/

#ifndef __USART1_H__
#define __USART1_H__

#include <stm32f10x.h>

//��ʼ��usart1�ĺ����ӿ�
//plck������ʱ��
//baud��Ҫ���õĲ�����
void usart1Init(u8 pclk, u32 baud);

//���ͺ�������
void putChar(u8 ch);      //����1Byte����
void putStr(char * str);  //����String���� ��\0��
void putBuffer(u8 * buf, u16 length); //����һ������

void putDataDma(u8 * buf, u16 len);//ͨ��DMA����һ������

//���պ�������
u8 getChar(void);
u8 getStr(char * str);  //���ؽ��յ������ݳ���

//ͨ��ѭ�����л�ȡһ������
//flag��
//    0    ֱ�ӻ�ȡ������յ�������
//    1    �жϻ�ȡ��������һ֡Э�������ٷ���
u16 getBuffer(u8 * buf, u8 flag);

#endif
