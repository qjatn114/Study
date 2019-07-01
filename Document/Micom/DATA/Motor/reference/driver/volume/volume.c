#include "at90can128.h"
#include "adc.h"
#include <avr/interrupt.h>

#define TIMER_1MS		249		// 250 -1

void Volume_Init(void)
{
	/***** Timer 2 초기화 *****/
	/* CTC 모드 */ 
	WGM21 = 1;
	WGM20 = 0;
	/* 1/64 분주 */ 
	CS22 = 1;
	CS21 = 0;
	CS20 = 0;
	/* OCR레지스터 설정 (1ms으로) */
	OCR2A = TIMER_1MS;
	/* 인터럽트 활성화 */ 
	OCIE2A = 1;
}

unsigned char Volume_GetData(unsigned short *Data)
{
	unsigned short ADCValue;
	
	if(ADC_GetData(1, &ADCValue))
	{
		*Data = ADCValue;
		return 1;
	}
	else
	{
		return 0;
	}
}



/* 타이머 2 ISR */
ISR(TIMER2_COMP_vect)
{
	static unsigned short Count = 0;

	Count++;
	
	if(Count == 100)		// 512us * 1953 = 약 1s
	{
		ADC_Start(1);		// Volume ADC를 시작한다. 
		Count = 0;
	}
}


