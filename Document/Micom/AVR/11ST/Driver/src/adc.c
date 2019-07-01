#include "type.h"
#include "atmega128.h"
#include "adc.h"
#include <avr/interrupt.h>


ADC_Handle_t ADC_Handle[4]= {NULL,};


void ADC_Init(void)
{
	/* Register Init */
	REFS1 = 0;		//01 : AVCC
	REFS0 = 1;

	ADLAR = 0 ;		// 0 : ������ ����
	ADEN = 1;		// ADC Ȱ��ȭ
	ADIE = 1;		//���ͷ�Ʈ Ȱ��ȭ

	ADPS2 = 1;		// 111 : 1/128
	ADPS1 = 1;
	ADPS0 = 1;
}

void ADC_Start(uint8_t Channel)
{
	while(ADSC);		//ADC���� ������ ��ٸ�
	ADMUX = (ADMUX & 0xE0) | Channel;	//Mux ����
	ADSC = 1;		//ADC Start
}

void ADC_Open(uint8_t Channel,ADC_Handle_t Handle)
{
	ADC_Handle[Channel] = Handle;
}

void ADC_Close(uint8_t Channel)
{
	ADC_Handle[Channel] = NULL;
}

ISR(ADC_vect)
{
	uint8_t Channel;
	uint16_t ADCValue;

	Channel = ADMUX & 0x1f;
	ADCValue = ADCL + ( (uint16_t)ADCH << 8 );
	if(ADC_Handle[Channel])
	{
		ADC_Handle[Channel](ADCValue);
	}
}



