
#include "figure.h"
#include "briupUsart.h"
#include "briupDelay.h"
#include "mini12864.h"
#include "basePeripheral.h"
//===================================�����ǲ���Ҫ�о��Ķ���=====================================
//�����������ݵĻ����������
static volatile u8 usart3Buffer[256];
//����ͷ������β
static volatile u16 buf3Head, buf3Tail;
static volatile u16 buf3Count = 0;
u32 SaveNumber=0; 
u32 searchnum=0;
u32 SearchNumber=0;	
void usart3Init( u8 pclk, u32 baud);
void usart3DmaPut( u8 * buf, u16 len);
u16 usart3GetBuffer(u8 * buf);

//��֤�豸���ֿ��� ������16�����ش�12���ֽ�
unsigned char  VPWD[16]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};	

//̽����ָ����Ӵ������϶���ͼ��   ����12���ֽڣ��ش�12��
unsigned char  GIMG[12]={0xef,0x01,0xff,0xff,0xff,0xff, 0x01,0x00,0x03,0x01,0x00,0x05};

//����ԭʼͼ������ָ������  ����13 ���ش�12
unsigned char  GENT1[13]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x04,0x02,0x01,0x00,0x08};

//����ԭʼͼ������ָ������2�� ����13 �ش�12
unsigned char  GENT2[13]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x04,0x02,0x02,0x00,0x09}; 

//��charbuffera��charbufferb�е������ļ����������򲿷�ָ�ƿ�  ��17 �� 16
unsigned char  SEAT[17]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x03,0xe7,0x00,0xf8};

//��charbuffera��charbufferb�е�ָ�������ļ��ϲ�����ģ�壬����ModelBuffer��  ��12��12
unsigned char  MERG[12]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x05,0x00,0x09};

//��ModelBuffer2�е��ļ��浽flashָ�ƿ���  �� 15 �� 12
unsigned char  STOR[15]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x06,0x06,0x02,0x00,0x00,0x00,0x0f};

//���ָ�ƿ�    �� 12  ��  12
unsigned char  DELE_all[12]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x0d,0x00,0x11};

u8 VefPSW(void);
u8 ImgProcess(u8 BUFID);
u8 search(void);
u8 savefingure(u32 ID);
u8 enroll(void);

//===================================�����ǲ���Ҫ�о��Ķ���=====================================




void figureInit(void)
{
	usart3Init( 36, 9600);
	_delay_ms(100);
	
}

u8 addFigure(void)
{
	Clear_Screen_IN();//ȫ����
	
	if(VefPSW()==1)
	{
		showStrCn(1,0,(u8*)" ���ֳɹ�");
		baseBeepSet(1);
		_delay_ms(500);
		baseBeepSet(0);
	//��������
	}
	if(SaveNumber<162)
	{
		_delay_ms(50);
		baseBeepSet(1);
		_delay_ms(500);
		baseBeepSet(0);
		Clear_Screen_IN();
		showStrCn(3,0,(u8*)" �밴����ָ");
		_delay_sec(4);

		if(enroll()==1)
		{
			_delay_ms(500);
			Clear_Screen_IN();
			showStrCn(3,0,(u8*)" ¼�����");
			showStrCn(3,0,(u8*)" ���ɿ���ָ");
			_delay_ms(2000);
			if(savefingure(SaveNumber+1)==1)
			{
				Clear_Screen_IN();
				showStrCn(3,0,(u8*)" �洢�ɹ�");
				SaveNumber++;
				_delay_ms(100);
				baseBeepSet(1);
				_delay_ms(100);
				baseBeepSet(0);
				_delay_sec(3);	
			}
		}
	}
	return 0;
}

u8 checkFigure(void)
{
	Clear_Screen_IN();
	_delay_ms(500);
				baseBeepSet(1);
	_delay_ms(500);
				baseBeepSet(0);
	Clear_Screen_IN();
	showStrCn(3,0," �밴����ָ");
	_delay_ms(2000);			
	searchnum = search();
	if(searchnum>=1&&searchnum<=1000)
	{
				baseBeepSet(1);
		_delay_ms(500);
				baseBeepSet(0);
		Clear_Screen_IN();
		showStrCn(1,0," ʶ��ɹ�");
		showStrCn(3,0," ��ӭ����");
		//LOCK_CONTROL=1;
		_delay_ms(3000);
		return 1;
	}
	else if(searchnum==0)
	{
		Clear_Screen_IN();
		showStrCn(1,0," ʶ��ʧ��");
				baseBeepSet(1);
		_delay_ms(100);
				baseBeepSet(0);
		_delay_ms(100);
				baseBeepSet(1);
		_delay_ms(100);
				baseBeepSet(0);
		_delay_ms(3000);
		//LOCK_CONTROL=0;
		return 0;
	}
}


//=====================================�������ǲ���Ҫ�о��Ķ���=========================================

u8 VefPSW(void)
{
	u8 len, buf[100];
	usart3DmaPut(VPWD, 16);
	do
	{
		len = usart3GetBuffer( buf);
	}while(len == 0);
	
	if(buf[9]==0x00){
		return 0;//��ʾ������֤��ȷ
	}else if(buf[9]==0x01){
		return 2;//��ʾ�հ��д�
	}else {
		return 3;//��ʾ�����ȷ
	}
}

u8 ImgProcess(u8 BUFID)
{
	u8 len, buf[100];
	usart3DmaPut(GIMG, 12);
	do
	{
		len = usart3GetBuffer( buf);
	}while(len == 0);
	if(buf[9]==0x00)
	{
			if(BUFID==1)
			{
				usart3DmaPut(GENT1, 13);
				do
				{
					len = usart3GetBuffer( buf);
				}while(len == 0);
				if(buf[9]==0x00){
					return 1;//�ɹ�
				}
				else
				{
					return 0;//ʧ��
				}
			}
			else if(BUFID==2)
			{
				usart3DmaPut(GENT2, 13);
				do
				{
					len = usart3GetBuffer( buf);
				}while(len == 0);
				if(buf[9]==0x00){
					return 1;//�ɹ�
				}
				else
				{
					return 0;//ʧ��
				}
			}
		
	}else if(buf[9]==0x01)
	{
		return 2;//��ʾ�հ��д�
	}else if(buf[9]==0x02)
	{
		return 3;//��ʾ������������ָ
	}else if(buf[9]==0x03)
	{
		return 4;
	}
	return 0;
}

u8 search(void)
{
	u8 i=0;
	u8 len, buf[100];
	while(i<20)
	{
		usart3DmaPut(GIMG, 12);
		do
		{
			len = usart3GetBuffer( buf);
		}while(len == 0);
		if(buf[9] == 0x00)
		{
			usart3DmaPut(GENT1, 13);
			do
			{
				len = usart3GetBuffer( buf);
			}while(len == 0);
			if(buf[9] == 0x00)
			{
				usart3DmaPut(SEAT, 17);
				do
				{
					len = usart3GetBuffer( buf);
				}while(len == 0);
				if(buf[9] == 0x00)
					return (buf[10]<<8)|buf[11];
				else if(buf[9] == 0x09)
				{
					return 0;
				}
			}
		}
		i++;
	}
	return 0;
}

u8 savefingure(u32 ID)
{
	u8 i=0;
	u32 sum=0;
	u8 FIFO[80]={0};
	u8 len, buf[100];
	
	for(i=0;i<15;i++)
	{
		FIFO[i]=STOR[i];
	}
	
	FIFO[11]=ID/256;
	FIFO[12]=ID%256;
	
	for(i=6;i<13;i++)
	{
		sum= sum + FIFO[i];
	}
	
	FIFO[13]=sum/256;
	FIFO[14]=sum%256;
	
	usart3DmaPut( FIFO, 15);
	do
	{
		len = usart3GetBuffer( buf);
	}while(len == 0);
	if(buf[9]==0x00)
	{
		return 1;//�洢�ɹ�
	}
	else
	{
		return 0;
	}
}

u8 enroll(void)
{
	u8 temp = 0, count = 0;
	u8 len, buf[100];
	putDataDma((u8*)"��ʼ�ɼ�ָ��...", 15);
	while(1)
	{
		Clear_Screen_IN();
		showStrCn(3,0,(u8*)" ��ʼ¼��");
		_delay_ms(1000);
		temp=ImgProcess(1);
		if(temp==1)
		{
			Clear_Screen_IN();
			showStrCn(3,0,(u8*)" ��һ�βɼ��ɹ�");
			count=0;
			//�ɼ���һ�������ɹ�
			baseBeepSet( 1);
			_delay_ms(100);
			baseBeepSet( 0);
			_delay_ms(2000);
			break;
		}
		else
		{
			if(temp==2)
			{
				Clear_Screen_IN();
				showStrCn(3,0,(u8*)"�ɼ�ʧ��");
				showStrCn(5,0,(u8*)"��������");
				_delay_ms(1000);
				count++;
				if(count>=40)
					return 0;
			}
			else if(temp ==3)
			{
				Clear_Screen_IN();
				showStrCn(3,0,(u8*)" �ɼ�ʧ��");
				showStrCn(5,0,(u8*)"������������ָ");
				_delay_ms(1000);
				count++;
				if(count>=40)
					return 0;
			}
			else if(temp==4)
			{
				Clear_Screen_IN();
				showStrCn(3,0,(u8*)" �ɼ�ʧ��");
				showStrCn(5,0,(u8*)"ָ������������");
				_delay_ms(1000);
				count++;
				if(count>=40)
					return 0;
			}
		}
	}
	_delay_ms(1000);
	while(1)
	{
		Clear_Screen_IN();
		showStrCn(3,0,(u8*)" ��ʼ¼��");
		_delay_ms(1000);
		temp = ImgProcess(2);
		if(temp==1)
		{
			Clear_Screen_IN();
			showStrCn(3,0,(u8*)" �ڶ��βɼ��ɹ�");
			_delay_ms(2000);
			usart3DmaPut( MERG, 12);
			do
			{
				len = usart3GetBuffer( buf);
			}while( len == 0);
			if(buf[9]==0x00)
			{	
				Clear_Screen_IN();
				showStrCn(3,0,(u8*)" �ϳ�ģ��ɹ�");
				baseBeepSet(1);
				_delay_ms(100);
				baseBeepSet(0);
				_delay_ms(100);
				baseBeepSet(1);
				_delay_ms(100);
				baseBeepSet(0);
				_delay_ms(2000);
				return 1;
			}
			else
			{
				Clear_Screen_IN();
				showStrCn(3,0,(u8*)" �ϳ�ʧ��");
				_delay_ms(1000);
				return 0;
			}
		}
		else
		{
			if(temp==2)
			{
				Clear_Screen_IN();
				showStrCn(3,0,(u8*)" �ɼ�ʧ��");
				showStrCn(5,0,(u8*)"��������");
				_delay_ms(1000);
				count++;
				if(count>=25)
					return 0;
			}
			else if(temp ==3)
			{
				Clear_Screen_IN();
				showStrCn(3,0,(u8*)" �ɼ�ʧ��");
				showStrCn(5,0,(u8*)"������������ָ");
				_delay_ms(1000);
				count++;
				if(count>=25)
					return 0;
			}
			else if(temp==4)
			{
				Clear_Screen_IN();
				showStrCn(3,0,(u8*)" �ɼ�ʧ��");
				showStrCn(5,0,(u8*)"ָ������������");
				_delay_ms(1000);
				count++;
				if(count>=25)
					return 0;
			}
			else 
				return 0;
		}
	}
}

//����3��ʼ�������ӿ�
//	pclk:�����ʱ��Ƶ��	MHz
//	baud:Ŀ�겨����
void usart3Init( u8 pclk, u32 baud)
{
	NVIC_InitTypeDef nvic_init;
	//����DIV��������ֵ
	double usartdiv = (pclk * 1000000.0)/(16 * baud);
	u16 mant = (u16)usartdiv;
	u16 frac = (usartdiv - mant) * 16;
	mant = mant<<4 | (frac & 0x0f);
	
	//����USART3��GPIOB��ʱ��
	//	Tx -> PB10
	//	Rx -> PB11
	RCC->APB2ENR |= 1<<3;	//GPIOB
	RCC->APB1ENR |= 1<<18;	//USART3
	
	//����GPIO�ĸ��ù���ģʽ
	GPIOB->CRH &= ~0x0000FF00;
	GPIOB->CRH |=  0x00008B00;
	GPIOB->ODR |= 1<<11;	//PB11��������
	
	//����USART������
	USART3->BRR = mant;
	//13->����EN 3->TxEN 2->RxEN  5->�����ж�EN
	USART3->CR1 |= 1<<13 | 1<<3 | 1<<2 | 1<<5;
	USART3->CR3 |= 1<<7;
	
	DMA1_Channel2->CPAR = (u32)&USART3->DR;
	DMA1_Channel2->CMAR = 0;	//ʹ��ʱ����
	DMA1_Channel2->CNDTR = 0; //��������0
	DMA1_Channel2->CCR = 0;
	DMA1_Channel2->CCR |= 1<<13 | 1<<7 | 1<<4;
	
	nvic_init.NVIC_IRQChannel = USART3_IRQn;
	nvic_init.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_init.NVIC_IRQChannelSubPriority = 3;
	nvic_init.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &nvic_init);
}

u16 usart3GetBuffer(u8 * buf)
{
	//�����һ�λ�ȡ���Ļ���������
	//ת�Ƶ�buf�У����ƶ�������ͷ��
	u16 temp, i, head = buf3Head;
	u16 lenH = (head + 7)%256;
	u16 lenL = (lenH + 1)%256;
	vu16 length = 0;
	while(1)
	{
		if( length == 0)
			length = usart3Buffer[lenH] << 8 | usart3Buffer[lenL];
		if( length != 0)
		{
			temp = buf3Count;
			if( temp < length + 9)
				continue;
			else
				break;
		}
		_delay_ms(1);
	}
	buf3Count = 0;
	for( i = 0;i < temp;i ++)
	{
		*buf = usart3Buffer[buf3Head];
		buf ++;
		buf3Head ++;
		buf3Head %= 256;
	}
	return temp;
}

//ͨ��DMA����buf��ָ������(len)������
//	buf -> Դ��ַ
//	len -> ����
void usart3DmaPut(u8 * buf, u16 len)
{
	DMA1_Channel2->CCR &= ~0x01;
	DMA1_Channel2->CMAR = (u32)buf;
	DMA1_Channel2->CNDTR = len;
	DMA1_Channel2->CCR |= 0x01;
}


//==============�жϵķָ���==================
//USART�����жϴ������
void USART3_IRQHandler(void)
{
	u8 temp = 0;
	if( USART3->SR & (1<<5))
	{
		temp = USART3->DR;
		usart3Buffer[buf3Tail] = temp;
		buf3Tail ++;
		buf3Tail %= 256;
		buf3Count ++;
	}
}
