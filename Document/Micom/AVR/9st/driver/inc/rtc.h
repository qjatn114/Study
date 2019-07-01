#ifndef _RTC_H_
#define _RTC_H_

#include "type.h"

typedef struct{
	uint8_t Second;
	uint8_t Minute;
	uint8_t Hour;
	uint8_t Day;
	uint8_t Month;
	uint16_t Year;
}RTC_Time_t;



void RTC_Init(void);
uint8_t RTC_GetTime(RTC_Time_t *Time);
void RTC_SetTime(RTC_Time_t Time);


#endif 

