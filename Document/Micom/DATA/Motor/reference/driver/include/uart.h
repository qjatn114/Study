#ifndef _UART_H_
#define _UART_H_

void UART_Init(void);
void UART_WriteByte(unsigned char Data);
void UART_WriteHexa(unsigned char Data);
void UART_WriteDecimal(unsigned short Data);
void UART_WriteString(const char *Data);
unsigned char UART_GetData(unsigned char *Data);


#endif 
