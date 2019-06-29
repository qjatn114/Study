#ifndef _ADC_H_
#define _ADC_H_

#include "type.h"



typedef void (*ADC_Handle_t)(uint16_t ADCValue);

void ADC_Init(void);
void ADC_Start(uint8_t Channel);
void ADC_Open(uint8_t Channel,ADC_Handle_t Handle);
void ADC_Close(uint8_t Channel);






#endif
