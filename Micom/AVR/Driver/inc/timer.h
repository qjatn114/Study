#ifndef _TIMER_H_
#define _TIMER_H_


typedef enum{
	ALARM0,
	ALARM1,
	ALARM2,
	ALARM3,
	ALARM_MAX
}Alarm_t;

typedef void (*Alarm_Handle_t)(void);

void Timer_Init(void);
void Alarm_Open(Alarm_t Alarm,uint16_t msPeriod,Alarm_Handle_t Handle);
void Alarm_Close(Alarm_t Alarm);
void Timer_msDelay(uint16_t msDelay);

#endif
