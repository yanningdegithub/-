/*180716
I2C�������������Ļ��������ȳ�ʼ��
����ԭʼ����/������

���ȳ�ʼ��I2Cͨ�Žӿ�
��ʹ����ʪ�ȴ������������ߴ�����
*����ǿ�ȴ�������Hardware��BH1750������ֲ

*/

/********************
* FileName: 	briupI2C.c
* Description: 	
		���ģ��i2c (iic) ͨ�ŵ�
		�ӿڳ�ʼ����ͨ�Ź���ʵ�ֺ���
* Author:		Dennis Chen
* CreateDate:	2018-7-9
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-9	����	��ӳ�ʼ���ӿ�����
*********************/
#include "briupI2C.h"
#include "briupDelay.h"

//��ʼ��IIC
void IIC_Init(void)
{					     
	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��	   	  
	GPIOB->CRL&=0XFFF00FFF;
	GPIOB->CRL|=0X00033000;;//PB3/PB4����������� 
	IIC_SCL_H( );
	IIC_SDA_H( );
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA_H( );	  	  
	IIC_SCL_H( );
	_delay_us(4);
 	IIC_SDA_L( );//START:when CLK is high,DATA change form high to low 
	_delay_us(4);
	IIC_SCL_L( );//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL_L( );
	IIC_SDA_L( );//STOP:when CLK is high DATA change form low to high
 	_delay_us(4);
	IIC_SCL_H( ); 
	_delay_us(1);
	IIC_SDA_H( );//����I2C���߽����ź�
	_delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA_H( );_delay_us(1);	   
	IIC_SCL_H( );_delay_us(1);	
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			//IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L( );//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL_L( );
	SDA_OUT();
	IIC_SDA_L( );
	_delay_us(2);
	IIC_SCL_H( );
	_delay_us(2);
	IIC_SCL_L( );
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL_L( );
	SDA_OUT();
	IIC_SDA_H( );
	_delay_us(2);
	IIC_SCL_H( );
	_delay_us(2);
	IIC_SCL_L( );
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��		  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL_L( );//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {
		if( (txd & 0x80) >> 7)
			IIC_SDA_H();
		else
			IIC_SDA_L();
		
        txd<<=1; 	  
		_delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_H( );
		_delay_us(2); 
		IIC_SCL_L( );	
		_delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL_L( ); 
        _delay_us(2);
				IIC_SCL_H( );
        receive<<=1;
        if(READ_SDA)receive++;   
		_delay_us(1); 
    }	
		//IIC_SCL_L( );	
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}
//���ֽ�д��
u8 Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_Date)
{
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(SlaveAddress);//�����豸��ַ
	if(IIC_Wait_Ack()){IIC_Stop(); return 1;}
	IIC_Send_Byte(REG_Address);//���Ͳ����Ĵ�����ַ
	IIC_Wait_Ack();
	IIC_Send_Byte(REG_Date);//����д��Ĵ���������
	if(IIC_Wait_Ack()){IIC_Stop(); return 1;}
	IIC_Stop();
	_delay_us(200);
	return 0;
}
//���ֽڶ�ȡ
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{
  unsigned char REG_Date;
	IIC_Start();
	IIC_Send_Byte(SlaveAddress);
	if(IIC_Wait_Ack()){IIC_Stop(); return 0;}
	IIC_Send_Byte(REG_Address);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(SlaveAddress+1);
	IIC_Wait_Ack();
	REG_Date = IIC_Read_Byte(0);
	IIC_Stop();
	return REG_Date;
}

//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
unsigned char Single_Read_Len(unsigned char SlaveAddress,unsigned char REG_Address,u8 len,u8 *buf)
{ 
 	IIC_Start(); 
	IIC_Send_Byte(SlaveAddress);//����������ַ
	if(IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_Send_Byte(REG_Address);	//д�Ĵ�����ַ
    IIC_Wait_Ack();		//�ȴ�Ӧ��
		_delay_ms(100);			//����SHT20��Ҫһ����ʱ��������ݲ������˴�����ʱ������
    IIC_Start();
	IIC_Send_Byte(SlaveAddress+1);//����������ַ+������	
    IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	while(len)
	{
		if(len==1)*buf=IIC_Read_Byte(0);//������,����nACK 
		else *buf=IIC_Read_Byte(1);		//������,����ACK  
		len--;
		buf++; 
	}    
    IIC_Stop();	//����һ��ֹͣ���� 
	return 0;	
}

u8 Sing_Write_ND(u8 addr, u8 reg)
{
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(addr);//�����豸��ַ
	if(IIC_Wait_Ack()){IIC_Stop(); return 1;}
	IIC_Send_Byte(reg);//���Ͳ����Ĵ�����ַ
	IIC_Wait_Ack();
	IIC_Stop();
	_delay_ms(5);
	return 1;
}

u8 Sing_Read_NR(u8 addr, u8 len, u8 *buf)
{	
	IIC_Start(); 
	IIC_Send_Byte(addr+1);//����������ַ
	while(IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		IIC_Stop();		 
		return 1;		
	}
	while(len)
	{
		if(len==1)*buf=IIC_Read_Byte(0);//������,����nACK 
		else *buf=IIC_Read_Byte(1);		//������,����ACK  
		len--;
		buf++; 
	}    
    IIC_Stop();	//����һ��ֹͣ���� 
		_delay_ms(5);
	return 1;
}

