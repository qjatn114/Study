#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "type.h"

typedef struct{
 uint8_t Hour;
 uint8_t Minute;
 uint8_t Second;
}Time_t;


void Clock_App(void);
Time_t Clock_GetTime(void);








#endif
