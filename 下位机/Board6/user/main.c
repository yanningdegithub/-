
#include <stm32f10x.h>

#include "protocol.h"

#include "briupDelay.h"

#include "briupUsart.h"
#include "briupZigbee.h"

#include "briupGPIO.h"
#include "basePeripheral.h"

#include "servo.h"

int main(void) {	
	UserProt cmd;
	u8 stat;
	
	_delay_init(72);
	usart1Init(72, 57600);
	zigbeeInit(36, 57600);
	briupGPIOInit();	
	
	Servo_Init(20000, 100);
	
	while(1) {
		stat = protocolRes(&cmd);
		
//		if(stat != 1)
//			putChar(stat);
		
		if(stat == 0) {
			if(cmd.uDevId == 0x01) {
				switch (cmd.uData[0]) {
					case 0x00:
						Servo_Init(20000, 100);
						break;
					case 0x1e:
						Servo_Init(20000, 80);
						break;
					case 0x3c:
						Servo_Init(20000, 60);
						break;
					case 0x5a:
						Servo_Init(20000, 40);
						break;
					default:
						break;
				}
			}
			_delay_ms(1000);
		}
	}

//	Servo_Init(20000, 100);
//	_delay_sec(1.5);
//	
//	Servo_Init(20000, 80);
//	_delay_sec(1.5);
//	
//	Servo_Init(20000, 60);
//	_delay_sec(1.5);
//	
//	Servo_Init(20000, 40);
//	_delay_sec(1.5);
//	
//	Servo_Init(20000, 100);
//	_delay_sec(1.5);
			
////	Servo_ON();
//	_delay_sec(1.5);
//	
////	Servo_OFF();
//	_delay_sec(1.5);

}
