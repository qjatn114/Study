#ifndef _KEY_H_
#define _KEY_H_

typedef enum{
	KEY_NOTHING,
	KEY_RIGHT,		
	KEY_UP,
	KEY_CENTER,
	KEY_LEFT,
	KEY_DOWN
}KEY_CODE;

typedef void (*KEY_HANDLE)(KEY_CODE Key);

void Key_Init(void);
KEY_CODE Key_GetKey(void);

#endif
