#include "Atmega128.h"
#include <avr/interrupt.h>
#include "Timer.h"

#define ALRAM_MIN_PERIOD 5

typedef struct
{
	Alarm_Handle_t Handle;
	uint16_t       Period;
	uint16_t       Cnt;
}Alram_State_t;

Alram_State_t Alram_Table[ALARM_MAX]={{NULL, 0, 0}, };
volatile uint16_t Delay_Cnt = 0;
//uint8_t Timer_Delay_Flag = 0;


void Timer_Init(void)
{
	/* Timer Init (5ms tick) */
	WGM01 = 1;  // 10 : CTC Mode
	WGM00 = 0;
	
	CS02 = 1;   // 110: clk/256
	CS01 = 1;
	CS00 = 0;
	
	OCR0 = 143; // 144-1 : 5ms tick
	OCIE0 = 1;  // Timer0 Interrupt Enable
}

void Alarm_Open(Alram_t Alram, uint16_t msPeriod, Alarm_Handle_t Handle)
{
	Alram_Table[Alram].Period = msPeriod;
	Alram_Table[Alram].Handle = Handle;
}

void Alarm_Close(Alram_t Alram)
{
	Alram_Table[Alram].Handle = NULL;
}

void Timer_msDelay(uint16_t msDelay)
{
	cli();
	Delay_Cnt = msDelay / ALRAM_MIN_PERIOD;
	sei();
	
	while(Delay_Cnt);
}

ISR(TIMER0_COMP_vect)
{
	uint8_t i;
	
	for(i=0; i<ALARM_MAX; i++)
	{
		if(Alram_Table[i].Handle)
		{
			Alram_Table[i].Cnt++;
			if(Alram_Table[i].Cnt*ALRAM_MIN_PERIOD >= Alram_Table[i].Period)
			{
				Alram_Table[i].Cnt = 0;
				Alram_Table[i].Handle();			
			}
		}
	}

	Delay_Cnt--;
}
