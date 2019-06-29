#ifndef _UART_H_
#define _UART_H_

#include "type.h"

typedef void(*UART_Handle_t)(uint16_t Data);

void UART_Init(void);
void UART_PutChar(uint8_t Data);
void UART_PutString(const char *String);
void UART_Open(UART_Handle_t Handle);
void UART_Close(void);





#endif
