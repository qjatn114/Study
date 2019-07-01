#include "type.h"
#include "keyy.h"
#include "extint.h"
#include "adc.h"

#define ADC_KEY_RIGHT    0
#define ADC_KEY_UP       198
#define ADC_KEY_CENTER   409
#define ADC_KEY_LEFT     611
#define ADC_KEY_DOWN     813

#define ADC_KEY_VARIATION   50



Key_Handle_t Key_Handle = NULL;

static void Key_Extint_Handle (void);
static void Key_Adc_Handle(uint16_t ADCValue);

void KEY_Init(void)
{
	ADC_Open(0,Key_Adc_Handle);
	ExtInt_Open(Key_Extint_Handle );
}


void KEY_Open(Key_Handle_t Handle)
{
	Key_Handle = Handle;
}


void KEY_Close(void)
{
	Key_Handle = NULL;
}

static void Key_Extint_Handle (void)
{
	ADC_Start(0);
}

static void Key_Adc_Handle(uint16_t ADCValue)
{
	/* ADC -> Key */
	Key_t Key;
 
	 if(ADCValue < (ADC_KEY_RIGHT + ADC_KEY_VARIATION))  
	 {  
	 Key = KEY_RIGHT; 
	 } 
	 else if(ADCValue < (ADC_KEY_UP + ADC_KEY_VARIATION))  
	 {  
	 Key = KEY_UP;  
	 } 
	 else if(ADCValue < (ADC_KEY_CENTER + ADC_KEY_VARIATION))  
	 {  
	 Key = KEY_CENTER;  
	 } 
	 else if(ADCValue < (ADC_KEY_LEFT + ADC_KEY_VARIATION))  
	 {  
	 Key = KEY_LEFT;  
	 } 
	 else if(ADCValue < (ADC_KEY_DOWN + ADC_KEY_VARIATION))  
	 {  
	 Key = KEY_DOWN;  
	 } 
	 else  
	 {  
	 Key = KEY_NOTHING; 
	 }

	/* Back */
	if(Key_Handle)
	{
		Key_Handle(Key);
	}
}

