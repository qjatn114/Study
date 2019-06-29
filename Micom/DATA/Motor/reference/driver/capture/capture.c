/**
* @file		capture.c
* @brief		CAPTURE  ����̹�  
* @author		���̼�/�ַ�� ���� ���� �п� 	
* @remarks
* @par �����̷� 
*	@li	2013.04.15 : �ʱ�  �Լ� �ۼ�  
*/
#include "at90can128.h"
#include <avr/interrupt.h>

#define TIMER1_TOP		1024

unsigned short OverflowCount = 0;			// ĸ�ĵ� ��ȣ�� ������ ���� �ϱ� ���� �ֱ⸦ ���� ī����  
unsigned long CaptureCount = 0;				// ĸ�ĵ� ��ȣ�� ���� 
unsigned long CaptureCountPerUnitTime = 0;	// ���� �ð��� ĸ�ĵ� ��ȣ 
unsigned char CaptureFlag = 0;				// 0 : ĸ�� �ȵ�, 1 : ĸ�� ��.



void Capture_Init(void)
{
	/***** Ÿ�̸�1 Capture �κ� ����(PWM�� Ÿ�̸�1 ���) *****/
	ICES1 = 1;		// 0 : Falling Edge , 1 : Rising Edge 
	
	ICIE1 = 1;		// Capture ���ͷ�Ʈ Ȱ��ȭ 	
	TOIE1 = 1;		// Overflow ���ͷ�Ʈ Ȱ��ȭ (�ι� ���������� �߻��ϴ� ���� ���� ���� Ÿ�̸�)


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


/* Ÿ�̸� 1 ISR */
// 1/(16M /(8*1024))= 512us ���� �߻� */
ISR(TIMER1_OVF_vect)
{
	OverflowCount++;
	
	if(OverflowCount == 195)		// 512us * 1953 = �� 1s
	{
		CaptureCountPerUnitTime = CaptureCount;
		CaptureCount = 0;
		CaptureFlag = 1;
		OverflowCount = 0;
	}
}



