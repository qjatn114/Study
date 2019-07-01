#ifndef _KEY_H_
#define _KEY_H_

#include "Type.h"

typedef enum
{
	KEY_NOTHING,
	KEY_RIGHT,
	KEY_UP,
	KEY_CENTER,
	KEY_LEFT,
	KEY_DOWN,
}Key_t;

typedef void (*Key_Handle_t)(Key_t Key);

void Key_Init(void);
void Key_Open(Key_Handle_t Handle);
void Key_Close(void);

#endif
