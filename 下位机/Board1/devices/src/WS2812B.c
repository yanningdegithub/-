/*******************************************************
�����ͺţ�KS6812 (WS2812B��֮��������)
ͨ�ŷ�ʽ��SPI(���߷���)+DMA
�ļ����ܣ�����KS6812��ʾ
��������˳��G R  B ���ȴ�����ɫ �ٴ�����ɫ �ٴ�����ɫ
*******************************************************/

#include "WS2812B.h"
#include <string.h>

PixColor pixBuf[4][4] = {0};

#define WS_ONE		0xFFC0	//10 H    6L
#define WS_ZERO		0xF000	// 4 H	 12L

u16 PixelBuffer[485];//100+16*24+1 0~99��ԶΪ0 ���ڳ�ʼ�� 1636��ԶΪ0 ���ڴ��������������

void WS2812B_Init(void)
{
	u16 i;
	//SPI����
	
	RCC->APB2ENR|=1<<12;//SPI1ʱ��ʹ�� 
	RCC->APB2ENR|=1<<2; //PROTAʱ��ʹ��
	RCC->AHBENR|=1<<0;  //DMA1ʱ��ʹ��
	
	GPIOA->CRL&=0X0FFFFFFF;		 
	GPIOA->CRL|=0XB0000000;		 //PA7 ���� 
	
	//GPIOA->ODR|=0X7<<5;			 //��ʼ���ߵ�ƽ
	
	SPI1->CR1|=1<<15;
	SPI1->CR1|=1<<14;//����ֻ��ģʽ
	SPI1->CR1|=1<<11;//16λ���ݸ�ʽ
	//SPI1->CR1|=1<<10;
	SPI1->CR1|=1<<9; //���nss����
	SPI1->CR1|=1<<8;  
	SPI1->CR1|=0<<7; //MSBfirst 
	SPI1->CR1|=1<<3; //Fsck=Fcpu/4
	SPI1->CR1|=1<<2; //SPI����
	SPI1->CR1&=~0x02;//����ģʽ��SCKΪ0 CPOL=0
	SPI1->CR1&=~0x01;//���ݲ����ӵ�һ��ʱ����ؿ�ʼ,CPHA=0  

  SPI1->CR2|=1<<1;//�������ͻ�����DMA 
	SPI1->CR1|=1<<6; //SPI�豸ʹ��
	
	DMA1_Channel3->CCR|=1<<12;//�����ȼ�
  DMA1_Channel3->CCR|=1<<10;//�洢�����ݿ��Ϊ16λ
	DMA1_Channel3->CCR|=1<<8;//�������ݿ��Ϊ16λ
	DMA1_Channel3->CCR|=1<<7;//�洢����ַ����ģʽ
	DMA1_Channel3->CCR|=1<<4;//�Ӵ洢����
	DMA1_Channel3->CNDTR=0;//����������Ϊ0
	DMA1_Channel3->CPAR = (u32)&(SPI1->DR);//�����ַ
	DMA1_Channel3->CMAR = (u32)(PixelBuffer);//�洢����ַ
	for(i=0;i<485;i++)
	{
		PixelBuffer[i]=0X0000;
	}
}


//�������úõ�LED����ɫ����
//	ֱ������ָ������ֵ��LED��ɫ��
//	���ṹ�������е����� װ���ɫ������
//	����ɫ����ͨ��DMA����
void  ws2812SendData(void)
{
	//�ṹ�� G R B -> color
	u16 i,j,k, flag = 100;
	//��ʼ����ɫ����
	for( i = 0;i < 485;i ++)
		PixelBuffer[i] = 0;
	
	for( i = 0;i < 4;i ++)
	{
		for( j = 0;j < 4;j ++)
		{
			pixBuf[i][j].color = pixBuf[i][j].green <<16;
			pixBuf[i][j].color |= pixBuf[i][j].red << 8;
			pixBuf[i][j].color |= pixBuf[i][j].blue;
			
			for( k = 0;k < 24;k ++)
			{
				//PixelBuffer[flag + (i*4+j)*24 + k]
				if( pixBuf[i][j].color & (1<<23))
				{
					PixelBuffer[flag + (i*4+j)*24 + k] = WS_ONE;
				}
				else
					PixelBuffer[flag + (i*4+j)*24 + k] = WS_ZERO;
				pixBuf[i][j].color <<= 1;
			}
		}
	}
	WS2812B_EN();
}


void WS2812B_EN(void)
{
	DMA1_Channel3->CCR&=~(1<<0);//�ر�DMA1ͨ��3
	DMA1_Channel3->CNDTR = 485;//��ʼ����������ֵ
	DMA1_Channel3->CCR|=1<<0;//ʹ��DMA����
}
/*********************************************
������     WS2812B_Pixel_EN
�������ܣ�������ʼ��������LED
�������: x,yΪ��ʼ����� XΪ�� YΪ��
					len������ʼ����㿪ʼ��������Ҫ����LED�ĸ�����
					RGB_Value:��Ҫ��ʾ����ɫ bit0-7��ɫ bit8-15��ɫ bit16-23��ɫ
					mode����ʾģʽ 
*********************************************/
void WS2812B_Pixel_EN(u8 x,u8 y,u8 len,u32* RGB_Value,u8 mode)
{
	u16 Pixel_Point = 0;
	u16 One=0XFFC0;
	u16 Zero=0XF000;
	u32 i=0;
	Pixel_Point = (Y_LEN*y+x)*24+100;
	while(len--)
	{
		for(i=0X800000;i>=0X01;i>>=1)
		{
			PixelBuffer[Pixel_Point]= (*RGB_Value)&i ? One : Zero;
			Pixel_Point++;
		}
		if(mode == 1)
			RGB_Value++;
	}
	WS2812B_EN();
}
/*********************************************
������     WS2812B_Clear
�������ܣ� Ϩ�����е�LED
*********************************************/
void WS2812B_Clear(void)
{
	u16 i;
	memset(pixBuf, 0, sizeof(pixBuf));
	for(i=0;i<485;i++)
	{
		PixelBuffer[i+100]=0XF000;
	}
	WS2812B_EN();
}



