#include "clock.h"
#include "event.h"
#include "Timer.h"
#include "Key.h"
#include "fnd.h"
#include "i2c.h"
#include "rtc.h"

typedef enum{
 	CLOCK_STATE_CLOCK_INIT,  /* �ð� �ʱ� ���� */
 	CLOCK_STATE_SETTIME_INIT,  /* �ð� ���� �ʱ� ���� */
 	CLOCK_STATE_SETTIME_MINUTE, /* �� ���� ����  */
 	CLOCK_STATE_SETTIME_SECOND, /* �� ���� ����  */
	CLOCK_STATE_STOPWATCH_INIT, /* �ʽð� �ʱ� ���� */
	CLOCK_STATE_STOPWATCH_RUN,  /* �ʽð� ���� ����  */
 	CLOCK_STATE_STOPWATCH_STOP  /* �ʽð� ���� ���� */
}Clock_State_t;

#define CLOCK_MODE_CLOCK    0
#define CLOCK_MODE_STOPWATCH  1

typedef struct{
 	Clock_State_t State;  // ������� 
 	uint8_t Mode;    // 0 : �ð��� ,1 : �ʽð� ��� 
 	Time_t Time;    // ����ð� 
 	uint16_t StopwatchTime;  // �ʽð� �ð� 
 	uint8_t TimeEnable;   // 0 : �ð� ����, 1 : �ð� ���� 
 	uint8_t StopwatchEnable; // 0 : �ʽð� ����, 1 : �ʽð� ����
 	uint8_t MinuteBlink;  // 1 : �б�����, 0 : �ȱ���  
 	uint8_t SecondBlink;  // 1 : �ʱ�����, 0 : �ȱ���   
}Clock_t;

typedef void (*STATE_FUNCTION)(void);

typedef struct{
 	Clock_State_t CurrentState;  /* ���� ���� */
 	Clock_State_t NextState;    /* ���� ���� */
 	Event_t Event;              /* �̺�Ʈ */
 	uint16_t Arg;
 	STATE_FUNCTION pFunction;  /* ���� ó���Լ� */
}Clock_State_Machine_t;

/* �̺�Ʈ ó�� �Լ�  */
static void Clock_100msCallback(Event_t Event, uint16_t Arg);
static void Clock_RTCCallback(Event_t Event, uint16_t Arg);
static void Clock_KeyCallback(Event_t Event, uint16_t Arg);

/* �ð� ǥ�� �Լ� */
static void Clock_Display(void);
static void Clock_DisplayClockTime(void);
static void Clock_DisplayStopwatchTime(void);

/* ���� ó�� �Լ� */
static void Clock_C0S0(void);
static void Clock_S0C0(void);
static void Clock_S0S1(void);
static void Clock_S2S1(void);
static void Clock_S1S2(void);
static void Clock_S2S0(void);
static void Clock_C0T0(void);
static void Clock_T0C0(void);
static void Clock_T0T1(void);
static void Clock_T1T0(void);
static void Clock_T1T2(void);
static void Clock_T2T1(void);
static void Clock_T2T0(void);
static void Clock_T0T2(void);
static void Clock_T1T1Up(void);
static void Clock_T1T1Down(void);
static void Clock_T2T2Up(void);
static void Clock_T2T2Down(void);


static uint8_t Clock_FindStateMachine(Clock_State_t CurState, Event_t Event, uint16_t Arg);


static void Clock_TimeUpdate(void);

Clock_t ClockStatus;

/* �ð� ���µ�  */
const Clock_State_Machine_t ClockStateMachine[] = {
 {CLOCK_STATE_CLOCK_INIT,     CLOCK_STATE_STOPWATCH_INIT,  EVENT_KEY,  KEY_LEFT,   Clock_C0S0},
 {CLOCK_STATE_CLOCK_INIT,     CLOCK_STATE_SETTIME_INIT,    EVENT_KEY,  KEY_RIGHT,  Clock_C0T0},
 {CLOCK_STATE_STOPWATCH_INIT, CLOCK_STATE_CLOCK_INIT,      EVENT_KEY,  KEY_UP,     Clock_S0C0},
 {CLOCK_STATE_STOPWATCH_INIT, CLOCK_STATE_STOPWATCH_RUN,   EVENT_KEY,  KEY_CENTER, Clock_S0S1},
 {CLOCK_STATE_STOPWATCH_RUN,  CLOCK_STATE_STOPWATCH_STOP,  EVENT_KEY,  KEY_CENTER, Clock_S1S2},
 {CLOCK_STATE_STOPWATCH_STOP, CLOCK_STATE_STOPWATCH_RUN,   EVENT_KEY,  KEY_CENTER, Clock_S2S1},
 {CLOCK_STATE_STOPWATCH_STOP, CLOCK_STATE_STOPWATCH_INIT,  EVENT_KEY,  KEY_UP,     Clock_S2S0},
 {CLOCK_STATE_SETTIME_INIT,   CLOCK_STATE_CLOCK_INIT,      EVENT_KEY,  KEY_UP,     Clock_T0C0},
 {CLOCK_STATE_SETTIME_INIT,   CLOCK_STATE_SETTIME_MINUTE,  EVENT_KEY,  KEY_LEFT,   Clock_T0T1},
 {CLOCK_STATE_SETTIME_INIT,   CLOCK_STATE_SETTIME_SECOND,  EVENT_KEY,  KEY_RIGHT,  Clock_T0T2},
 {CLOCK_STATE_SETTIME_MINUTE, CLOCK_STATE_SETTIME_INIT,    EVENT_KEY,  KEY_CENTER, Clock_T1T0},
 {CLOCK_STATE_SETTIME_MINUTE, CLOCK_STATE_SETTIME_SECOND,  EVENT_KEY,  KEY_RIGHT,  Clock_T1T2},  
 {CLOCK_STATE_SETTIME_SECOND, CLOCK_STATE_SETTIME_INIT,    EVENT_KEY,  KEY_CENTER, Clock_T2T0},
 {CLOCK_STATE_SETTIME_SECOND, CLOCK_STATE_SETTIME_MINUTE,  EVENT_KEY,  KEY_LEFT,   Clock_T2T1},
 {CLOCK_STATE_SETTIME_MINUTE, CLOCK_STATE_SETTIME_MINUTE,  EVENT_KEY,  KEY_UP,     Clock_T1T1Up},
 {CLOCK_STATE_SETTIME_MINUTE, CLOCK_STATE_SETTIME_MINUTE,  EVENT_KEY,  KEY_DOWN,   Clock_T1T1Down},  
 {CLOCK_STATE_SETTIME_SECOND, CLOCK_STATE_SETTIME_SECOND,  EVENT_KEY,  KEY_UP,     Clock_T2T2Up},
 {CLOCK_STATE_SETTIME_SECOND, CLOCK_STATE_SETTIME_SECOND,  EVENT_KEY,  KEY_DOWN,   Clock_T2T2Down},
 {0xFF, 0xFF, 0xFF, KEY_NOTHING, NULL}
};



void Clock_App(void)
{
	/* ������ �ʱ�ȭ */
	ClockStatus.State = CLOCK_STATE_CLOCK_INIT;
	ClockStatus.Mode  = CLOCK_MODE_CLOCK;
	ClockStatus.StopwatchTime = 0;
	ClockStatus.TimeEnable = 1;
	ClockStatus.StopwatchEnable = 0;
	ClockStatus.MinuteBlink = 0;
	ClockStatus.SecondBlink = 0;

	
	/* �̺�Ʈ ��� */
	Event_RegisterCallBack(EVENT_ALARM0,100,Clock_100msCallback);
	Event_RegisterCallBack(EVENT_ALARM1,1000,Clock_RTCCallback);
	Event_RegisterCallBack(EVENT_KEY,0,Clock_KeyCallback);
}

Time_t Clock_GetTime(void)
{
	Time_t Time;
	Time.Hour = ClockStatus.Time.Hour;
	Time.Minute = ClockStatus.Time.Minute;
	Time.Second = ClockStatus.Time.Second;
	return Time;
}

static void Clock_100msCallback(Event_t Event, uint16_t Arg)
{
	if(ClockStatus.StopwatchEnable == 1)
	{
		ClockStatus.StopwatchTime++;
	}
	
	Clock_Display();
}

static void Clock_RTCCallback(Event_t Event, uint16_t Arg)
{
	RTC_Time_t Time;

	if(ClockStatus.TimeEnable == 1)
	{
		RTC_GetTime(&Time);
		ClockStatus.Time.Hour = Time.Hour;
		ClockStatus.Time.Minute = Time.Minute;
		ClockStatus.Time.Second = Time.Second;
	}
}

static void Clock_KeyCallback(Event_t Event, uint16_t Arg)
{
	uint8_t StateNum;
	/* ���µ����� ��ġ�� ã�� */
	StateNum = Clock_FindStateMachine(ClockStatus.State, Event, Arg);

	/* ����ó���Լ� ���� */
	if(StateNum == 0xFF)
	{
		return;
	}

	if(ClockStateMachine[StateNum].pFunction)
	{
		ClockStateMachine[StateNum].pFunction();
	}	

	/* ���� ���¸� ���� ���·� */
	ClockStatus.State = ClockStateMachine[StateNum].NextState;
}


static void Clock_Display(void)
{
	if(ClockStatus.Mode == CLOCK_MODE_CLOCK)
 	{
  		Clock_DisplayClockTime();
 	}
 	else
 	{
  		Clock_DisplayStopwatchTime();
 	}
}

static void Clock_DisplayClockTime(void)
{
	if(ClockStatus.MinuteBlink == 1)
	{
		FND_On(10, 2, 1);
		FND_On(10, 3, 0);
	}

	if(ClockStatus.SecondBlink == 1)
	{
		FND_On(10, 0, 0);
		FND_On(10, 1, 0);
	}
	
	FND_Write( ClockStatus.Time.Second%10,    0, 0); //   1��
	FND_Write((ClockStatus.Time.Second/10)%6, 1, 0); // 10��
	FND_Write((ClockStatus.Time.Minute%10),   2, 1); //  1��
	FND_Write((ClockStatus.Time.Minute/10)%6, 3, 0); // 10��
}

static void Clock_DisplayStopwatchTime(void)
{
	FND_Write( ClockStatus.StopwatchTime%10,      0, 0);
	FND_Write((ClockStatus.StopwatchTime/10)%10,  1, 1);
	FND_Write((ClockStatus.StopwatchTime/100)%6,  2, 0);
	FND_Write((ClockStatus.StopwatchTime/600)%10, 3, 1);
}


static void Clock_C0S0(void)
{
	ClockStatus.Mode = CLOCK_MODE_STOPWATCH;
}

static void Clock_S0C0(void)
{
	ClockStatus.Mode = CLOCK_MODE_CLOCK;
}

static void Clock_S0S1(void)
{
	ClockStatus.StopwatchEnable = 1;
}

static void Clock_S2S1(void)
{
	ClockStatus.StopwatchEnable = 1;
}

static void Clock_S1S2(void)
{
	ClockStatus.StopwatchEnable = 0;
}

static void Clock_S2S0(void)
{
	ClockStatus.StopwatchTime = 0;
}

static void Clock_C0T0(void)
{
	ClockStatus.TimeEnable = 0;
}

static void Clock_T0C0(void)
{
	RTC_Time_t Time;
	RTC_GetTime(&Time);
	Time.Minute = ClockStatus.Time.Minute;
	Time.Second = ClockStatus.Time.Second;
	RTC_SetTime(Time);
	ClockStatus.TimeEnable = 1;
}

static void Clock_T0T1(void)
{
	ClockStatus.MinuteBlink = 1;
}

static void Clock_T1T0(void)
{
	ClockStatus.MinuteBlink = 0;
}

static void Clock_T1T2(void)
{
	ClockStatus.MinuteBlink = 0;
	ClockStatus.SecondBlink = 1;
}

static void Clock_T2T1(void)
{
	ClockStatus.MinuteBlink = 1;
	ClockStatus.SecondBlink = 0;
}

static void Clock_T2T0(void)
{
	ClockStatus.SecondBlink = 0;
}

static void Clock_T0T2(void)
{
	ClockStatus.SecondBlink = 1;
}

static void Clock_T1T1Up(void)
{
	ClockStatus.Time.Minute = (ClockStatus.Time.Minute + 1) % 60;
}

static void Clock_T1T1Down(void)
{
	if(ClockStatus.Time.Minute == 0)
	{
		ClockStatus.Time.Minute = 59;
	}
	else
	{
		ClockStatus.Time.Minute--;
	}
}

static void Clock_T2T2Up(void)
{
	ClockStatus.Time.Second = (ClockStatus.Time.Second + 1) % 60;
}

static void Clock_T2T2Down(void)
{
	if(ClockStatus.Time.Second == 0)
	{
		ClockStatus.Time.Second = 59;
	}
	else
	{
		ClockStatus.Time.Second--;
	}
}


static uint8_t Clock_FindStateMachine(Clock_State_t CurState, Event_t Event, uint16_t Arg)
{
	uint8_t i;
  
 	for(i = 0; ClockStateMachine[i].CurrentState != 0xFF; i++)
 	{
   		if((ClockStateMachine[i].CurrentState == CurState) &&
    	   (ClockStateMachine[i].Event == Event) && 
    	   (ClockStateMachine[i].Arg == Arg))
   		{
     		return i;  /* ã�� */
   		}
	}
 	return 0xFF; /* ��ã�� */
}


static void Clock_TimeUpdate(void)
{
}

