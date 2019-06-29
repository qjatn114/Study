#include "uart.h"
#include "timer.h"
#include "adc.h"
#include "keyy.h"
#include "remocon.h"


#include "type.h"
#include "event.h"

#define EVENT_BUFFER_SIZE  128


typedef struct{
 Event_t buf[EVENT_BUFFER_SIZE];
 uint16_t arg[EVENT_BUFFER_SIZE];
 uint8_t top;
 uint8_t bottom;
 uint8_t count;
}Event_Buffer_t;


static uint8_t Event_GetEvent(Event_t *Event, uint16_t *Arg);
/* 드라이버 콜백 함수 */

static void Event_Alarm0Callback(void);
static void Event_Alarm1Callback(void);
static void Event_Alarm2Callback(void);
static void Event_Alarm3Callback(void);
static void Event_KeyCallback(Key_t Key);
static void Event_UARTCallback(uint8_t Data);
static void Event_VolumeCallback(uint16_t Data);
static void Event_TempCallback(uint16_t Data);
static void Event_BrightCallback(uint16_t Data);
static void Event_RemoconCallback(Remocon_Code_t Code);


Event_Buffer_t EventBuf;
Event_Callback_t EventCallbackTable[EVENT_MAX] = {NULL,  };



void Event_Init(void)
{
	EventBuf.top = 0;
	EventBuf.bottom = 0;
	EventBuf.count = 0;
}

void Event_RegisterCallback(Event_t Event,uint16_t Arg,Event_Callback_t Callback)
{
	switch(Event)
	 {
	  case EVENT_ALARM0 :
	   Alarm_Open(ALARM0, Arg, Event_Alarm0Callback);
	   break;
	  case EVENT_ALARM1 :
	   Alarm_Open(ALARM1, Arg, Event_Alarm1Callback);
	   break;
	  case EVENT_ALARM2 :
	   Alarm_Open(ALARM2, Arg, Event_Alarm2Callback);
	   break;
	  case EVENT_ALARM3 :
	   Alarm_Open(ALARM3, Arg, Event_Alarm3Callback);
	   break;
	  case EVENT_KEY :
	   KEY_Open(Event_KeyCallback);
	   break;
	  case EVENT_UART :
	   UART_Open(Event_UARTCallback);
	   break;
	  case EVENT_VOLUME :
	   ADC_Open(1, Event_VolumeCallback);
	   break;
	  case EVENT_TEMP :
	   ADC_Open(2, Event_TempCallback);
	   break;
	  case EVENT_BRIGHT :
	   ADC_Open(3, Event_BrightCallback);
	   break;
	  case EVENT_REMOCON:
	   Remocon_Open(Event_RemoconCallback);
	   break;  
	  default :
	   break;
	 }


	 EventCallbackTable[Event] = Callback;
}

void Event_RemoveCallback(Event_t Event)
{
	//Close
}

void Event_Process(void)
{
	Event_t  Event;
	uint16_t  Arg;
	/* Event 빼오기 */
	if(Event_GetEvent(&Event,&Arg)==0)
		return;

	/* Back 한다 */
	if(EventCallbackTable[Event])
	{
		EventCallbackTable[Event](Event,Arg);
	}
}

void Event_PutEvent(Event_t Event,uint16_t Arg)
{
	EventBuf.buf[EventBuf.top] = Event;
	EventBuf.arg[EventBuf.top] = Arg;

	EventBuf.top = (EventBuf.top +1) % EVENT_BUFFER_SIZE;	//RingBuffer
	EventBuf.count++;
	if(EventBuf.count > EVENT_BUFFER_SIZE)
	{
		EventBuf.bottom = EventBuf.top;
		EventBuf.count = EVENT_BUFFER_SIZE;
	}
}

static uint8_t Event_GetEvent(Event_t *Event, uint16_t *Arg)
{
	if(EventBuf.count == 0)
	{
		return 0;
	}
	*Event = EventBuf.buf[EventBuf.bottom];
	*Arg = EventBuf.arg[EventBuf.bottom];

	EventBuf.bottom = (EventBuf.bottom +1) % EVENT_BUFFER_SIZE;		//RingArg
	EventBuf.count--;

	return 1;


	
}

static void Event_Alarm0Callback(void)
{
	Event_PutEvent(EVENT_ALARM0,0);
}
static void Event_Alarm1Callback(void)
{
	Event_PutEvent(EVENT_ALARM1,0);
}

static void Event_Alarm2Callback(void)
{
	Event_PutEvent(EVENT_ALARM2,0);

}

static void Event_Alarm3Callback(void)
{
	Event_PutEvent(EVENT_ALARM3,0);

}

static void Event_KeyCallback(Key_t Key)
{
	Event_PutEvent(EVENT_KEY ,Key);

}

static void Event_UARTCallback(uint8_t Data)
{
	Event_PutEvent(EVENT_UART ,Data);
}

static void Event_VolumeCallback(uint16_t Data)
{
	Event_PutEvent(EVENT_VOLUME,Data);
}

static void Event_TempCallback(uint16_t Data)
{
	Event_PutEvent(EVENT_TEMP,Data);
}

static void Event_BrightCallback(uint16_t Data)
{
	Event_PutEvent(EVENT_BRIGHT,Data);
}

static void Event_RemoconCallback(Remocon_Code_t Code)
{
	Event_PutEvent(EVENT_REMOCON,Code);
}


