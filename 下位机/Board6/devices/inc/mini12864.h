/********************
* FileName: 	mini12864.h
* Description: 	
			Һ������������
			���������ӿ�����
* Author:		Dennis Chen
* CreateDate:	2018-7-10
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-10	����	��ӳ�ʼ���ӿ�����
*********************/
#ifndef __MINI12864_H__
#define __MINI12864_H__

#include <stm32f10x.h>

#define Rom_OUT_IN		((GPIOB->IDR & (1<<7))>>7)	//�ֿ� IC �ӿڶ���:Rom_OUT �����ֿ� IC �� SO

#define Lcd_Sclk_H()	GPIOB->ODR |= (1<<14) 			//�ӿڶ���:Lcd_Sclk ���� LCD �� SCLK
#define Lcd_Sid_H() 	GPIOB->ODR |= (1<<13)				//�ӿڶ���:Lcd_Sid ���� LCD �� SDA
#define Lcd_RS_H()		GPIOB->ODR |= (1<<12)			//�ӿڶ���:Lcd_RS ���� LCD �� RS,Ҳ�С�CD��
#define Lcd_CS_H()		GPIOB->ODR |= (1<<15) 			//�ӿڶ���:Lcd_CS ���� LCD �� CS1
#define Lcd_Reset_H()	GPIOB->ODR |= (1<<8)				//�ӿڶ���:Lcd_Reset ���� LCD �� RESET
#define Rom_IN_H()		GPIOB->ODR |= (1<<6) 			//�ֿ� IC �ӿڶ���:Rom_IN �����ֿ� IC �� SI
#define Rom_SCK_H()		GPIOB->ODR |= (1<<4)  		//�ֿ� IC �ӿڶ���:Rom_SCK �����ֿ� IC �� SCK
#define Rom_CS_H()		GPIOB->ODR |= (1<<5)			//�ֿ� IC �ӿڶ��� Rom_CS �����ֿ� IC �� CS

#define Lcd_Sclk_L()	GPIOB->ODR &= ~(1<<14) 			//�ӿڶ���:Lcd_Sclk ���� LCD �� SCLK
#define Lcd_Sid_L() 	GPIOB->ODR &= ~(1<<13)				//�ӿڶ���:Lcd_Sid ���� LCD �� SDA
#define Lcd_RS_L()		GPIOB->ODR &= ~(1<<12)			//�ӿڶ���:Lcd_RS ���� LCD �� RS,Ҳ�С�CD��
#define Lcd_CS_L()		GPIOB->ODR &= ~(1<<15) 			//�ӿڶ���:Lcd_CS ���� LCD �� CS1
#define Lcd_Reset_L()	GPIOB->ODR &= ~(1<<8)				//�ӿڶ���:Lcd_Reset ���� LCD �� RESET
#define Rom_IN_L()		GPIOB->ODR &= ~(1<<6) 			//�ֿ� IC �ӿڶ���:Rom_IN �����ֿ� IC �� SI
#define Rom_SCK_L()		GPIOB->ODR &= ~(1<<4)  		//�ֿ� IC �ӿڶ���:Rom_SCK �����ֿ� IC �� SCK
#define Rom_CS_L()		GPIOB->ODR &= ~(1<<5)			//�ֿ� IC �ӿڶ��� Rom_CS �����ֿ� IC �� CS


//=====================================================================================
//
//	�����ʾ����������
//
//=====================================================================================

//��ӡGB2312���ַ���
void showStrCn(u8 page,u8 column,u8 *text);
//ȫ������
void Clear_Screen_IN(void);

//LCDģ��GPIO�ڳ�ʼ��
void Lcd_GPIO_Iint_IN(void);
//LCD ģ���ʼ��
void Lcd_Init_IN(void);
//дָ�LCD ģ��
void Transfer_Cmd_Lcd_IN(int cmd);
//д���ݵ� LCD ģ��
void Transfer_Data_Lcd_IN(int data);
//LCD ���ݵ�ַ����
void Lcd_Address_IN(u32 page,u32 column);
//��ʾ 128x64 ����ͼ��
void display_128x64_IN(u8 *dp);


//��ָ�����Ѷ�ֿ� IC
void send_command_to_ROM_IN( u8 datu );
//�Ӿ���Ѷ�ֿ� IC ��ȡ���ֻ��ַ����ݣ�1 ���ֽڣ�
static u8 get_data_from_ROM_IN(void);
//��ָ����ַ��������д��Һ����ָ����page, column)������
void get_and_write_16x16_IN(long fontaddr,u8 page,u8 column);
//��ָ����ַ��������д��Һ����ָ����page, column)������
void get_and_write_8x16_IN(long fontaddr,u8 page,u8 column);


#endif
