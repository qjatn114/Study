#include "atmega128.h"
#include "type.h"

void LED_Init(void)
{
	/* 포트 초기화 (PA0~7(Data_0~7) : 출력, PG3(LED_LE):출력) */
	DDRA = 0xFF;
	DDG3 = 1;
}
void LED_On(uint8_t Data)
{
	PORTA = Data;
	/* Latch 신호 발생 */
	PORTG3 = 0;	// 0
	PORTG3 = 1;	// 1
	PORTG3 = 0;	// 0
}













