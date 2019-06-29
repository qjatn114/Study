/**
* @file		led.c
* @brief		LED  드라이버  
* @author		강이석/ 솔루션 공과 전자 학원 	
* @remarks
* @par 수정이력 
*	@li	2012.11.06 : 초기  함수 작성  
*/

#include "at90can128.h"


// LED 0 ~3 : PORTC4 ~ 7 



/**
* @fn		void LED_Init(void)
* @brief
*	- LED 초기화 함수 
* @remarks
* @param	void
* @return	void			
*/
void LED_Init(void)
{
	// 포트 초기화 
	PORTC &= 0x0F;			// PORTC4 ~ 7에 0 출력
	DDRC |= 0xF0;			// PORTC4 ~ 7를 출력핀으로 만듬.
}

/**
* @fn		void LED0_On(unsigned char OnOff)
* @brief
*	- LED0 를 On/Off 
* @remarks
* @param	unsigned char Data		: On/Off 데이터 
* @return	void			
*/
void LED0_On(unsigned char OnOff)
{
	PORTC4 = (OnOff)? 1 : 0;
}

/**
* @fn		void LED1_On(unsigned char OnOff)
* @brief
*	- LED0 를 On/Off 
* @remarks
* @param	unsigned char Data		: On/Off 데이터 
* @return	void			
*/
void LED1_On(unsigned char OnOff)
{
	PORTC5 = (OnOff)? 1 : 0;
}

/**
* @fn		void LED2_On(unsigned char OnOff)
* @brief
*	- LED0 를 On/Off 
* @remarks
* @param	unsigned char Data		: On/Off 데이터 
* @return	void			
*/
void LED2_On(unsigned char OnOff)
{
	PORTC6 = (OnOff)? 1 : 0;
}

/**
* @fn		void LED3_On(unsigned char OnOff)
* @brief
*	- LED0 를 On/Off 
* @remarks
* @param	unsigned char Data		: On/Off 데이터 
* @return	void			
*/
void LED3_On(unsigned char OnOff)
{
	PORTC7 = (OnOff)? 1 : 0;
}



