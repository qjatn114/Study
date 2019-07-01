/**
* @file		adc.c
* @brief		ADC  ����̹�  
* @author		���̼�/�ַ�� ���� ���� �п� 	
* @remarks
* @par �����̷� 
*	@li	2012.11.06 : �ʱ�  �Լ� �ۼ�  
*/

#include "at90can128.h"
#include <avr/interrupt.h>

#include "uart.h"

// Channel 0 : Ű,  Channel 1 : ��������     
unsigned short ADCBuffer[5]={0, };	// ADC���� �����ϴ� ���� 		
unsigned char ADCFlag = 0;			// �� ��Ʈ�� ä�� ���� ADC���� ����Ǿ� �ִ��� ǥ�� 

/**
* @fn		void ADC_Init(void)
* @brief
*	- ADC �ʱ�ȭ �Լ� 
* @remarks
* @param	void
* @return	void			
*/
void ADC_Init(void)
{
	// �������� �ʱ�ȭ
	// ���۷��� ���� : AVCC 
	REFS1 = 0;
	REFS0 = 1;
	// ������ ���� 
	ADLAR = 0;	// ������ ���� 
	// ADC Ȱ��ȭ 
	ADEN = 1;
	// ���ͷ�Ʈ Ȱ��ȭ 
	ADIE = 1;
	// Ŭ�� ���� : 100 = 1/16 
	ADPS2 = 1;
	ADPS1 = 0;
	ADPS0 = 0;
}

/**
* @fn		void ADC_Start(unsigned char Channel)
* @brief
*	- ADC�� �����Ѵ�.  
* @remarks
* @param	unsigned char Channel	: ADC�� ä��
* @return	void			
*/
void ADC_Start(unsigned char Channel)
{
	  
	while(ADSC);		// ADC �� �Ϸ� �� ������ ��ٸ���.		

	ADMUX = (ADMUX & 0xE0) | Channel;	// ADC ä���� �����Ѵ�. 
	
	ADSC = 1;			// ADC �� �����Ѵ�. 	
}

unsigned char ADC_GetData(unsigned char Channel, unsigned short *Data)
{
	if(ADCFlag & (1 << Channel))
	{
		cli();
		*Data = ADCBuffer[Channel];
		ADCFlag &= (~(1 << Channel));
		sei();
		return 1;
	}
	else
	{
		return 0;
	}
}



/**
* @fn		ISR(ADC_vect)
* @brief
*	- ADC ISR(Interrupt Service Routine) 
* @remarks
* @param	ADC_vect	: ���ͷ�Ʈ ���� ��ȣ 
* @return	void			
*/
ISR(ADC_vect)
{
	unsigned short ADCValue;
	unsigned char Channel;

	// ADC ���� �о� �´�. (����: ADCL�� ���� �а� ADCH�� ������.)
	ADCValue = ADCL +((unsigned short)ADCH << 8);

	// ADC Channel ������ ������ �´�. 
	Channel = ADMUX & 0x1F;

	// ADC���� �����Ѵ�. 
	ADCBuffer[Channel] = ADCValue; 
	ADCFlag |= (1 << Channel);
}

