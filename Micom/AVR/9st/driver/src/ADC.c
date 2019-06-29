#include "Atmega128.h"
#include <avr/interrupt.h>
#include "ADC.h"

ADC_Handle_t ADC_Handle[4];

void ADC_Init(void)
{
	/* 레지스터 초기화 */
	REFS1 = 0; //01 : AVCC
	REFS0 = 1;
	ADLAR = 0; // 0 : 오른쪽 정렬
	ADEN  = 1; // ADC Enable
	ADIE  = 1; // ACD Interrupt Enable
	
	ADPS2 = 1; // 111 : sampling period -> clk/128
	ADPS1 = 1;
	ADPS0 = 1;
}

void ADC_Start(uint8_t Channel)
{
	while(ADSC); // 이전 ADC가 끝날때 까지 기다림
	ADMUX = (ADMUX & 0xE0) | Channel; // 채널 선택
	ADSC = 1;
}

void ADC_Open(uint8_t Channel, ADC_Handle_t Handle)
{
	ADC_Handle[Channel] = Handle;
}

void ADC_Close(uint8_t Channel)
{
	ADC_Handle[Channel] = NULL;
}

ISR(ADC_vect)
{
	uint16_t ADCValue;
	uint8_t Channel;
	
	ADCValue = ADCL + ((uint16_t)ADCH << 8);
	Channel = ADMUX & 0x1F;
	
	if(ADC_Handle[Channel])
	{
		ADC_Handle[Channel](ADCValue);
	}
}

