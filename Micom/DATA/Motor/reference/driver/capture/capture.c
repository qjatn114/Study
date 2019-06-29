/**
* @file		capture.c
* @brief		CAPTURE  드라이버  
* @author		강이석/솔루션 공과 전자 학원 	
* @remarks
* @par 수정이력 
*	@li	2013.04.15 : 초기  함수 작성  
*/
#include "at90can128.h"
#include <avr/interrupt.h>

#define TIMER1_TOP		1024

unsigned short OverflowCount = 0;			// 캡쳐된 신호의 개수를 측정 하기 위한 주기를 위한 카운터  
unsigned long CaptureCount = 0;				// 캡쳐된 신호의 개수 
unsigned long CaptureCountPerUnitTime = 0;	// 단위 시간당 캡쳐된 신호 
unsigned char CaptureFlag = 0;				// 0 : 캡쳐 안됨, 1 : 캡쳐 됨.



void Capture_Init(void)
{
	/***** 타이머1 Capture 부분 설정(PWM도 타이머1 사용) *****/
	ICES1 = 1;		// 0 : Falling Edge , 1 : Rising Edge 
	
	ICIE1 = 1;		// Capture 인터럽트 활성화 	
	TOIE1 = 1;		// Overflow 인터럽트 활성화 (두번 연속적으로 발생하는 것을 막기 위한 타이머)


	/***** Waveform Generation Mode 설정 ******/
	/*	0000 : Normal
		0001 : PWM, Pase Correct, 8-bit
		0010 : PWM, Pase Correct, 9-bit
		0011 : PWM, Pase Correct, 10-bit
		0100 : CTC
		0101 : Fast PWM, 8-bit
		0110 : Fast PWM, 9-bit
		0111 : Fast PWM, 10-bit
		1000 : PWM, Phase and Frequency Correct (TOP : ICRn)
	*/		
	WGM13 = 0;		// Fast PWM, 10-bit
	WGM12 = 1;
	WGM11 = 1;
	WGM10 = 1;

	/* Clock 설정 */
	/*	000 : No clock source
		001 : 1/1
		010 : 1/8
		011 : 1/64
		100 : 1/256
		101 : 1/1024	
	*/
	CS12 = 0;
	CS11 = 1;
	CS10 = 0;
			
	/* Count 값 초기화 */
	TCNT1H =0x00;
	TCNT1L =0x00;

	/* Clear TC1 interrupt flags*/
	TIFR1 = TIFR1;	  



}

unsigned char Capture_GetTime(unsigned long *Time)
{
	if(CaptureFlag)
	{
		CaptureFlag = 0;
		*Time = CaptureCountPerUnitTime;
		return 1;
	}
	else
	{
		return 0;
	}
}

ISR(TIMER1_CAPT_vect)
{
	CaptureCount++;
}


/* 타이머 1 ISR */
// 1/(16M /(8*1024))= 512us 마다 발생 */
ISR(TIMER1_OVF_vect)
{
	OverflowCount++;
	
	if(OverflowCount == 195)		// 512us * 1953 = 약 1s
	{
		CaptureCountPerUnitTime = CaptureCount;
		CaptureCount = 0;
		CaptureFlag = 1;
		OverflowCount = 0;
	}
}



