#ifndef _EXTINT_H_
#define _EXTINT_H_

#include "Type.h"

typedef void (*ExtInt_Handle_t)(void);

void ExtInt_Init(void);
uint8_t ExtInt_Check(void);
void ExtInt_Open(ExtInt_Handle_t Handle);
void ExtInt_Close(void);


#endif
