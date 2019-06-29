#include "type.h"
#include "atmega128.h"

#include <avr/interrupt.h>


//const�� ROM�� �����ϱ� ���ؼ� ( ��� : ������ �ʱ� ������, ���� : ���ϱ� ������ RAM�� ���� )
const uint8_t FND_Pont[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0x80,0x90,0xff};
const uint8_t FND_Common[4] = {0x10,0x20,0x40,0x80};

uint8_t FND_Buffer[] = {0xff,0xff,0xff,0xff};

void FND_Init(void)
{
	/* ��Ʈ �ʱ�ȭ (PA0~7(Data_0~7) : ���, PG4(FND_LE):���, PF4~7(FND_0~3) : ��� ) */
	DDRA = 0xFF;
	DDG4 = 1;
	DDRF |= 0xF0;

	/* Ÿ�̸� �ʱ�ȭ (Timer2,CTC Mode, 1/1024, 5ms Interrupt) */
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
	/* Segment ��ȣ */
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
	
	/* Common ��ȣ */
	PORTF = (PORTF & 0x0F) | FND_Common[Digit];
}

void FND_Write(uint8_t Num,uint8_t Digit,uint8_t Dot)
{
	/* Segment ��ȣ */
	if(Dot)
	{
		FND_Buffer[Digit] = FND_Pont[Num] & 0x7F;
	}
	else
	{
		FND_Buffer[Digit] = FND_Pont[Num];
	}
}


/* 5ms ȣ�� */
ISR(TIMER2_COMP_vect)
{
	static uint8_t Digit = 0;

	/* 0 1 2 3 0 1 2 3...... */
	Digit++;
	Digit %= 4;
	
	/* Segment ��ȣ */
	PORTA = FND_Buffer[Digit];
	PORTG4 = 0;
	PORTG4 = 1;
	PORTG4 = 0;
	
	/* Common ��ȣ */
	PORTF = (PORTF & 0x0F)| FND_Common[Digit];
}
