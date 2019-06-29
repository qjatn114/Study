#ifndef _EVENT_H_
#define _EVENT_H_

#include "type.h"

typedef enum{
 EVENT_ALARM0,
 EVENT_ALARM1,
 EVENT_ALARM2,
 EVENT_ALARM3,
 EVENT_KEY,
 EVENT_UART,
 EVENT_VOLUME,
 EVENT_TEMP,
 EVENT_BRIGHT,
 EVENT_REMOCON,
 EVENT_MAX 
}Event_t;

typedef void (*Event_Callback_t)(Event_t Event,uint16_t Arg);

void Event_Init(void);
void Event_RegisterCallback(Event_t Event,uint16_t Arg,Event_Callback_t Callback);
void Event_RemoveCallback(Event_t Event);
void Event_Process(void);			// App로 back주는 함수
void Event_PutEvent(Event_t Event,uint16_t Arg);

#endif
