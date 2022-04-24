
#include <stm32f10x.h>

#include "briupDelay.h"
#include "briupI2C.h"

#include "protocol.h"

#include "briupUsart.h"
#include "briupZigbee.h"
#include "briupUsart3.h"

#include "briupGPIO.h"
#include "basePeripheral.h"

#include "sht20.h"
#include "BH1750.h"
#include "veml6070.h"
#include "CO2.h"

//#include "stdio.h"


int main(void) {	
	u8 setlight[2] = {0x01, 0x00};
	float tem, hum, light;
	u16 veml;
	u8 co2h, co2l;
	u8 zbBuf[2];

	int inttem, inthum, intlight;
	
	_delay_init(72);
	usart1Init(72, 57600);
	zigbeeInit(36, 57600);
	usart3Init(36, 9600);
	IIC_Init();
	
	briupGPIOInit();
	
	BH1750_Init();
	VEML6070Init();

	while(1) {
//		sprintf(buf,"%.0f%.0f", tem, hum);

// Bu Yong Ban 2 De Wen Shi Du
//		//=============================================SHT20
//		SHT20_Measure(&tem, &hum); // t, h
//		
//		//transmute to int
//		inttem = (int)tem;
//		//putChar((u8)(inttem & 0x00ff));
//		
//		inthum = (int)hum;
//		//putChar((u8)(inthum & 0x00ff));
//		
//		zbBuf[0] = (u8)(inttem & 0x00ff);
//		zbBuf[1] = (u8)(inthum & 0x00ff);
//		
////		putBuffer(zbBuf, 14);
////		zigbeeSendBuf(zbBuf, 14);
//		protocolSendToRaspi(0x02, 0x04, 0x02, zbBuf);
			
		//=============================================BH1750
		BH1750_Measure(&light);
		
		//环境300+，最大109225，设定上限9999
		if(light > 9999) light = 9999;
				
		//transmute to int, max is 27 0F (9999)
		intlight = (int)light;
		
		//putChar((u8)((intlight & 0xff00) >> 8));
		//putChar((u8)(intlight & 0x00ff));
		
		
		zbBuf[0] = (u8)((intlight & 0xff00) >> 8);
		zbBuf[1] = (u8)(intlight & 0x00ff);
		
		putChar(zbBuf[0]);
		putChar(zbBuf[1]);
		
		protocolSendToRaspi(0x03, 0x04, 0x02, zbBuf);
		
		if(intlight > 0x05dc) {
			protocolSendToBoard(0x01, 0x01, 0x02, setlight);
		}
		
		_delay_sec(5);
		
		//=============================================VEML
		VEML6070Measure(&veml);
		
		//环境3+，最大2149，设定上限9999
		if(veml > 9999) veml = 9999;
		
		//max is 27 0F (9999)
		zbBuf[0] = (u8)((veml & 0xff00) >> 8);
		zbBuf[1] = (u8)(veml & 0x00ff);
		protocolSendToRaspi(0x04, 0x04, 0x02, zbBuf);
		_delay_sec(5);
		
		//=============================================CO2
		CO2_Measure(&co2h, &co2l);
		
		//max is 13 88 (5000)
		zbBuf[0] = co2h;
		zbBuf[1] = co2l;
		protocolSendToRaspi(0x01, 0x04, 0x02, zbBuf);
		_delay_sec(5);
	}
	
}



