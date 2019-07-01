#include "type.h"
#include "atmega128.h"
#include "uart.h"
#include <avr/interrupt.h>


static UART_Handle_t UART_Handle = NULL;

void UART_Init(void)
{
	/* 레지스터 초기화 */
	U2X1 = 0;		//0 :16 sampling  1: 8sampling
	RXCIE1 = 1;		//Enable Interrupt
	RXEN1 = 1;
	TXEN1 = 1;
	
	UCSZ12 = 0;		//011 : Data 8 bit
	UCSZ11 = 1;
	UCSZ10 = 1;
	
	UPM11 = 0;		//00 : Parity None
	UPM10 = 0;

	USBS1 = 0;		//0 : Stopbit 1

	UBRR1H = 0;		// 3 : 115200bps
	UBRR1L = 3;
}

void UART_PutChar(uint8_t Data)
{
	/* UDR 비어있을 때 까지 기다림 */
	while(UDRE1 == 0);
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
	if(UART_Handle)
	{
		UART_Handle(UDR1);
	}

}

