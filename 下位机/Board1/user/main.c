#include <stm32f10x.h>
#include <string.h>

#include "briupTim.h"
#include "briupDelay.h"

#include "briupUsart.h"
#include "briupZigbee.h"

#include "briupGPIO.h"
#include "basePeripheral.h"
#include "highLight.h"
#include "WS2812B.h"

#include "protocol.h"

int main(void) {
	u16 stat;
	UserProt cmd;
	u8 row, lightness;
	int i, j;
	
	//NVIC÷–∂œ∑÷◊È≈‰÷√
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	_delay_init(72);
	briupGPIOInit();
	usart1Init(72, 57600);
	zigbeeInit(36, 57600);
	timInit(72, 1000);
	
//	WS2812B_Init();
//	
//	for (i = 0; i < 4; i++) {
//		for (j = 0; j < 4; j++) {
//			pixBuf[i][j].green = 0x00;
//			pixBuf[i][j].red = 0x00;
//			pixBuf[i][j].blue = 0x00;		
//		}
//	}
//	ws2812SendData();
	
	lightSet(0x01,1);
	
	while(1) {
//		lightSet(ROW_ALL, 1);
		stat = protocolRes(&cmd);
//		if(stat != 0x01)
//			putChar(stat);
		if(stat == 0) { /////////////////////////////////////////
			switch(cmd.uDevId) {
				case 0x01:
					
					switch(cmd.uData[0]) {
						case 0x01:
							row = ROW_1;
							break;
						case 0x02:
							row = ROW_2;
							break;
						case 0x03:
							row = ROW_3;
							break;
						case 0x04:
							row = ROW_4;
							break;
						default:
							break;
					}
					
					lightness = cmd.uData[1];
					lightSet(row, lightness);
					break;
					
				case 0x03:
					
					baseLedSet(cmd.uData[0]);
				
					break;
				
				default:
					break;
			}
		}
		_delay_ms(1000);
	}
}
// highlight1 -> bb aa 00 ff ff 01 02 01 02 01 05 00 ee ff
// rgbled     -> bb aa 00 ff ff 01 02 03 01 03 00 ee ff
