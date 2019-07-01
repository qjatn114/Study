#include "Atmega128.h"
#include <avr/interrupt.h>
#include "Type.h"
#include "fnd.h"

const uint8_t FND_Font[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xFF};
const uint8_t FND_Common[] = {0x10, 0x20, 0x40, 0x80};
const uint8_t FND_Dot[] = {1,0};	
uint8_t FND_Buffer[] = {0xFF, 0xFF, 0xFF, 0xFF};

void FND_Init(void)
{
	/* Data_0~7 : PA0~7, FND_Latch : PG4 , FND_0~3 : PF4~7*/
	DDRA |= 0xFF;
	DDG4 = 1;
	DDF4 = 1;
	DDF5 = 1;
	DDF6 = 1;
	DDF7 = 1;
	/* Timer Init (5ms tick) */
	WGM21 = 1; // 10 : CTC Mode
	WGM20 = 0;
	CS22 = 1; // 101: clk/1024
	CS21 = 0;
	CS20 = 1;
	
	OCR2 = 35; // 36-1 : 5ms tick
	OCIE2 = 1; // Timer2 Interrupt Enable
}

void FND_On(uint8_t Num, uint8_t Digit, uint8_t Dot)
{
	/* Segment ��ȣ */
	PORTA = FND_Font[Num];
	/* Dot ��ȣ */
	PORTA7 = FND_Dot[Dot];
	/* Latch ��ȣ �߻�  */
	PORTG4 = 0;
	PORTG4 = 1;
	PORTG4 = 0;
	
	/* Common ��ȣ */
	PORTF &= 0x0F;
	PORTF |= FND_Common[Digit];
}

void FND_Write(uint8_t Num, uint8_t Digit, uint8_t Dot)
{
	if(Dot)
	{
		FND_Buffer[Digit] = FND_Font[Num] & 0x7F;
	}
	else
	{
		FND_Buffer[Digit] = FND_Font[Num];
	}
}


/* 5ms ���� ȣ�� */
ISR(TIMER2_COMP_vect)
{
	static uint8_t Digit = 0;
	Digit++;
	Digit %= 4;
	PORTA = FND_Buffer[Digit];
	
	/* Latch ��ȣ �߻�  */
	PORTG4 = 0;
	PORTG4 = 1;
	PORTG4 = 0;

	/* Common ��ȣ */
	PORTF &= 0x0F;
	PORTF |= FND_Common[Digit];
}

