
#include <stm32f10x.h>

#include "briupDelay.h"
#include "briupI2C.h"

#include "protocol.h"

#include "briupUsart.h"
#include "briupZigbee.h"
#include "briupUsart3.h"

#include "briupGPIO.h"
#include "basePeripheral.h"

#include "pm2_5.h"
#include "sht20.h"

int main(void) {
	float tem, hum;
	int inttem, inthum;
	u16 pm25;
	u8 shtBuf[2], pmBuf[2];
	
	_delay_init(72);
	usart1Init(72, 57600);
	zigbeeInit(36, 57600);
	usart3Init(36, 9600);
	IIC_Init();
	
	briupGPIOInit();
	
	while(1) {
		pm25 = pm25Value();
		pmBuf[0] = ((u8)((pm25 & 0xff00) >> 8));
		pmBuf[1] = ((u8)(pm25 & 0x00ff));
		
		SHT20_Measure(&tem, &hum);
		inttem = (int)tem;
		inthum = (int)hum;
		shtBuf[0] = ((u8)(inttem & 0x00ff));
		shtBuf[1] = ((u8)(inthum & 0x00ff));
		
		//pm2.5 sensor ID -> 0x01
		protocolSendToRaspi(0x01, 0x02, pmBuf);
		_delay_sec(6);
		
		//sht20 sensor ID -> 0x02
		protocolSendToRaspi(0x02, 0x02, shtBuf);
		_delay_sec(6);
	
	}
}
