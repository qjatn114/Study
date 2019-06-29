#include "Atmega128.h"
#include "Type.h"
#include <avr/interrupt.h>
#include "ExtInt.h"

uint8_t ExtInt_Flag = 0; // 0 : 안눌림, 1 : 눌림
ExtInt_Handle_t ExtInt_Handle = NULL;


void ExtInt_Init(void)
{
	/* External Interrupt 4 Enable */
	ISC41 = 1; // 10: Falling edge
	ISC40 = 0;
	INT4 = 1; // Interrupt Enable
}


uint8_t ExtInt_Check(void)
{
	if(ExtInt_Flag)
	{
		ExtInt_Flag = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

void ExtInt_Open(ExtInt_Handle_t Handle)
{
	ExtInt_Handle = Handle;
}

void ExtInt_Close(void)
{
	ExtInt_Handle = NULL;
}



ISR(INT4_vect)
{
	ExtInt_Flag = 1;
	
	if(ExtInt_Handle)
	{
		ExtInt_Handle();
	}	
}
