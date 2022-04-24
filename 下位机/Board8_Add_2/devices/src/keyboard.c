#include "keyboard.h"
#include "briupDelay.h"
#include "briupUsart.h"
volatile u8 keyValue =0;

void keyboardInit(void)
{
	NVIC_InitTypeDef nvic_init;
	
	RCC->APB2ENR|=1<<4 | 1<<0;
	GPIOC->CRH&=0xff0fffff;
	GPIOC->CRH|=0x00800000;
	
	AFIO->EXTICR[3] &= ~(0x0F << 4);
	AFIO->EXTICR[3] |= 0x02<<4;
	
	EXTI->RTSR |= 1<<13;
	EXTI->FTSR &= ~(1<<13);
	EXTI->IMR |= 1<<13;
	
	nvic_init.NVIC_IRQChannel = EXTI15_10_IRQn;
	nvic_init.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_init.NVIC_IRQChannelSubPriority = 0;
	nvic_init.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &nvic_init);
	_delay_ms(10);
	IIC_M_Init();
	_delay_ms(10);
}

u8 getKeyValue(void)
{
	u8 temp = keyValue;
	keyValue = 0x20;
	return temp;
}


//�ⲿ�жϷ������
void EXTI15_10_IRQHandler(void)
{ 
	EXTI->PR=1<<13;  //���LINE�ϵ��жϱ�־λ  
	IIC_M_Start();
	IIC_M_Send_Byte(0XBA);
	if(IIC_M_Wait_Ack()){IIC_M_Stop(); return ;}
	keyValue = IIC_M_Read_Byte(0);
	IIC_M_Stop();
	EXTI->PR=1<<13;  //���LINE�ϵ��жϱ�־λ 
}





//============================================================

//��ʼ��IIC
void IIC_M_Init(void)
{					     
	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��	   	  
	GPIOB->CRL&=0XFFFFFF00;
	GPIOB->CRL|=0X00000033;//PB0/PB1����������� 
	IIC_M_SCL_H();
	IIC_M_SDA_H();
}
//����IIC��ʼ�ź�
void IIC_M_Start(void)
{
	//SDA_M_OUT();     //sda�����
	IIC_M_SDA_H();	  	  
	IIC_M_SCL_H();
	_delay_us(4);
 	IIC_M_SDA_L();//START:when CLK is high,DATA change form high to low 
	_delay_us(4);
	IIC_M_SCL_L();//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_M_Stop(void)
{
	SDA_M_OUT();//sda�����
	IIC_M_SCL_L();
	IIC_M_SDA_L();//STOP:when CLK is high DATA change form low to high
 	_delay_us(4);
	IIC_M_SCL_H(); 
	_delay_us(1);
	IIC_M_SDA_H();//����I2C���߽����ź�
	_delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_M_Wait_Ack(void)
{
	u16 ucErrTime=0;
	SDA_M_IN();      //SDA����Ϊ����  
	IIC_M_SDA_H();_delay_us(1);	   
	IIC_M_SCL_H();_delay_us(1);	
	while(READ_M_SDA)
	{
		ucErrTime++;
		if(ucErrTime>2500)
		{
			//IIC_Stop();
			return 1;
		}
	}
	IIC_M_SCL_L();//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_M_Ack(void)
{
	IIC_M_SCL_L();
	SDA_M_OUT();
	IIC_M_SDA_L();
	_delay_us(2);
	IIC_M_SCL_H();
	_delay_us(2);
	IIC_M_SCL_L();
}
//������ACKӦ��		    
void IIC_M_NAck(void)
{
	IIC_M_SCL_L();
	SDA_M_OUT();
	IIC_M_SDA_H();
	_delay_us(2);
	IIC_M_SCL_H();
	_delay_us(2);
	IIC_M_SCL_L();
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��		  
void IIC_M_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_M_OUT(); 	    
    IIC_M_SCL_L();//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {
		if( txd & 0x80)
			IIC_M_SDA_H();
		else
			IIC_M_SDA_L();
		
        txd<<=1; 	  
		_delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_M_SCL_H();
		_delay_us(2); 
		IIC_M_SCL_L();	
		_delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_M_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_M_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_M_SCL_L(); 
        _delay_us(2);
				IIC_M_SCL_H();
        receive<<=1;
        if(READ_M_SDA)receive++;   
				_delay_us(1); 
    }	
    if (!ack)
        IIC_M_NAck();//����nACK
    else
        IIC_M_Ack(); //����ACK   
    return receive;
}

