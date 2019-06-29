#include "remocon.h"
#include "type.h"
#include "atmega128.h"
#include "uart.h"
#include <avr/interrupt.h>


#define NEC_LEADING_CODE_LENGTH  0x103
#define NEC_LOGIC1_CODE_LENGTH  0x40
#define NEC_LOGIC0_CODE_LENGTH  0x20
#define NEC_REPEAT_CODE_LENGTH  0x144
#define NEC_CODE_LENGTH_VARIATION 4
#define NEC_LEADING_CODE 'L'
#define NEC_LOGIC1_CODE  '1'
#define NEC_LOGIC0_CODE  '0'
#define NEC_ERROR_CODE  'E'

Remocon_Handle_t Remocon_Handle = NULL;




void Remocon_Init(void)
{
	/*  Register Init ( Normal Mode : 캡쳐 시간이 변하면 안되므로)  */
	WGM33 = 0;		//0000 : Normal
	WGM32 = 0;
	WGM31 = 0;
	WGM30 = 0;

	ICES3 = 0;		//  0 : Falling edge

	CS32 = 1;		// 100 : 1/256
	CS31 = 0;
	CS30 = 0;

	TICIE3 = 1;		// Capture Interrupt Enable
}

void Remocon_Open(Remocon_Handle_t Handle)
{
	Remocon_Handle = Handle;
	
}

void Remocon_Close(void)
{
	Remocon_Handle = NULL;
}

ISR(TIMER3_CAPT_vect)
{
	uint16_t CurTime;				//현재  시간
	static uint16_t PrevTime;		//과거 시간
	uint16_t Interval;				//시간 간격
	uint8_t Code;	
	static uint8_t State = 0;		// 0 : Leading Pulse 기다리는 상태, 1 : Data 받는 상태
	static uint32_t CodeBits = 0;
	static uint8_t Count = 0;
	/* 길이 계산 */
	CurTime = ICR3L + ( (uint16_t)ICR3H << 8 );
	Interval = CurTime - PrevTime;
	PrevTime = CurTime;
	
	/* 0,1,L 구별 */
	
	if((Interval > (NEC_LEADING_CODE_LENGTH - NEC_CODE_LENGTH_VARIATION))
	 && (Interval < (NEC_LEADING_CODE_LENGTH + NEC_CODE_LENGTH_VARIATION)))
	 {
	 Code = NEC_LEADING_CODE;
	 }
	 else if((Interval > (NEC_LOGIC1_CODE_LENGTH - NEC_CODE_LENGTH_VARIATION))
	 && (Interval < (NEC_LOGIC1_CODE_LENGTH + NEC_CODE_LENGTH_VARIATION)))
	 {
	 Code = NEC_LOGIC1_CODE;
	 }
	 else if((Interval > (NEC_LOGIC0_CODE_LENGTH - NEC_CODE_LENGTH_VARIATION))
	 && (Interval < (NEC_LOGIC0_CODE_LENGTH + NEC_CODE_LENGTH_VARIATION)))
	 {
	 Code = NEC_LOGIC0_CODE;
	 }
	 else
	 {
	 Code = NEC_ERROR_CODE;
	 }
//	 UART_PutChar(Code);

	/* NEC Code 구별 */
	switch(State)
	{
		case 0:			//Leading Pulse 기다리는 상태
			if(Code == 'L')
			{
				State = 1;
				Count = 0;
			}
			break;
		case 1:			// Data 받는 상태
			if(Code == '0')
			{
				CodeBits >>= 1;
				Count++;
			}
			else if(Code == '1')
			{
				CodeBits >>= 1;
				CodeBits |= 0x80000000;
				Count++;
			}
			else if(Code == 'L')
			{
				State = 0;
			}
			else
			{
				State = 0;
			}

			if(Count == 32)
			{
				if(Remocon_Handle)
				{
					Remocon_Handle((CodeBits & 0x00FF0000) >> 16);
				}
				State = 0;
			}
			break;

		default :
			break;
	}
	
}
