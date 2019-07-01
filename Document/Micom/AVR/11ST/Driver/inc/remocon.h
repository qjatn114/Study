#ifndef _REMOCON_H_
#define _REMOCON_H_

#include "type.h"

typedef enum{
 REMOCON_UP = 0x12,
 REMOCON_DOWN = 0x10,
 REMOCON_LEFT = 0x0B,
 REMOCON_RIGHT = 0x07,
 REMOCON_CENTER = 0x1A
}Remocon_Code_t;

typedef void (*Remocon_Handle_t)(Remocon_Code_t Code);

void Remocon_Init(void);
void Remocon_Open(Remocon_Handle_t Handle);
void Remocon_Close(void);








#endif
