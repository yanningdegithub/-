
#ifndef _LOCK_H_
#define _LOCK_H_

#include <stm32f10x.h>

#define LOCK_CONTROL			PBxOut(8)				//�������������

void Lock_Init(void);

void Lock_Open_Once(void);

#endif
