#ifndef _EXTINT_H_
#define _EXTINT_H_

typedef void (*ExtInt_Handle_t)(void);

void Extint_Init(void);
uint8_t Extint_Check(void);
void ExtInt_Open(ExtInt_Handle_t Handle);
void ExtInt_Close(void);



#endif
