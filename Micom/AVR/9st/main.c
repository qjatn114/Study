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
#include "clock.h"
#include "i2c.h"
#include "rtc.h"
#include "gps.h"

static void Init(void);

int main(void)
{
	Init();

	Clock_App();
	//GPS_App();
	
	sei(); // Global Interrupt Enable
	
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
	I2C_Init();
	RTC_Init();
}
