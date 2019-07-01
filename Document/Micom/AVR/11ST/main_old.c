#include "led.h"
#include "type.h"
#include "fnd.h"
#include "extint.h"
#include "uart.h"
#include "timer.h"
#include "adc.h"
#include "lcd.h"
#include "keyy.h"
#include "remocon.h"
#include "event.h"

#include <avr/interrupt.h>

static void Init(void);
static void Delay(uint32_t Times);
static void Key_Count_Polling(void);
static void Key_Count_Callback(void);
static void UART_Count_Callback(uint16_t Data);
static void StopWatch_Display(void);
//static void Volume_Callback(uint16_t ADCValue);
//static void Bright_Callback(uint16_t ADCValue);
//static void Temp_Callback(uint16_t ADCValue);
static void Volume_Callback(Event_t Event,uint16_t ADCValue);
static void Bright_Callback(Event_t Event,uint16_t ADCValue);
static void Temp_Callback(Event_t Event,uint16_t ADCValue);

static void ADC_Trigger(void);
static void KEY_Control(Key_t Key);
static void Snake_App(Remocon_Code_t Code);

const uint8_t LED_Pattern[] = {0x00,0x81,0x42,0x24,0x18,0x55,0x44,0xff};
static uint16_t Time;
static uint8_t Time_Flag = 0;
int main(void)
{
	uint8_t i;
	
	Init();

	LED_On(0x13);
	FND_Write(0,0,0);
	FND_Write(1,1,0);
	FND_Write(2,2,0);
	FND_Write(3,3,0);

	UART_PutChar('A');
	UART_PutChar('B');
	UART_PutChar('C');
	UART_PutChar('D');
	UART_PutString("\r\n=====================");
	UART_PutString("\r\n======ATmega128======");
	UART_PutString("\r\n=====================");

	LCD_FillColor(0, 160, 30, 320,BLACK);
	LCD_FillColor(29, 160, 30, 320,WHITE);
	LCD_FillColor(59, 160, 30, 320,YELLOW);
	LCD_FillColor(89, 160, 30, 320,RED);
	LCD_FillColor(119, 160, 30, 320,GREEN);
	LCD_FillColor(149, 160, 30, 320,BLUE);
	LCD_FillColor(179, 160, 30, 320,CYAN);
	LCD_FillColor(209, 160, 30, 320,MAGENTA); 


	LCD_WriteString(10, 10,"ABCDEFG 솔루션 공과 전자학원",YELLOW, BLUE);
	LCD_WriteEnglish(10,26,'1',YELLOW,BLUE);
	LCD_WriteEnglish(18,26,'2',YELLOW,BLUE);
	LCD_WriteEnglish(26,26,'3',YELLOW,BLUE);
	LCD_WriteEnglish(34,26,'4',YELLOW,BLUE);
	LCD_DrawRect(100, 100, 200, 200, 0, RED);
	LCD_DrawCircle(120, 160, 100, 0, CYAN);

	Alarm_Open(ALARM0,100,StopWatch_Display);
	UART_Open(UART_Count_Callback);
//	ExtInt_Open(Key_Count_Callback);
	Alarm_Open(ALARM1,100,ADC_Trigger);
//	ADC_Open(1,Volume_Callback);	//가변저항
//	ADC_Open(3,Bright_Callback);	//밝기
//	ADC_Open(2,Temp_Callback);		//온도

	Event_RegisterCallback(EVENT_VOLUME,0,Volume_Callback);
	Event_RegisterCallback(EVENT_BRIGHT,0,Bright_Callback);
	Event_RegisterCallback(EVENT_TEMP,0,Temp_Callback);


	KEY_Open(KEY_Control);
	Remocon_Open(Snake_App);
	
	sei();		//Global Interrupt Enable
	while(1)
	{
		Event_Process();

	}
}


static void Init(void)
{
	/*드라이버 초기화*/
	LED_Init();
	FND_Init();
	Extint_Init();
	UART_Init();
	Timer_Init();
	LCD_Init();
	ADC_Init();
	KEY_Init();
	Remocon_Init();
	Event_Init();
}

static void Delay(uint32_t Times)
{
	volatile uint32_t j;

	for(j=0;j < Times;j++);
}

static void Key_Count_Polling(void)
{
	static uint16_t Count = 0;
	
	/* 눌렸는지 확인 */
	if(Extint_Check()== 0)
		return;
	
	/* 카운터 증가 */
	Count++;

	/* FND 표시 */
	FND_Write(Count % 10,0,0);					// 1의 자리
	FND_Write(Count/10 %10,1,0);				// 10의 자리
	FND_Write(Count / 100 % 10,2,0);			// 100의 자리
	FND_Write(Count / 1000 % 10,3,0);			// 1000의 자리
}

static void Key_Count_Callback(void)
{
	static uint16_t Count = 0;
	
	/* 카운터 증가 */
	Count++;

	/* FND 표시 */
	FND_Write(Count % 10,0,0);					// 1의 자리
	FND_Write(Count/10 %10,1,0);				// 10의 자리
	FND_Write(Count / 100 % 10,2,0);			// 100의 자리
	FND_Write(Count / 1000 % 10,3,0);			// 1000의 자리
}

static void UART_Count_Callback(uint16_t Data)
{
	switch(Data)
	{
		case 0:			//stop
			Time_Flag = 0;
			break;
		case 1:			//start
			Time_Flag = 1;
			break;
		case 2:			//reset
			Time_Flag = 0;
			Time = 0;
			break;
		default :
			break;
	}
	/* FND 표시 */
/*	FND_Write(Data % 10,0,0);					// 1의 자리
	FND_Write(Data/10 %10,1,0);				// 10의 자리
	FND_Write( Data/ 100 % 10,2,0);			// 100의 자리
	FND_Write( Data/ 1000 % 10,3,0);			// 1000의 자리
	*/
}

static void StopWatch_Display(void)
{
	if(Time_Flag)
	{
		Time++;
	}
		/* FND 표시 */
	FND_Write(Time      % 10,0,0);				// 0.1초
	FND_Write(Time/ 10  %10,1,0);				// 1초 자리
	FND_Write(Time/ 100 % 6,2,0);			// 10초 자리
	FND_Write(Time/ 600 % 10,3,0);			// 1분의 자리
}

//static void Volume_Callback(uint16_t ADCValue)
static void Volume_Callback(Event_t Evnt,uint16_t ADCValue)
{
	LCD_WriteString(10, 100, "가변저항:" , YELLOW, BLUE);
 	LCD_WriteEnglish(90 + 8, 100, ADCValue / 1000 % 10 + '0' , YELLOW, BLUE);
 	LCD_WriteEnglish(90 + 16, 100, ADCValue / 100 % 10 + '0' , YELLOW, BLUE);
 	LCD_WriteEnglish(90 + 24, 100, ADCValue / 10 % 10 + '0' , YELLOW, BLUE);
 	LCD_WriteEnglish(90 + 32, 100, ADCValue  % 10 + '0' , YELLOW, BLUE);
}

//static void Bright_Callback(uint16_t ADCValue)
static void Bright_Callback(Event_t Evnt,uint16_t ADCValue)

{
	LCD_WriteString(10, 116, "밝    기:" , YELLOW, BLUE);
	LCD_WriteEnglish(90 + 8, 116, ADCValue / 1000 % 10 + '0' , YELLOW, BLUE);
	LCD_WriteEnglish(90 + 16, 116, ADCValue / 100 % 10 + '0' , YELLOW, BLUE);
	LCD_WriteEnglish(90 + 24, 116, ADCValue / 10 % 10 + '0' , YELLOW, BLUE);
	LCD_WriteEnglish(90 + 32, 116, ADCValue  % 10 + '0' , YELLOW, BLUE);

}

//static void Temp_Callback(uint16_t ADCValue)
static void Temp_Callback(Event_t Evnt,uint16_t ADCValue)

{
	LCD_WriteString(10, 132, "온    도:" , YELLOW, BLUE);
	LCD_WriteEnglish(90 + 8, 132, ADCValue / 1000 % 10 + '0' , YELLOW, BLUE);
	LCD_WriteEnglish(90 + 16, 132, ADCValue / 100 % 10 + '0' , YELLOW, BLUE);
	LCD_WriteEnglish(90 + 24, 132, ADCValue / 10 % 10 + '0' , YELLOW, BLUE);
	LCD_WriteEnglish(90 + 32, 132, ADCValue  % 10 + '0' , YELLOW, BLUE);

}

static void ADC_Trigger(void)
{
	static uint8_t Channel = 0;

	Channel++;
	if(Channel == 4)
	{
		Channel = 1;
	}

	ADC_Start(Channel);
}

static void KEY_Control(Key_t Key)
{
	
	LCD_WriteString(10, 148, "키   	값:" , YELLOW, BLUE);
switch(Key)
 {
  case KEY_RIGHT :
   LCD_WriteString(90 + 8, 148, "Right " , YELLOW, BLUE); 
   break;
  case KEY_UP :
   LCD_WriteString(90 + 8, 148, "Up   " , YELLOW, BLUE); 
   break;
  case KEY_CENTER :
   LCD_WriteString(90 + 8, 148, "Center" , YELLOW, BLUE); 
   break;
  case KEY_LEFT :
   LCD_WriteString(90 + 8, 148, "Left  " , YELLOW, BLUE); 
   break;
  case KEY_DOWN : 
   LCD_WriteString(90 + 8, 148, "Down  " , YELLOW, BLUE); 
   break;
  default :
   break;
 }
}

typedef struct{
 uint16_t X;
 uint16_t Y;
}Snake_t;


#define SNAKE_LENGTH 10


Snake_t Snake[SNAKE_LENGTH] ={{0,0}, };


static void Snake_App(Remocon_Code_t Code)
{
 static uint8_t SnakeHead = 0;
 uint16_t X, Y;


 X = Snake[SnakeHead].X;
 Y = Snake[SnakeHead].Y;
 /* 새로운 머리의 좌표 계산 */
 switch(Code)
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


