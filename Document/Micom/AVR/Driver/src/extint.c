#include "type.h"
#include "atmega128.h"
#include "extint.h"
#include <avr/interrupt.h>


static uint8_t Extint_Flag = 0;	//0 : NonPushed , 1: Pushed
static ExtInt_Handle_t ExtInt_Handle = NULL;		//주소값이 없다.


void Extint_Init(void)
{
	/* 레지스터 초기화 ( INT 4, Falling edge ) */
	ISC41 = 1;		// 1 0 : Falling Edge
	ISC40 = 0;
	INT4 =1;		// Enable Interrupt
	
}

uint8_t Extint_Check(void)
{
	if(Extint_Flag)
	{
		Extint_Flag = 0;
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
	Extint_Flag = 1;

	if(ExtInt_Handle)
	{
		ExtInt_Handle();
	}
}
