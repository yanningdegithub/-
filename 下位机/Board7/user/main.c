#include <stm32f10x.h>

#include "protocol.h"

#include "briupDelay.h"

#include "briupUsart.h"
#include "briupZigbee.h"

#include "briupGPIO.h"
#include "basePeripheral.h"

#include "a4988.h"
#include "miniFan.h"

int main(void) {
	u8 stat;
	u8 buf[1];
	UserProt cmd;
	
	_delay_init(72);
	usart1Init(72, 57600);
	zigbeeInit(36, 57600);
	briupGPIOInit();
	A4988_Init();
	miniFanInit();
	
	while(1) {
		stat = protocolRes(&cmd);
		if(stat == 0) {
			//putChar(stat);
			if(cmd.uDevId == 0x01) {
				setMiniFan(cmd.uData[0]);
			}
			else if(cmd.uDevId == 0x03) {
				Motor_Control(1800, 380, cmd.uData[0]);
			}
			_delay_ms(1000);
		}
		
//		buf[0] = 0; // avoid going up unstopable
//		getBuffer(buf, 0);
//		
//		if(buf[0] == '1') {
//			Motor_Control(1800, 380, 1);
//			setMiniFan(1);
//	//			putStr("qwedf");
//			_delay_ms(1000);
//		}

//		else if(buf[0] == '0') {
//			Motor_Control(1800, 380, 0);
//			setMiniFan(0);
//			_delay_ms(1000);
//		}
	}
}
