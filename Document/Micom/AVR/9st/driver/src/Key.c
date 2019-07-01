#include "Atmega128.h"
#include <avr/interrupt.h>
#include "Key.h"
#include "ExtInt.h"
#include "ADC.h"

#define ADC_KEY_RIGHT    0
#define ADC_KEY_UP       198
#define ADC_KEY_CENTER   409
#define ADC_KEY_LEFT     611
#define ADC_KEY_DOWN     813

#define ADC_KEY_VARIATION   50


Key_Handle_t Key_Handle;

static void ExtInt_Callback(void);
static void ADC_Callback(uint16_t Data);


void Key_Init(void)
{
	ExtInt_Init();
	ADC_Init();
}

void Key_Open(Key_Handle_t Handle)
{
	Key_Handle = Handle;
	ExtInt_Open(ExtInt_Callback);
	ADC_Open(0,ADC_Callback);
}

void Key_Close(void)
{
	Key_Handle = NULL;
	ExtInt_Close();
	ADC_Close(0);
}

static void ExtInt_Callback(void)
{
	ADC_Start(0);
}

static void ADC_Callback(uint16_t Data)
{
	Key_t key;
	if(Data <= ADC_KEY_RIGHT + ADC_KEY_VARIATION)
	{
		key = KEY_RIGHT;
	}
	else if((Data > ADC_KEY_UP - ADC_KEY_VARIATION) && (Data <= ADC_KEY_UP + ADC_KEY_VARIATION))
	{
		key = KEY_UP;
	}
	else if((Data > ADC_KEY_CENTER - ADC_KEY_VARIATION) && (Data <= ADC_KEY_CENTER + ADC_KEY_VARIATION))
	{
		key = KEY_CENTER;
	}
	else if((Data > ADC_KEY_LEFT - ADC_KEY_VARIATION) && (Data <= ADC_KEY_LEFT + ADC_KEY_VARIATION))
	{
		key = KEY_LEFT;
	}
	else if((Data > ADC_KEY_DOWN - ADC_KEY_VARIATION) &&  (Data <= ADC_KEY_DOWN + ADC_KEY_VARIATION))
	{
		key = KEY_DOWN;
	}
	else
	{
		key = KEY_NOTHING;
	}
	
	if(Key_Handle)
	{
		Key_Handle(key);
	}
	
}



