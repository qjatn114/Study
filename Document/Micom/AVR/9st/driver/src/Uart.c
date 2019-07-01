#include "Atmega128.h"
#include <avr/interrupt.h>

#include "Uart.h"


uint8_t UARTInt_Flag = 0;
uint8_t UART_Buffer = 0;

UART_Handle_t UART_Handle = NULL;


void UART_Init(void)
{
	/* 115200bps, Data : 8bit, Stop : 1bit, Parity : None */
	RXCIE1 = 1; // Enable RXC Interrupt
	RXEN1 = 1;
	TXEN1 = 1;
	
	UCSZ12 = 0; // 8bit
	UCSZ11 = 1;
	UCSZ10 = 1;

	UMSEL1 = 0; // 0 : 비동기, 1 : 동기

	UPM11 = 0; // 00 : Parity None
	UPM10 = 0;

	USBS1 = 0; // 0 : Stopbit 1bit

	UBRR1H = 0; // 115200bps at 7.3728MHz
	UBRR1L = 3;
}

void UART_PutChar(uint8_t Data)
{
	while(UDRE1 == 0); // 빌때까지 기다림
	
	UDR1 = Data;
}

void UART_PutString(const char *String)
{
	while(*String)
	{
		UART_PutChar(*String);
		String++;
	}
}

uint8_t UART_GetChar(uint8_t *Data)
{
	if(UARTInt_Flag)
	{
		*Data = UART_Buffer;
		UARTInt_Flag = 0;
		return 1;
	}
	else
	{
		return 0;
	}	
}

void UART_Open(UART_Handle_t Handle)
{
	UART_Handle = Handle;
}

void UART_Close(void)
{
	UART_Handle = NULL;
}

ISR(USART1_RX_vect)
{
	UART_Buffer = UDR1;
	UARTInt_Flag = 1;
	
	if(UART_Handle)
	{
		UART_Handle(UART_Buffer);
	}
}

