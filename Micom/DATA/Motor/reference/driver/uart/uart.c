/**
* @file		uart.c
* @brief		UART  드라이버  
* @author		강이석/솔루션 공과 전자 학원 	
* @remarks
* @par 수정이력 
*	@li	2012.11.06 : 초기  함수 작성  
*/

#include "at90can128.h"
#include "uart.h"
#include <avr/interrupt.h>

// UART1 사용 
// Data bits : 8bit 
// Parity bit : 0
// Stop bit : 1
// Baudrate : 115200

#define UART_BAUDRATE_19200			51
#define UART_BAUDRATE_28800			34
#define UART_BAUDRATE_38400			25
#define UART_BAUDRATE_57600			16
#define UART_BAUDRATE_115200		8
#define UART_BAUDRATE_250000		3


const unsigned char HexaString[] = "0123456789ABCDEF";
unsigned char RxdBuffer;
unsigned char RxdFlag = 0;

/**
* @fn		void UART_Init(void)
* @brief
*	- UART 초기화 함수 
* @remarks
* @param	void
* @return	void			
*/
void UART_Init(void)
{
	UCSR1B = 0x98;
	UCSR1C = 0x06;
	UBRR1H = 0;			// Baudrate : 115200
	UBRR1L = UART_BAUDRATE_38400;
}

/**
* @fn		void UART_WriteByte(unsigned char Data)
* @brief
*	- UART로 1바이트의 데이터를 전송한다.  
* @remarks
* @param	unsigned char Data		: 데이터 
* @return	void			
*/
void UART_WriteByte(unsigned char Data)
{
	while(UDRE1 == 0);	// UDR 이 빌 때까지 기다림.
	
	UDR1 = Data;
}


/**
* @fn		void UART_WriteHexa(unsigned char Data)
* @brief
*	- Hexa 데이터를 문자로 변환해서 UART로 전송한다.   
* @remarks
* @param	unsigned char Data		: 데이터 
* @return	void			
*/
void UART_WriteHexa(unsigned char Data)
{
	unsigned char Temp;

	UART_WriteByte('0');
	UART_WriteByte('x');	
	// 1. 상위 4비트를 가지고 온다. 
	Temp = Data >> 4;	
	// 2. 숫자를 -> ASCII 로 변환 
	Temp = HexaString[Temp];
	// 3. UART 전송 
	UART_WriteByte(Temp);

	// 1. 하위 4비트를 가지고 온다.
	Temp = Data & 0x0F; 
	// 2. 숫자를 -> ASCII 로 변환 
	Temp = HexaString[Temp];
	// 3. UART 전송 
	UART_WriteByte(Temp);
}

/**
* @fn		void UART_WriteDecimal(unsigned short Data)
* @brief
*	-  데이터를 10진수 문자로 변환해서 UART로 전송한다.   
* @remarks
* @param	unsigned short Data		: 데이터 
* @return	void			
*/
void UART_WriteDecimal(unsigned short Data)
{
	unsigned char Temp;
	/***** 10000 자리 전송 *****/
	// 1. 10000 자리를 가지고 온다. 
	Temp = Data / 10000 % 10;	// 10000 자리	
	// 2. 숫자를 -> ASCII 로 변환 
	Temp = HexaString[Temp];
	// 3. UART 전송 
	UART_WriteByte(Temp);

	/***** 1000 자리 전송 *****/
	// 1. 1000 자리를 가지고 온다. 
	Temp = Data / 1000 % 10;	// 1000 자리	
	// 2. 숫자를 -> ASCII 로 변환 
	Temp = HexaString[Temp];
	// 3. UART 전송 
	UART_WriteByte(Temp);

	/***** 100 자리 전송 *****/
	// 1. 10000 자리를 가지고 온다. 
	Temp = Data / 100 % 10;	// 100 자리	
	// 2. 숫자를 -> ASCII 로 변환 
	Temp = HexaString[Temp];
	// 3. UART 전송 
	UART_WriteByte(Temp);

	/***** 10 자리 전송 *****/
	// 1. 10 자리를 가지고 온다. 
	Temp = Data / 10 % 10;	// 10 자리	
	// 2. 숫자를 -> ASCII 로 변환 
	Temp = HexaString[Temp];
	// 3. UART 전송 
	UART_WriteByte(Temp);

	/***** 1 자리 전송 *****/
	// 1. 1 자리를 가지고 온다. 
	Temp = Data % 10;	// 1 자리	
	// 2. 숫자를 -> ASCII 로 변환 
	Temp = HexaString[Temp];
	// 3. UART 전송 
	UART_WriteByte(Temp);


}



/**
* @fn		void UART_WriteString(const CHAR *Data)
* @brief
*	- 문자열을  UART로 전송한다.   
* @remarks
* @param	unsigned char Data		: 문자열
* @return	void			
*/
void UART_WriteString(const char *Data)
{
	while(*Data != 0)
	{
		UART_WriteByte(*Data);
		Data++;	
	}
}

/**
* @fn		unsigned char UART_GetData(unsigned char *Data)
* @brief
*	- UART로 받은 데이터를 전달한다.  
* @remarks
* @param	unsigned char *Data		: 받은 데이터를 받은 변수의 포인터   
* @return	unsigned char
* 	- 0 : 받은 데이터가 없음 
* 	- 1 : 받은 데이터가 있음 	
*/
unsigned char UART_GetData(unsigned char *Data)
{
	if(RxdFlag)
	{
		RxdFlag = 0;
		*Data = RxdBuffer;
		return 1;
	}
	else
	{
		return 0;
	}
}



/**
* @fn		ISR(USART1_RX_vect)
* @brief
*	- UART1 Rx ISR(Interrupt Service Routine) 
* @remarks
* @param	USART1_RX_vect	: 인터럽트 백터 번호 
* @return	void			
*/
ISR(USART1_RX_vect)
{
	RxdBuffer = UDR1;
	RxdFlag = 1;	
}
