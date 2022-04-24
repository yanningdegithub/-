
#include <stm32f10x.h>
#include <stdio.h>

#include "protocol.h"

#include "briupDelay.h"

#include "briupUsart.h"
#include "briupZigbee.h"

#include "briupGPIO.h"
#include "basePeripheral.h"

#include "lock.h"
#include "keyboard.h"
#include "mini12864.h"
#include "figure.h"
#include "keyboard.h"

int main(void) {
	u8 stat;
	UserProt cmd;
	u8 ch, i, count[1];
	char sr[4], pw[4] = {0x01, 0x02, 0x03, 0x04}, buf[10];
	
	_delay_init(72);
	usart1Init(72, 57600);
	zigbeeInit(36, 57600);
	briupGPIOInit();
	
	Lock_Init();
	keyboardInit();
	figureInit();
	Lcd_Init_IN();
	
	addFigure();
	
	Clear_Screen_IN();
	showStrCn(3, 0, (u8*)"Choose");
//	sprintf(buf, "Choose\n");
//	putStr(buf);
	
	while(1) {
		
		

		ch = getKeyValue();
		if (ch != 0x20) {
			putChar(ch);
			switch(ch) {
				case 0x01:
					showStrCn(3, 0, (u8*)"Input:");
//					sprintf(buf, "Input\n");
//					putStr(buf);
					i = 0;
					do {
						ch = getKeyValue();
						count[0] = i + 0x31;
						if(ch != 0x20) {
							showStrCn(1,0,count);
//							putChar((u8)'*');
							sr[i] = ch;
							i++;
						}
					} while(i < 4);
					if(sr[0] == pw[0] &&
						 sr[1] == pw[1] &&
						 sr[2] == pw[2] &&
						 sr[3] == pw[3]) {
						showStrCn(3, 0, (u8*)"iRight");
//						sprintf(buf, "iRight\n");
//						putStr(buf);
						Lock_Open_Once();
					}
					else {
						showStrCn(3, 0, (u8*)"iWrong");
//						sprintf(buf, "iWrong\n");
//						putStr(buf);
					}
					break;
				case 0x02:
					showStrCn(3, 0, (u8*)"Origin");
//					sprintf(buf, "Origin\n");
//					putStr(buf);
					i = 0;
					do {
						ch = getKeyValue();
						count[0] = i + 0x31;
						if(ch != 0x20) {
							showStrCn(1,0,count);
//							putChar((u8)'*');
							sr[i] = ch;
							i++;
						}
					} while(i < 4);
					if(sr[0] == pw[0] &&
						 sr[1] == pw[1] &&
						 sr[2] == pw[2] &&
						 sr[3] == pw[3]) {
						showStrCn(3, 0, (u8*)"SetPwd");
//						sprintf(buf, "Set\n");
//						putStr(buf);
						i = 0;
						do {
							ch = getKeyValue();
							count[0] = i + 0x31;
							if(ch != 0x20) {
							showStrCn(1,0,count);
//							putChar((u8)'*');
								pw[i] = ch;
								i++;
							}
						} while(i < 4);
						showStrCn(3, 0, (u8*)"SetOK.");
//						sprintf(buf, "SetOK\n");
//						putStr(buf);
					}
					else {
						showStrCn(3, 0, (u8*)"oWrong");
//						sprintf(buf, "oWrong\n");
//						putStr(buf);
					}
					break;
				case 0x03:
				
					if(checkFigure() == 1) {
						Lock_Open_Once();
						Clear_Screen_IN();
					}
					
					break;
				default:
					break;
			}
//			memset(&cmd, 0, sizeof(UserProt));
		}

		stat = protocolRes(&cmd);
		
		if(stat != 1)
			putChar(stat);
		
		if(stat == 0){
			if(cmd.uDevId == 0x01 && cmd.uData[0] == 0x01) {
				Lock_Open_Once();
				_delay_ms(500);
			}
		}
		
		
	}		
}
