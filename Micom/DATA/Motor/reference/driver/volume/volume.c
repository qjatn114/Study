#include "at90can128.h"
#include "adc.h"
#include <avr/interrupt.h>

#define TIMER_1MS		249		// 250 -1

void Volume_Init(void)
{
	/***** Timer 2 �ʱ�ȭ *****/
	/* CTC ��� */ 
	WGM21 = 1;
	WGM20 = 0;
	/* 1/64 ���� */ 
	CS22 = 1;
	CS21 = 0;
	CS20 = 0;
	/* OCR�������� ���� (1ms����) */
	OCR2A = TIMER_1MS;
	/* ���ͷ�Ʈ Ȱ��ȭ */ 
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



/* Ÿ�̸� 2 ISR */
ISR(TIMER2_COMP_vect)
{
	static unsigned short Count = 0;

	Count++;
	
	if(Count == 100)		// 512us * 1953 = �� 1s
	{
		ADC_Start(1);		// Volume ADC�� �����Ѵ�. 
		Count = 0;
	}
}


