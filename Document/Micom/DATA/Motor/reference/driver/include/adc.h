#ifndef _ADC_H_
#define _ADC_H_

void ADC_Init(void);
void ADC_Start(unsigned char Channel);
unsigned char ADC_GetData(unsigned char Channel, unsigned short *Data);

#endif
