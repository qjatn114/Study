/**
* @file		pwm.c
* @brief		PWM ����̹�  
* @author		���̼�/�ַ�� ���� ���� �п� 	
* @remarks
* @par �����̷� 
*	@li	2013.04.15 : �ʱ�  �Լ� �ۼ�  
*/

#include "at90can128.h"
#include "pwm.h"


void PWM_Init(unsigned char Channels)
{
	/***** Ÿ�̸� 1 �ʱ�ȭ	*****/
	/*	Mode :  Fast PWM, 10-bit
		���� : ��Ʈ�� �Ϲ�	IO�� ����.
		���� : OC ������ ����.
	*/
	/***** ��Ʈ �ʱ�ȭ *****/
	if(Channels & PWM_CH_A)	// Channel  A �� ��� 
	{
		PORTB5 = 0;
		DDB5 = 1;
		COM1A1	= 0;		// 00 : Normal Port
		COM1A0	= 0;
	}
	if(Channels & PWM_CH_B)	// Channel  B �� ��� 
	{
		PORTB6 = 0;
		DDB6 = 1;
		COM1B1	= 0;		// 00 : Normal Port
		COM1B0	= 0;

	}
	if(Channels & PWM_CH_C)	// Channel  C �� ��� 
	{
		PORTB7 = 0;
		DDB7 = 1;
		COM1C1	= 0;		// 00 : Normal Port
		COM1C0	= 0;
	}
			
	/***** Waveform Generation Mode ���� ******/
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

	/* Clock ���� */
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
			
	/* Count �� �ʱ�ȭ */
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
	OCR1AH = Duty >> 8;			// ���� ����Ʈ ���� ����. 
	OCR1AL = (unsigned char)Duty;

	OCR1BH = Duty >> 8;			// ���� ����Ʈ ���� ����. 
	OCR1BL = (unsigned char)Duty;

	OCR1CH = Duty >> 8;			// ���� ����Ʈ ���� ����. 
	OCR1CL = (unsigned char)Duty;	
}

void PWM_A_SetDuty(unsigned short Duty)
{
	OCR1AH = Duty >> 8;			// ���� ����Ʈ ���� ����. 
	OCR1AL = (unsigned char)Duty;
}

void PWM_B_SetDuty(unsigned short Duty)
{
	OCR1BH = Duty >> 8;			// ���� ����Ʈ ���� ����. 
	OCR1BL = (unsigned char)Duty;
}

void PWM_C_SetDuty(unsigned short Duty)
{
	OCR1CH = Duty >> 8;			// ���� ����Ʈ ���� ����. 
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




