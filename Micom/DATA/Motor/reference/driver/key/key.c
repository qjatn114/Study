/**
* @file		key.c
* @brief		Key  ����̹�  
* @author		���̼�/�ַ�� ���� ���� �п� 	
* @remarks
* @par �����̷� 
*	@li	2012.11.06 : �ʱ�  �Լ� �ۼ�  
*/

#include "at90can128.h"
#include "adc.h"
#include "key.h"
#include "uart.h"
#include <avr/interrupt.h>


#define KEY_ADC_CHANNEL		0

#define KEY_NUMBER			5		// Ű�� ���� 

#define ADC_KEY_RIGHT		0		// Ű�� ADC �� 
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
*	- Key �ʱ�ȭ �Լ� 
* @remarks
* @param	void
* @return	void			
*/
void Key_Init(void)
{
	/***** �ܺ� ���ͷ�Ʈ4 (KEY_INT) �ʱ�ȭ *****/
	/* Falling edge */
	ISC41 = 1;		// 10 : Falling edge, 11 : Rising edge
	ISC40 = 0;
	/* ���ͷ�Ʈ Ȱ��ȭ */ 		
	INT4 = 1; 				
}

KEY_CODE Key_GetKey(void)
{
    unsigned short ADCValue;
	unsigned char i;

    if(ADC_GetData(0, &ADCValue) == 0)      // ADC ���� ������ �´�.
    {
        return KEY_NOTHING;					// ADC���� ���� ���
    }	

	
	/*  Key ����  ã�Ƽ� �����Ѵ�.  */
	for(i = 0; i < KEY_NUMBER; i++)
	{
		if(((short)ADCValue > ((short)KeyADCTable[i].KeyADC - ADC_KEY_VARIATION)) && (ADCValue < (KeyADCTable[i].KeyADC + ADC_KEY_VARIATION)))
		{
			return KeyADCTable[i].Key;		// Ű ���� �߰��� �Ǿ� Ű�� ����
			break;
		}
	}
	/* Ű ���� ã�� ���� ��� */
	return KEY_NOTHING;
}


/**
* @fn		ISR(INT4_vect)
* @brief
*	- �ܺ� ���ͷ�Ʈ 4 ISR(Interrupt Service Routine)  
*	- KEY_INT ���ͷ�Ʈ 
* @remarks
* @param	INT4_vect	: ���ͷ�Ʈ ���� ��ȣ 
* @return	void			
*/
ISR(INT4_vect)
{
	ADC_Start(0);		// Key ADC�� �����Ѵ�. 
}

