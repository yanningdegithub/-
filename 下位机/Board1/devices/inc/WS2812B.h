#ifndef __WS2812B_H
#define __WS2812B_H

#include <stm32f10x.h>

#define X_LEN			4	//����LEDX����
#define Y_LEN			4 //����LEDY����

//���������Ų�LED�ƶ�Ӧ�Ľṹ��
typedef struct
{
	u8	green;
	u8	red;
	u8	blue;
	u32 color;
}PixColor;

extern PixColor pixBuf[4][4];

//�������úõ�LED����ɫ����
void  ws2812SendData(void);

//�Ų�LED�Ƶĳ�ʼ���ӿ�
//	��ʼ��SPI��Ӧ��RCC��IO��SPI�Ĵ���
void WS2812B_Init(void);
//����һ��DMA���䣬���Ų�LED�Ƶ����ݻ�����
//������ݴ����SPI��DR
void WS2812B_EN(void);
/*********************************************
������     WS2812B_Pixel_EN
�������ܣ�������ʼ��������LED
�������: x,yΪ��ʼ����� XΪ�� YΪ��
					len������ʼ����㿪ʼ��������Ҫ����LED�ĸ�����
					RGB_Value:��Ҫ��ʾ����ɫ bit0-7��ɫ bit8-15��ɫ bit16-23��ɫ
					mode����ʾģʽ 
*********************************************/
void WS2812B_Pixel_EN(u8 x,u8 y,u8 len,u32* RGB_Value,u8 mode);
/*********************************************
������     WS2812B_Clear
�������ܣ� Ϩ�����е�LED
*********************************************/
void WS2812B_Clear(void);
#endif
