/**
* @file		uart.c
* @brief		UART  ����̹�  
* @author		���̼�/�ַ�� ���� ���� �п� 	
* @remarks
* @par �����̷� 
*	@li	2012.11.06 : �ʱ�  �Լ� �ۼ�  
*/

#include "at90can128.h"
#include "uart.h"
#include <avr/interrupt.h>

// UART1 ��� 
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
*	- UART �ʱ�ȭ �Լ� 
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
*	- UART�� 1����Ʈ�� �����͸� �����Ѵ�.  
* @remarks
* @param	unsigned char Data		: ������ 
* @return	void			
*/
void UART_WriteByte(unsigned char Data)
{
	while(UDRE1 == 0);	// UDR �� �� ������ ��ٸ�.
	
	UDR1 = Data;
}


/**
* @fn		void UART_WriteHexa(unsigned char Data)
* @brief
*	- Hexa �����͸� ���ڷ� ��ȯ�ؼ� UART�� �����Ѵ�.   
* @remarks
* @param	unsigned char Data		: ������ 
* @return	void			
*/
void UART_WriteHexa(unsigned char Data)
{
	unsigned char Temp;

	UART_WriteByte('0');
	UART_WriteByte('x');	
	// 1. ���� 4��Ʈ�� ������ �´�. 
	Temp = Data >> 4;	
	// 2. ���ڸ� -> ASCII �� ��ȯ 
	Temp = HexaString[Temp];
	// 3. UART ���� 
	UART_WriteByte(Temp);

	// 1. ���� 4��Ʈ�� ������ �´�.
	Temp = Data & 0x0F; 
	// 2. ���ڸ� -> ASCII �� ��ȯ 
	Temp = HexaString[Temp];
	// 3. UART ���� 
	UART_WriteByte(Temp);
}

/**
* @fn		void UART_WriteDecimal(unsigned short Data)
* @brief
*	-  �����͸� 10���� ���ڷ� ��ȯ�ؼ� UART�� �����Ѵ�.   
* @remarks
* @param	unsigned short Data		: ������ 
* @return	void			
*/
void UART_WriteDecimal(unsigned short Data)
{
	unsigned char Temp;
	/***** 10000 �ڸ� ���� *****/
	// 1. 10000 �ڸ��� ������ �´�. 
	Temp = Data / 10000 % 10;	// 10000 �ڸ�	
	// 2. ���ڸ� -> ASCII �� ��ȯ 
	Temp = HexaString[Temp];
	// 3. UART ���� 
	UART_WriteByte(Temp);

	/***** 1000 �ڸ� ���� *****/
	// 1. 1000 �ڸ��� ������ �´�. 
	Temp = Data / 1000 % 10;	// 1000 �ڸ�	
	// 2. ���ڸ� -> ASCII �� ��ȯ 
	Temp = HexaString[Temp];
	// 3. UART ���� 
	UART_WriteByte(Temp);

	/***** 100 �ڸ� ���� *****/
	// 1. 10000 �ڸ��� ������ �´�. 
	Temp = Data / 100 % 10;	// 100 �ڸ�	
	// 2. ���ڸ� -> ASCII �� ��ȯ 
	Temp = HexaString[Temp];
	// 3. UART ���� 
	UART_WriteByte(Temp);

	/***** 10 �ڸ� ���� *****/
	// 1. 10 �ڸ��� ������ �´�. 
	Temp = Data / 10 % 10;	// 10 �ڸ�	
	// 2. ���ڸ� -> ASCII �� ��ȯ 
	Temp = HexaString[Temp];
	// 3. UART ���� 
	UART_WriteByte(Temp);

	/***** 1 �ڸ� ���� *****/
	// 1. 1 �ڸ��� ������ �´�. 
	Temp = Data % 10;	// 1 �ڸ�	
	// 2. ���ڸ� -> ASCII �� ��ȯ 
	Temp = HexaString[Temp];
	// 3. UART ���� 
	UART_WriteByte(Temp);


}



/**
* @fn		void UART_WriteString(const CHAR *Data)
* @brief
*	- ���ڿ���  UART�� �����Ѵ�.   
* @remarks
* @param	unsigned char Data		: ���ڿ�
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
*	- UART�� ���� �����͸� �����Ѵ�.  
* @remarks
* @param	unsigned char *Data		: ���� �����͸� ���� ������ ������   
* @return	unsigned char
* 	- 0 : ���� �����Ͱ� ���� 
* 	- 1 : ���� �����Ͱ� ���� 	
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
* @param	USART1_RX_vect	: ���ͷ�Ʈ ���� ��ȣ 
* @return	void			
*/
ISR(USART1_RX_vect)
{
	RxdBuffer = UDR1;
	RxdFlag = 1;	
}
