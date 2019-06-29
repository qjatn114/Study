#include "Atmega128.h"
#include "Type.h"
#include "led.h"


#define LED_LE_PIN DDG3

void LED_Init(void)
{
	/* Data_0~7 : PA0~7, LED_LE : PG3 -> ��� */
	DDRA |= 0xFF;
	DDG3 = 1;
}

void LED_On(uint8_t Data)
{
	PORTA = Data;
	/* Latch ��ȣ �߻�  */
    PORTG3 = 0; // 0
	PORTG3 = 1;  // 1
	PORTG3 = 0; // 0
}


