#include "atmega128.h"
#include "type.h"

void LED_Init(void)
{
	/* ��Ʈ �ʱ�ȭ (PA0~7(Data_0~7) : ���, PG3(LED_LE):���) */
	DDRA = 0xFF;
	DDG3 = 1;
}
void LED_On(uint8_t Data)
{
	PORTA = Data;
	/* Latch ��ȣ �߻� */
	PORTG3 = 0;	// 0
	PORTG3 = 1;	// 1
	PORTG3 = 0;	// 0
}













