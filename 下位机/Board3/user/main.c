
#include <stm32f10x.h>

#include "briupDelay.h"
#include "briupTim.h"

#include "briupUsart.h"
#include "briupZigbee.h"
#include "briupUsart3.h"

#include "briupGPIO.h"
#include "basePeripheral.h"

#include "infrared.h"
#include "methane.h"
#include "smoke.h"
#include "fire.h"

#include "protocol.h"

int main(void) {
	u8 buf[2] = {0x00, 0x00};
	
	_delay_init(72);
	timInit(72, 1000);
	usart1Init(72, 57600);
	zigbeeInit(36, 57600);
	briupGPIOInit();
	infraredInit();
	methaneInit();
	smokeInit();
	fireInit();
	
	
	while(1) {
		//putChar(infraredStat());
		//putChar(methaneStat());
		//putChar(smokeStat());
		//putChar(fireStat());
		
		_delay_sec(7);
		buf[1] = infraredStat();
		protocolSendToRaspi(0x03, 0x04, 0x02, buf);
	}
}
