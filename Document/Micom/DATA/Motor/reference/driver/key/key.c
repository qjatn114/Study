/**
* @file		key.c
* @brief		Key  드라이버  
* @author		강이석/솔루션 공과 전자 학원 	
* @remarks
* @par 수정이력 
*	@li	2012.11.06 : 초기  함수 작성  
*/

#include "at90can128.h"
#include "adc.h"
#include "key.h"
#include "uart.h"
#include <avr/interrupt.h>


#define KEY_ADC_CHANNEL		0

#define KEY_NUMBER			5		// 키의 개수 

#define ADC_KEY_RIGHT		0		// 키의 ADC 값 
#define ADC_KEY_UP			198		
#define ADC_KEY_CENTER		409
#define ADC_KEY_LEFT		611
#define ADC_KEY_DOWN		813

#define ADC_KEY_VARIATION	50

typedef struct{
	KEY_CODE Key;
	unsigned short KeyADC;
}ST_KEY_ADC;


const ST_KEY_ADC KeyADCTable[KEY_NUMBER] = {{KEY_RIGHT, ADC_KEY_RIGHT}, {KEY_UP, ADC_KEY_UP},{KEY_CENTER, ADC_KEY_CENTER}, {KEY_LEFT, ADC_KEY_LEFT}, {KEY_DOWN, ADC_KEY_DOWN}}; 



/**
* @fn		void Key_Init(void)
* @brief
*	- Key 초기화 함수 
* @remarks
* @param	void
* @return	void			
*/
void Key_Init(void)
{
	/***** 외부 인터럽트4 (KEY_INT) 초기화 *****/
	/* Falling edge */
	ISC41 = 1;		// 10 : Falling edge, 11 : Rising edge
	ISC40 = 0;
	/* 인터럽트 활성화 */ 		
	INT4 = 1; 				
}

KEY_CODE Key_GetKey(void)
{
    unsigned short ADCValue;
	unsigned char i;

    if(ADC_GetData(0, &ADCValue) == 0)      // ADC 값을 가지고 온다.
    {
        return KEY_NOTHING;					// ADC값이 없는 경우
    }	

	
	/*  Key 값을  찾아서 리턴한다.  */
	for(i = 0; i < KEY_NUMBER; i++)
	{
		if(((short)ADCValue > ((short)KeyADCTable[i].KeyADC - ADC_KEY_VARIATION)) && (ADCValue < (KeyADCTable[i].KeyADC + ADC_KEY_VARIATION)))
		{
			return KeyADCTable[i].Key;		// 키 값이 발견이 되어 키가 리턴
			break;
		}
	}
	/* 키 값을 찾지 못한 경우 */
	return KEY_NOTHING;
}


/**
* @fn		ISR(INT4_vect)
* @brief
*	- 외부 인터럽트 4 ISR(Interrupt Service Routine)  
*	- KEY_INT 인터럽트 
* @remarks
* @param	INT4_vect	: 인터럽트 백터 번호 
* @return	void			
*/
ISR(INT4_vect)
{
	ADC_Start(0);		// Key ADC를 시작한다. 
}

