/**
* @file		fnd.c
* @brief		FND  ����̹�  
* @author		���̼�/ �ַ�� ���� ���� �п� 	
* @remarks
* @par �����̷� 
*	@li	2012.11.06 : �ʱ�  �Լ� �ۼ�  
*/


#include "at90can128.h"
#include <avr/interrupt.h>

// FND Segment : PORTA (FND�� ���� ����)
// FND Common : PORTC0 ~ 3 (FND�� ���� ��ġ ����)

#define FND_NUMBER		4

#define  TIMER0_5MS		77		// 78.125 - 1



void FND_DisplayLoop(void);

                  	//      0   ,      1 ,       2,        3,        4,        5,        6,        7,       8,        9,        X
const unsigned char FNDFont[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xFF};
unsigned char FNDData[FND_NUMBER] = {0xFF,0xFF,0xFF,0xFF};


/**
* @fn		void FND_Init(void)
* @brief
*	- FND �ʱ�ȭ �Լ� 
* @remarks
* @param	void
* @return	void			
*/
void FND_Init(void)
{
	/***** ��Ʈ �ʱ�ȭ *****/
	PORTA = 0xFF;		// DATA0 ~ 7 �� 0 ��� 
	DDRA = 0xFF;		// PORTA�� ��� ������ ���� 
	PORTC |= 0x0F;		// FND0~ 3�� 1 ��� 
	DDRC |= 0x0F;		// FND0 ~ 3�� ��������� ���� 

	/***** Ÿ�̸�0 �ʱ�ȭ *****/
	/* CTC ��� */ 
	WGM01 = 1;
	WGM00 = 0;
	/* 1/1024 ���� */ 
	CS02 = 1;
	CS01 = 0;
	CS00 = 1;
	/* OCR�������� ���� (5ms����) */
	OCR0A = TIMER0_5MS;
	/* ���ͷ�Ʈ Ȱ��ȭ */ 
	OCIE0A = 1;
}

/**
* @fn		void FND_On(unsigned char Data, unsigned char Location, unsigned char Dot)
* @brief
*	- FND �Ѵ� �Լ�(���� FND�� ����) 
* @remarks
* @param	unsigned char Data		:FND�� ǥ���� ����(0 ~ 9)
* @param	unsigned char Location	: FND�� ǥ�õ� ��ġ( 0 ~ 3) 
* @param	unsigned char Dot		: �� ǥ��(0 : ǥ�þ��� , 1 : ǥ��) 
* @return	void			
*/
void FND_On(unsigned char Data, unsigned char Location, unsigned char Dot)
{
	// Segment(����)�� �����͸� ����.
	 Data = FNDFont[Data];
	// Dot �� ����Ѵ�. 
	if(Dot != 0)
	{
		Data &= 0x7F;
	}
	PORTA = Data;
	
	// Common(��ġ)�� �����͸� ����. 
	PORTC = (PORTC | 0x0F) & (~(1 << Location));
}

/**
* @fn		void FND_Write(unsigned char Data, unsigned char Location, unsigned char Dot)
* @brief
*	- FND �Ѵ� �Լ�(�޸𸮸� ���� FND ����) 
* @remarks
* @param	unsigned char Data		:FND�� ǥ���� ����(0 ~ 9)
* @param	unsigned char Location	: FND�� ǥ�õ� ��ġ( 0 ~ 3) 
* @param	unsigned char Dot		: �� ǥ��(0 : ǥ�þ��� , 1 : ǥ��) 
* @return	void			
*/
void FND_Write(unsigned char Data, unsigned char Location, unsigned char Dot)
{
	 Data = FNDFont[Data];
	// Dot �� ����Ѵ�. 
	if(Dot != 0)
	{
		Data &= 0x7F;
	}	
	FNDData[Location] = Data;		
}

/**
* @fn		ISR(TIMER0_COMP_vect)
* @brief
*	- Timer 0 ISR(Interrupt Service Routine) 
*	- 5ms ���� �߻� 
*	- FND�� ǥ���ϴ�  �Լ�(�޸𸮿� ����� ���� FND�� ǥ��) 
* @remarks
* @param	TIMER0_COMP_vect	: ���ͷ�Ʈ ���� ��ȣ 

* @return	void			
*/
ISR(TIMER0_COMP_vect)
{

	static unsigned char LoopNum = 0;

	LoopNum++;
	LoopNum = LoopNum % FND_NUMBER;

	/* Segment �� ��� */
	PORTA = FNDData[LoopNum];

	/* Common �� ��� */
	PORTC = (PORTC | 0x0F) & (~(1 << LoopNum));

}




