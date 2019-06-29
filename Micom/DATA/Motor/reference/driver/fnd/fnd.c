/**
* @file		fnd.c
* @brief		FND  드라이버  
* @author		강이석/ 솔루션 공과 전자 학원 	
* @remarks
* @par 수정이력 
*	@li	2012.11.06 : 초기  함수 작성  
*/


#include "at90can128.h"
#include <avr/interrupt.h>

// FND Segment : PORTA (FND의 숫자 결정)
// FND Common : PORTC0 ~ 3 (FND가 켜질 위치 결정)

#define FND_NUMBER		4

#define  TIMER0_5MS		77		// 78.125 - 1



void FND_DisplayLoop(void);

                  	//      0   ,      1 ,       2,        3,        4,        5,        6,        7,       8,        9,        X
const unsigned char FNDFont[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xFF};
unsigned char FNDData[FND_NUMBER] = {0xFF,0xFF,0xFF,0xFF};


/**
* @fn		void FND_Init(void)
* @brief
*	- FND 초기화 함수 
* @remarks
* @param	void
* @return	void			
*/
void FND_Init(void)
{
	/***** 포트 초기화 *****/
	PORTA = 0xFF;		// DATA0 ~ 7 에 0 출력 
	DDRA = 0xFF;		// PORTA를 출력 핀으로 만듬 
	PORTC |= 0x0F;		// FND0~ 3에 1 출력 
	DDRC |= 0x0F;		// FND0 ~ 3을 출력핀으로 만듬 

	/***** 타이머0 초기화 *****/
	/* CTC 모드 */ 
	WGM01 = 1;
	WGM00 = 0;
	/* 1/1024 분주 */ 
	CS02 = 1;
	CS01 = 0;
	CS00 = 1;
	/* OCR레지스터 설정 (5ms으로) */
	OCR0A = TIMER0_5MS;
	/* 인터럽트 활성화 */ 
	OCIE0A = 1;
}

/**
* @fn		void FND_On(unsigned char Data, unsigned char Location, unsigned char Dot)
* @brief
*	- FND 켜는 함수(직접 FND를 구동) 
* @remarks
* @param	unsigned char Data		:FND에 표시할 숫자(0 ~ 9)
* @param	unsigned char Location	: FND가 표시될 위치( 0 ~ 3) 
* @param	unsigned char Dot		: 점 표시(0 : 표시안함 , 1 : 표시) 
* @return	void			
*/
void FND_On(unsigned char Data, unsigned char Location, unsigned char Dot)
{
	// Segment(숫자)에 데이터를 쓴다.
	 Data = FNDFont[Data];
	// Dot 를 계산한다. 
	if(Dot != 0)
	{
		Data &= 0x7F;
	}
	PORTA = Data;
	
	// Common(위치)에 데이터를 쓴다. 
	PORTC = (PORTC | 0x0F) & (~(1 << Location));
}

/**
* @fn		void FND_Write(unsigned char Data, unsigned char Location, unsigned char Dot)
* @brief
*	- FND 켜는 함수(메모리를 통한 FND 구동) 
* @remarks
* @param	unsigned char Data		:FND에 표시할 숫자(0 ~ 9)
* @param	unsigned char Location	: FND가 표시될 위치( 0 ~ 3) 
* @param	unsigned char Dot		: 점 표시(0 : 표시안함 , 1 : 표시) 
* @return	void			
*/
void FND_Write(unsigned char Data, unsigned char Location, unsigned char Dot)
{
	 Data = FNDFont[Data];
	// Dot 를 계산한다. 
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
*	- 5ms 마다 발생 
*	- FND를 표시하는  함수(메모리에 저장된 값을 FND에 표시) 
* @remarks
* @param	TIMER0_COMP_vect	: 인터럽트 백터 번호 

* @return	void			
*/
ISR(TIMER0_COMP_vect)
{

	static unsigned char LoopNum = 0;

	LoopNum++;
	LoopNum = LoopNum % FND_NUMBER;

	/* Segment 값 출력 */
	PORTA = FNDData[LoopNum];

	/* Common 값 출력 */
	PORTC = (PORTC | 0x0F) & (~(1 << LoopNum));

}




