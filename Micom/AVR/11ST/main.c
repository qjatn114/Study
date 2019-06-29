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
#include "clock.h"

#include <avr/interrupt.h>

static void Init(void);

int main(void)
{
	uint8_t i;
	
	Init();

	Clock_App();

	
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

