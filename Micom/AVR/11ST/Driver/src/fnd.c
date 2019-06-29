#include "type.h"
#include "atmega128.h"

#include <avr/interrupt.h>


//const는 ROM에 저장하기 위해서 ( 상수 : 변하지 않기 때문에, 변수 : 변하기 때문에 RAM에 저장 )
const uint8_t FND_Pont[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0x80,0x90,0xff};
const uint8_t FND_Common[4] = {0x10,0x20,0x40,0x80};

uint8_t FND_Buffer[] = {0xff,0xff,0xff,0xff};

void FND_Init(void)
{
	/* 포트 초기화 (PA0~7(Data_0~7) : 출력, PG4(FND_LE):출력, PF4~7(FND_0~3) : 출력 ) */
	DDRA = 0xFF;
	DDG4 = 1;
	DDRF |= 0xF0;

	/* 타이머 초기화 (Timer2,CTC Mode, 1/1024, 5ms Interrupt) */
	WGM21 = 1;
	WGM20 = 0;
	CS22 = 1;
	CS21 = 0;
	CS20 = 1;
	OCR2 = 35;	//5ms
	OCIE2 = 1;	//Interrupt Enable
}

void FND_On(uint8_t Num,uint8_t Digit,uint8_t Dot)
{
	/* Segment 신호 */
	if(Dot)
	{
		PORTA = FND_Pont[Num] & ~0x80;
	}
	else
	{
		PORTA = FND_Pont[Num];
	}
	PORTG4 = 0;
	PORTG4 = 1;
	PORTG4 = 0;
	
	/* Common 신호 */
	PORTF = (PORTF & 0x0F) | FND_Common[Digit];
}

void FND_Write(uint8_t Num,uint8_t Digit,uint8_t Dot)
{
	/* Segment 신호 */
	if(Dot)
	{
		FND_Buffer[Digit] = FND_Pont[Num] & 0x7F;
	}
	else
	{
		FND_Buffer[Digit] = FND_Pont[Num];
	}
}


/* 5ms 호출 */
ISR(TIMER2_COMP_vect)
{
	static uint8_t Digit = 0;

	/* 0 1 2 3 0 1 2 3...... */
	Digit++;
	Digit %= 4;
	
	/* Segment 신호 */
	PORTA = FND_Buffer[Digit];
	PORTG4 = 0;
	PORTG4 = 1;
	PORTG4 = 0;
	
	/* Common 신호 */
	PORTF = (PORTF & 0x0F)| FND_Common[Digit];
}
