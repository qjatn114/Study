/**
* @file		pwm.c
* @brief		PWM 드라이버  
* @author		강이석/솔루션 공과 전자 학원 	
* @remarks
* @par 수정이력 
*	@li	2013.04.15 : 초기  함수 작성  
*/

#include "at90can128.h"
#include "pwm.h"


void PWM_Init(unsigned char Channels)
{
	/***** 타이머 1 초기화	*****/
	/*	Mode :  Fast PWM, 10-bit
		정지 : 포트를 일반	IO로 만듬.
		동작 : OC 핀으로 동작.
	*/
	/***** 포트 초기화 *****/
	if(Channels & PWM_CH_A)	// Channel  A 인 경우 
	{
		PORTB5 = 0;
		DDB5 = 1;
		COM1A1	= 0;		// 00 : Normal Port
		COM1A0	= 0;
	}
	if(Channels & PWM_CH_B)	// Channel  B 인 경우 
	{
		PORTB6 = 0;
		DDB6 = 1;
		COM1B1	= 0;		// 00 : Normal Port
		COM1B0	= 0;

	}
	if(Channels & PWM_CH_C)	// Channel  C 인 경우 
	{
		PORTB7 = 0;
		DDB7 = 1;
		COM1C1	= 0;		// 00 : Normal Port
		COM1C0	= 0;
	}
			
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

void PWM_A_Enable(void)
{
	COM1A1	= 1;		// 00 : Normal Port, 10 : Clear at Match/Set at Top
	COM1A0	= 0;
}

void PWM_B_Enable(void)
{
	COM1B1	= 1;		// 00 : Normal Port, 10 : Clear at Match/Set at Top
	COM1B0	= 0;
}

void PWM_C_Enable(void)
{
	COM1C1	= 1;		// 00 : Normal Port, 10 : Clear at Match/Set at Top
	COM1C0	= 0;
}

void PWM_A_Disable(void)
{
	COM1A1	= 0;		// 00 : Normal Port, 10 : Clear at Match/Set at Top
	COM1A0	= 0;
}

void PWM_B_Disable(void)
{
	COM1B1	= 0;		// 00 : Normal Port, 10 : Clear at Match/Set at Top
	COM1B0	= 0;
}

void PWM_C_Disable(void)
{
	COM1C1	= 0;		// 00 : Normal Port, 10 : Clear at Match/Set at Top
	COM1C0	= 0;
}


void PWM_SetDuty(unsigned short Duty)
{
	OCR1AH = Duty >> 8;			// 상위 바이트 먼저 쓴다. 
	OCR1AL = (unsigned char)Duty;

	OCR1BH = Duty >> 8;			// 상위 바이트 먼저 쓴다. 
	OCR1BL = (unsigned char)Duty;

	OCR1CH = Duty >> 8;			// 상위 바이트 먼저 쓴다. 
	OCR1CL = (unsigned char)Duty;	
}

void PWM_A_SetDuty(unsigned short Duty)
{
	OCR1AH = Duty >> 8;			// 상위 바이트 먼저 쓴다. 
	OCR1AL = (unsigned char)Duty;
}

void PWM_B_SetDuty(unsigned short Duty)
{
	OCR1BH = Duty >> 8;			// 상위 바이트 먼저 쓴다. 
	OCR1BL = (unsigned char)Duty;
}

void PWM_C_SetDuty(unsigned short Duty)
{
	OCR1CH = Duty >> 8;			// 상위 바이트 먼저 쓴다. 
	OCR1CL = (unsigned char)Duty;	
}

unsigned short PWM_A_GetDuty(void)			// Duty : 0 ~ 1023
{
	return OCR1AL + ((unsigned short)OCR1AH << 8);
}

unsigned short PWM_B_GetDuty(void)			// Duty : 0 ~ 1023
{
	return OCR1BL + ((unsigned short)OCR1BH << 8);
}

unsigned short PWM_C_GetDuty(void)			// Duty : 0 ~ 1023
{
	return OCR1CL + ((unsigned short)OCR1CH << 8);
}




