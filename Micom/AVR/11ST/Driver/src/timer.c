#include "type.h"
#include "atmega128.h"
#include "timer.h"

#include <avr/interrupt.h>

/*
static Alarm_Handle_t Alarm_Handle[ALARM_MAX] = {NULL,};
static uint16_t msPeriod[ALARM_MAX] = 0;
uint16_t Count[ALARM_MAX] = 0;
*/
                                 
typedef struct{
	Alarm_Handle_t Alarm_Handle;
	uint16_t msPeriod;
	uint16_t Count;
}Alarm_State_t;

Alarm_State_t Alarm_Table[ALARM_MAX] = {{NULL,0,0},};
volatile uint16_t Delay_Count = 0;

void Timer_Init(void)
{
	/* 레지스터 초기화 (Timer0, CTC, 1/256, 5ms Interrupt) */
	WGM00 = 1;	//CTC
	WGM01 = 0;

	CS00 = 0;		// 110 : 1/256
	CS01 = 1;
	CS02 = 1;	

	OCR0 = 143;		// 143 : 5ms

	OCIE0 = 1;		// Enable Interrupt
}

void Alarm_Open(Alarm_t Alarm,uint16_t msPeriod,Alarm_Handle_t Handle)
{
	Alarm_Table[Alarm].Alarm_Handle = Handle;
	Alarm_Table[Alarm].msPeriod = msPeriod /5;
	Alarm_Table[Alarm].Count = 0;
}

void Alarm_Close(Alarm_t Alarm)
{
	Alarm_Table[Alarm].Alarm_Handle = NULL;
}

void Timer_msDelay(uint16_t msDelay)
{
	cli();			//인터럽트 정지
	Delay_Count = msDelay / 5;		//이때 인터럽트 못하게 하라
	sei();			//인터럽트 활성화
	while(Delay_Count);
}

ISR(TIMER0_COMP_vect)
{
	uint8_t i;
	for(i=0;i<ALARM_MAX;i++)
	{
		if(Alarm_Table[i].Alarm_Handle)
		{
			Alarm_Table[i].Count++;
			if(Alarm_Table[i].Count == Alarm_Table[i].msPeriod)
			{
				Alarm_Table[i].Alarm_Handle();
				Alarm_Table[i].Count = 0;
			}
		}
	}
	/*msDelay*/
	Delay_Count--;
}

