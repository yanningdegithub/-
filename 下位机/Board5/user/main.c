
#include <stm32f10x.h>

#include "briupDelay.h"

#include "protocol.h"

#include "briupUsart.h"
#include "briupZigbee.h"
#include "briupUsart3.h"

#include "briupGPIO.h"
#include "basePeripheral.h"

#include "alarm.h"
#include "oeSwitch.h"

int main(void) {
	UserProt cmd;
	u8 stat;
	
	_delay_init(72);
	usart1Init(72, 57600);
	zigbeeInit(36, 57600);
	briupGPIOInit();
	
	oeSwitchInit();
	alarmInit();
	
	while(1) {

//		_delay_ms(1000);
//		oppoSwitchAlarm();
//		rvseSwitchAlarm();
		
		stat = protocolRes(&cmd);
		if(stat == 0) {
			//zigbeeSendBuf((u8*)&stat, 1);
			putChar(stat);
			//putChar(cmd.uCheck);
			if(cmd.uDevId == 0x01 && cmd.uData[0] == 0x01)
				alarmAction();
		}
	}
}
