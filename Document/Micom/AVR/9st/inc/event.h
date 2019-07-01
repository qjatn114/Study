#ifndef _EVENT_H_
#define _EVENT_H_

#include "Type.h"

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

typedef void (*Event_Callback_t)(Event_t Event, uint16_t Arg);

void Event_Init(void);
void Event_RegisterCallBack(Event_t Event, uint16_t Arg, Event_Callback_t Callback);
void Event_RemoveCallBack(Event_t Event);
void Event_PutEvent(Event_t Event, uint16_t Arg);

void Event_Process(void);



#endif
