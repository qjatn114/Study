#ifndef _KEY_H_
#define _KEY_H_

#include "type.h"


typedef enum{
 KEY_NOTHING,
 KEY_RIGHT,
 KEY_UP,
 KEY_CENTER,
 KEY_LEFT,
 KEY_DOWN
}Key_t;

typedef void (*Key_Handle_t)(Key_t Key);

void KEY_Init(void);
void KEY_Open(Key_Handle_t Handle);
void KEY_Close(void);





#endif
