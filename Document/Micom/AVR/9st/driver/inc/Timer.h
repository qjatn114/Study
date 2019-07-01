#ifndef _TIMER_H_
#define _TIMER_H_

#include "Type.h"

typedef enum
{
	ALARM0,
	ALARM1,
	ALARM2,
	ALARM3,
	ALARM4,
	ALARM_MAX
}Alram_t;

typedef void (*Alarm_Handle_t)(void);

void Timer_Init(void);
void Alarm_Open(Alram_t Alram, uint16_t msPeriod, Alarm_Handle_t Handle);
void Alarm_Close(Alram_t Alram);
void Timer_msDelay(uint16_t msDelay);


#endif
