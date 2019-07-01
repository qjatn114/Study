#include "Atmega128.h"
#include <avr/interrupt.h>
#include "Type.h"
#include "led.h"
#include "fnd.h"
#include "ExtInt.h"
#include "lcd.h"
#include "Uart.h"
#include "Timer.h"
#include "ADC.h"
#include "Key.h"
#include "Remocon.h"
#include "event.h"


static void Init(void);
static void Delay(uint32_t Times);
static void Key_Count_Polling(void);
static void Key_Count_Callback(void);

static void UART_Polling(uint8_t *data);
static void UART_Callback(uint8_t Data);

static void UART_Control_Polling(void);
static void UART_Control_Callback(uint8_t Data);

static void StopWatch_Display_Callback(void);

static void UART_Control_Callback2(uint8_t Data);

static void StopWatch_Display_Callback2(Event_t Event, uint16_t Arg);

static void ADC_Trigger(Event_t Event, uint16_t Arg);

static void ADC_CH0_Callback(uint16_t Data); 

static void ADC_CH1_Callback(Event_t Event, uint16_t ADCValue);
static void ADC_CH2_Callback(Event_t Event, uint16_t ADCValue);
static void ADC_CH3_Callback(Event_t Event, uint16_t ADCValue);

/*static void ADC_CH1_Callback(uint16_t ADCValue);
static void ADC_CH2_Callback(uint16_t ADCValue);
static void ADC_CH3_Callback(uint16_t ADCValue);*/

static void Key_Callback(Event_t Event, uint16_t Arg);

static void REMOCON_Callback(Remocon_Code_t Code);

static void Snake_App(Event_t Event, uint16_t Arg);





const uint8_t LED_Pattern[8] = {0x00, 0x81, 0x42, 0x24, 0x18, 0x55, 0xAA, 0xFF};

void LED_Blink(void);

uint16_t StopWatch_Data = 0;

int main(void)
{
	uint8_t data;
	uint8_t *pdata = &data;
	Init();

	LED_On(0xAA);
	FND_Write(0, 0, 0);
	FND_Write(1, 1, 0);
	FND_Write(2, 2, 0);
	FND_Write(3, 3, 0);

	UART_PutChar('A');
	UART_PutChar('B');
	UART_PutChar('C');
	UART_PutChar('D');
	UART_PutString("\r\n====================");
	UART_PutString("\r\n== Atmega128 Test ==");
	UART_PutString("\r\n====================");

	LCD_FillColor(0, 160, 30, 320,BLACK);
 	LCD_FillColor(29, 160, 30, 320,WHITE);
 	LCD_FillColor(59, 160, 30, 320,YELLOW);
 	LCD_FillColor(89, 160, 30, 320,RED);
 	LCD_FillColor(119, 160, 30, 320,GREEN);
 	LCD_FillColor(149, 160, 30, 320,BLUE);
 	LCD_FillColor(179, 160, 30, 320,CYAN);
 	LCD_FillColor(209, 160, 30, 320,MAGENTA); 


 	LCD_WriteString(10, 10,"ABCDEFG 솔루션 공과 전자학원",YELLOW, BLUE);
 	LCD_DrawRect(100, 100, 200, 200, 0, RED);
 	LCD_DrawCircle(120, 160, 100, 0, CYAN);
	
	
	//ExtInt_Open(Key_Count_Callback);
	//UART_Open(UART_Callback);
	UART_Open(UART_Control_Callback2);
	//Alarm_Open(ALARM0, 100, StopWatch_Display_Callback);
	//UART_Open(UART_Control_Callback);
	//Alarm_Open(ALARM1, 100, ADC_Trigger);

	Event_RegisterCallBack(EVENT_ALARM1,100,ADC_Trigger);

	Event_RegisterCallBack(EVENT_VOLUME,0,ADC_CH1_Callback);
	Event_RegisterCallBack(EVENT_TEMP,0,ADC_CH2_Callback);
	Event_RegisterCallBack(EVENT_BRIGHT,0,ADC_CH3_Callback);
	
	//ADC_Open(1, ADC_CH1_Callback);
	//ADC_Open(2, ADC_CH2_Callback);
	//ADC_Open(3, ADC_CH3_Callback);

	Event_RegisterCallBack(EVENT_KEY,0,Key_Callback);

	//Key_Open(Key_Callback);
	//Remocon_Open(Snake_App);
	Event_RegisterCallBack(EVENT_REMOCON,0,Snake_App);

	sei();
	
	while(1)
	{
		Event_Process();
	}
}

static void Init(void)
{
	/* 드라이버 초기화 */
	LED_Init();
	FND_Init();
	ExtInt_Init();
	UART_Init();
	Timer_Init();
	ADC_Init();
	LCD_Init();
	Key_Init();
	Remocon_Init();
	Event_Init();
}

static void Delay(uint32_t Times)
{
	volatile uint32_t i;

	for(i = 0; i < Times; i++);
}

void LED_Blink(void)
{
	uint8_t i;
	for(i=0; i<sizeof(LED_Pattern); i++)
	{
		LED_On(LED_Pattern[i]);
		Timer_msDelay(500);
		//Delay(100000);
	}
}

static void Key_Count_Polling(void)
{
	static uint16_t Count = 0;
	if(ExtInt_Check() == 0)//안룰림
		return;

	Count++;

	/* FND 표시 */
	
	FND_Write(Count%10, 0, 0);
	FND_Write((Count/10)%10, 1, 0);
	FND_Write((Count/100)%10, 2, 0);
	FND_Write((Count/1000)%10, 3, 0);
}

static void Key_Count_Callback(void)
{
	static uint16_t Count = 0;

	Count++;

	/* FND 표시 */
	
	FND_Write(Count%10, 0, 0);
	FND_Write((Count/10)%10, 1, 0);
	FND_Write((Count/100)%10, 2, 0);
	FND_Write((Count/1000)%10, 3, 0);
}

static void UART_Polling(uint8_t *data)
{
	if(UART_GetChar(data))
	{
		UART_PutChar(*data);
	}
}

static void UART_Callback(uint8_t Data)
{
	UART_PutChar(Data);
}

static void UART_Control_Polling(void)
{
	uint8_t Data;
	
	if(UART_GetChar(&Data) == 0)
		return;

	FND_Write(Data%10, 0, 0);
	FND_Write((Data/10)%10, 1, 0);
	FND_Write((Data/100)%10, 2, 0);
	FND_Write((Data/1000)%10, 3, 0);

}

static void UART_Control_Callback(uint8_t Data)
{
	FND_Write(Data%10, 0, 0);
	FND_Write((Data/10)%10, 1, 0);
	FND_Write((Data/100)%10, 2, 0);
	FND_Write((Data/1000)%10, 3, 0);
}

static void StopWatch_Display_Callback(void)
{
	static uint16_t Data = 0;
	Data++;
	FND_Write(Data%10, 0, 0);
	FND_Write((Data/10)%10, 1, 1);
	FND_Write((Data/100)%6, 2, 0);
	FND_Write((Data/600)%10, 3, 1);
}

static void UART_Control_Callback2(uint8_t Data)
{
	switch(Data)
	{
		case 0: // stop
			Alarm_Close(ALARM0);
			break;

		case 1: // start
			Alarm_Open(ALARM0, 100, StopWatch_Display_Callback2);
			break;

		case 2: // reset
			cli();
			StopWatch_Data = 0;
			FND_Write(0, 0, 0);
			FND_Write(0, 1, 1);
			FND_Write(0, 2, 0);
			FND_Write(0, 3, 1);
			sei();
			break;

		default:
			break;
	} 
}

static void StopWatch_Display_Callback2(Event_t Event, uint16_t Arg)
{
	StopWatch_Data++;
	FND_Write(StopWatch_Data%10, 0, 0);
	FND_Write((StopWatch_Data/10)%10, 1, 1);
	FND_Write((StopWatch_Data/100)%6, 2, 0);
	FND_Write((StopWatch_Data/600)%10, 3, 1);
}

static void ADC_CH0_Callback(uint16_t Data)
{
}


static void ADC_CH1_Callback(Event_t Event, uint16_t ADCValue)
{
	LCD_WriteString(  10, 100,"가변저항:",YELLOW, BLUE);
	LCD_WriteEnglish(90 + 8, 100, ADCValue / 1000 % 10 + '0' , YELLOW, BLUE);
 	LCD_WriteEnglish(90 + 16, 100, ADCValue / 100 % 10 + '0' , YELLOW, BLUE);
 	LCD_WriteEnglish(90 + 24, 100, ADCValue / 10 % 10 + '0' , YELLOW, BLUE);
 	LCD_WriteEnglish(90 + 32, 100, ADCValue  % 10 + '0' , YELLOW, BLUE);
}

static void ADC_CH2_Callback(Event_t Event, uint16_t ADCValue)
{
	LCD_WriteString(  10, 120,"온    도:",YELLOW, BLUE);
	LCD_WriteEnglish(90 + 8, 120, ADCValue / 1000 % 10 + '0' , YELLOW, BLUE);
 	LCD_WriteEnglish(90 + 16, 120, ADCValue / 100 % 10 + '0' , YELLOW, BLUE);
 	LCD_WriteEnglish(90 + 24, 120, ADCValue / 10 % 10 + '0' , YELLOW, BLUE);
 	LCD_WriteEnglish(90 + 32, 120, ADCValue  % 10 + '0' , YELLOW, BLUE);
}

static void ADC_CH3_Callback(Event_t Event, uint16_t ADCValue)
{
	LCD_WriteString(  10, 140,"밝    기:",YELLOW, BLUE);
	LCD_WriteEnglish(90 + 8, 140, ADCValue / 1000 % 10 + '0' , YELLOW, BLUE);
 	LCD_WriteEnglish(90 + 16, 140, ADCValue / 100 % 10 + '0' , YELLOW, BLUE);
 	LCD_WriteEnglish(90 + 24, 140, ADCValue / 10 % 10 + '0' , YELLOW, BLUE);
 	LCD_WriteEnglish(90 + 32, 140, ADCValue  % 10 + '0' , YELLOW, BLUE);
}

static void ADC_Trigger(Event_t Event, uint16_t Arg)
{
	static uint8_t Channel = 0;
	Channel++;
	if(Channel == 4)
	{
		Channel = 1;
	}
	ADC_Start(Channel);
}

static void Key_Callback(Event_t Event, uint16_t Arg)
{

	uint8_t data;
	LCD_WriteString(  10, 80,"키    값:",YELLOW, BLUE);
	switch(Arg)
	{
		case KEY_RIGHT:
			data = 'R';	
			break;

		case KEY_UP:
			data = 'U';
			Event_RegisterCallBack(EVENT_ALARM0,100,StopWatch_Display_Callback2);
			break;

		case KEY_CENTER:
			data = 'C';
			Event_RemoveCallBack(EVENT_ALARM0);
			break;

		case KEY_LEFT:
			data = 'L';
			break;

		case KEY_DOWN:
			data = 'D';
			cli();
			StopWatch_Data = 0;
			FND_Write(0, 0, 0);
			FND_Write(0, 1, 1);
			FND_Write(0, 2, 0);
			FND_Write(0, 3, 1);
			sei();
			break;	

		default:
			data = 'N';
			break;
				
	}
	LCD_WriteEnglish(90 + 8, 80, data , YELLOW, BLUE);
}

static void REMOCON_Callback(Remocon_Code_t Code)
{
	uint8_t data;
	LCD_WriteString(  10, 60,"리모콘값:",YELLOW, BLUE);
	switch(Code)
	{
		case REMOCON_RIGHT:
			data = 'R';	
			break;

		case REMOCON_UP:
			data = 'U';
			Alarm_Open(ALARM0, 100, StopWatch_Display_Callback2);
			break;

		case REMOCON_CENTER:
			data = 'C';
			Alarm_Close(ALARM0);
			break;

		case REMOCON_LEFT:
			data = 'L';
			break;

		case REMOCON_DOWN:
			data = 'D';
			cli();
			StopWatch_Data = 0;
			FND_Write(0, 0, 0);
			FND_Write(0, 1, 1);
			FND_Write(0, 2, 0);
			FND_Write(0, 3, 1);
			sei();
			break;	

		default:
			data = 'N';
			break;
				
	}
	LCD_WriteEnglish(90 + 8, 60, data , YELLOW, BLUE);
}

typedef struct{
 uint16_t X;
 uint16_t Y;
}Snake_t;


#define SNAKE_LENGTH 10


Snake_t Snake[SNAKE_LENGTH] ={{0,0}, };


static void Snake_App(Event_t Event, uint16_t Arg)
{
 static uint8_t SnakeHead = 0;
 uint16_t X, Y;


 X = Snake[SnakeHead].X;
 Y = Snake[SnakeHead].Y;
 /* 새로운 머리의 좌표 계산 */
 switch(Arg)
 {
  case REMOCON_UP :
   Y -= 10;
   break;
  case REMOCON_DOWN:
   Y += 10;
   break;
  case REMOCON_LEFT:
   X -= 10;
   break;
  case REMOCON_RIGHT:
   X += 10; 
   break;
  default:
   return;
 }
 /* 새로운 머리 위치로 이동 */
 SnakeHead++;
 SnakeHead %= SNAKE_LENGTH;
 /* 새로운 머리 좌표 저장 */
 Snake[SnakeHead].X = X;
 Snake[SnakeHead].Y = Y;
 /* 뱀을 그린다. */
 // 꼬리를 지운다 
 LCD_FillColor(Snake[(SnakeHead + 1) % SNAKE_LENGTH].X,Snake[(SnakeHead + 1) % SNAKE_LENGTH].Y , 10, 10, BLACK);
 // 머리를 그린다. 
 LCD_FillColor(Snake[SnakeHead].X, Snake[SnakeHead].Y, 10, 10, YELLOW);
}


