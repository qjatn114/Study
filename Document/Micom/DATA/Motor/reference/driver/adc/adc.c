/**
* @file		adc.c
* @brief		ADC  드라이버  
* @author		강이석/솔루션 공과 전자 학원 	
* @remarks
* @par 수정이력 
*	@li	2012.11.06 : 초기  함수 작성  
*/

#include "at90can128.h"
#include <avr/interrupt.h>

#include "uart.h"

// Channel 0 : 키,  Channel 1 : 가변저항     
unsigned short ADCBuffer[5]={0, };	// ADC값을 저장하는 버퍼 		
unsigned char ADCFlag = 0;			// 각 비트는 채널 별로 ADC값이 저장되어 있는지 표시 

/**
* @fn		void ADC_Init(void)
* @brief
*	- ADC 초기화 함수 
* @remarks
* @param	void
* @return	void			
*/
void ADC_Init(void)
{
	// 레지스터 초기화
	// 레퍼런스 전압 : AVCC 
	REFS1 = 0;
	REFS0 = 1;
	// 데이터 정렬 
	ADLAR = 0;	// 오른쪽 정렬 
	// ADC 활성화 
	ADEN = 1;
	// 인터럽트 활성화 
	ADIE = 1;
	// 클럭 분주 : 100 = 1/16 
	ADPS2 = 1;
	ADPS1 = 0;
	ADPS0 = 0;
}

/**
* @fn		void ADC_Start(unsigned char Channel)
* @brief
*	- ADC를 시작한다.  
* @remarks
* @param	unsigned char Channel	: ADC할 채널
* @return	void			
*/
void ADC_Start(unsigned char Channel)
{
	  
	while(ADSC);		// ADC 가 완료 될 때까지 기다린다.		

	ADMUX = (ADMUX & 0xE0) | Channel;	// ADC 채널을 설정한다. 
	
	ADSC = 1;			// ADC 를 시작한다. 	
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
* @param	ADC_vect	: 인터럽트 백터 번호 
* @return	void			
*/
ISR(ADC_vect)
{
	unsigned short ADCValue;
	unsigned char Channel;

	// ADC 값을 읽어 온다. (주의: ADCL를 먼저 읽고 ADCH를 읽은다.)
	ADCValue = ADCL +((unsigned short)ADCH << 8);

	// ADC Channel 정보를 가지고 온다. 
	Channel = ADMUX & 0x1F;

	// ADC값을 저장한다. 
	ADCBuffer[Channel] = ADCValue; 
	ADCFlag |= (1 << Channel);
}

