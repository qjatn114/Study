#include "atmega128.h"
#include "rtc.h"
#include "i2c.h"
#include "uart.h"

#include <avr/interrupt.h>

/* ---------- 핀 맵 ----------
*	RTC_INT : PE5(INT5)
*/


#define PCF8563_I2C_SLV_ADDR			0xA2

// 레지스터 
#define PCF8563_REG_CONTROL_STATUS_1	0x00
#define PCF8563_REG_CONTROL_STATUS_2	0x01
#define PCF8563_REG_VL_SECONDS			0x02
#define PCF8563_REG_MINUTES				0x03
#define PCF8563_REG_HOURS				0x04
#define PCF8563_REG_DAYS				0x05
#define PCF8563_REG_WEEKDAYS			0x06
#define PCF8563_REG_CENTURY_MONTHS		0x07
#define PCF8563_REG_YEARS				0x08

#define PCF8563_REG_MINUTE_ALARM		0x09
#define PCF8563_REG_HOUR_ALARM			0x0A
#define PCF8563_REG_DAY_ALARM			0x0B
#define PCF8563_REG_WEEKDAY_ALARM		0x0C

#define PCF8563_REG_CLKOUT_CONTROL		0x0D
#define PCF8563_REG_TIMER_CONTROL		0x0E
#define PCF8563_REG_TIMER				0x0F


#define CLOCKOUT_FE			7
#define CLOCKOUT_FD1		1
#define CLOCKOUT_FD0		0




uint8_t I2C_TxBuffer[2];
uint8_t I2C_RxBuffer[8];


#define PCF8563_DEBUG		1


static uint8_t PCF8563_Write(uint8_t RegAddr, uint8_t Data);
static uint8_t PCF8563_Read(uint8_t RegAddr);
//static uint8_t PCF8563_ReadSeq(uint8_t StartRegAddr, uint8_t *Buffer, uint8_t Length);

static uint8_t BCD2Hexa(uint8_t BCD_Value);
static uint8_t Hexa2BCD(uint8_t Hexa_Value);


void RTC_Init(void)
{	
	I2C_Init();


	PCF8563_Write(PCF8563_REG_CONTROL_STATUS_1, 0x00);
	PCF8563_Write(PCF8563_REG_CONTROL_STATUS_2, 0x00);

	// Clock out 활성화 , 1Hz
	PCF8563_Write(PCF8563_REG_CLKOUT_CONTROL, (1 << CLOCKOUT_FE) | (1 << CLOCKOUT_FD1) | (1 << CLOCKOUT_FD0));	


	// 인터럽트 활성화 
	// 1. RTC_CLOCK (1Hz 마다 클럭 신호 발생 )
//	ISC51 = 1;		// 11 : 상승 에지, 10 : 하강 에지 
//	ISC50 = 1;

//	INT5 = 1;		// 인터럽트 활성화 
	
	

}

uint8_t RTC_GetTime(RTC_Time_t *Time)
{

	uint8_t Temp;	

	// 초
	Temp = PCF8563_Read(PCF8563_REG_VL_SECONDS);
	Time->Second = BCD2Hexa(Temp & 0x7F);

	// 분
	Temp = PCF8563_Read(PCF8563_REG_MINUTES);
	Time->Minute = BCD2Hexa(Temp & 0x7F);

	// 시 
	Temp = PCF8563_Read(PCF8563_REG_HOURS);
	Time->Hour = BCD2Hexa(Temp & 0x3F);
	
	// 일 
	Temp = PCF8563_Read(PCF8563_REG_DAYS);
	Time->Day = BCD2Hexa(Temp & 0x3F);
	
	// 월 
	Temp = PCF8563_Read(PCF8563_REG_CENTURY_MONTHS);
	Time->Month = BCD2Hexa(Temp & 0x1F);

	// 년 
	Temp = PCF8563_Read(PCF8563_REG_YEARS);
	Time->Year= BCD2Hexa(Temp & 0x1F);

	return 1;
}

void RTC_SetTime(RTC_Time_t Time)
{
	uint8_t Temp;
	// 초
	Temp = Hexa2BCD(Time.Second);
	PCF8563_Write(PCF8563_REG_VL_SECONDS, Temp);
	// 분
	Temp = Hexa2BCD(Time.Minute);
	PCF8563_Write(PCF8563_REG_MINUTES, Temp);
	// 시
	Temp = Hexa2BCD(Time.Hour);
	PCF8563_Write(PCF8563_REG_HOURS, Temp);
	// 일 
	Temp = Hexa2BCD(Time.Day);
	PCF8563_Write(PCF8563_REG_DAYS, Temp);
	// 월 
	Temp = Hexa2BCD(Time.Month);
	PCF8563_Write(PCF8563_REG_CENTURY_MONTHS, Temp);
	// 년 
	Temp = Hexa2BCD(Time.Year);
	PCF8563_Write(PCF8563_REG_YEARS, Temp);
}


static uint8_t PCF8563_Write(uint8_t RegAddr, uint8_t Data)
{

	// Start 신호 송신 
	if(I2C_SendStart() == 0)
	{
		return 0;
	}

	// Slave Address(쓰기 주소)  송신 
	if(I2C_SendMTSlaveAddr(PCF8563_I2C_SLV_ADDR & 0xFE) == 0)
	{
		return 0;
	}

	// Register Address  송신 
	if(I2C_SendData(RegAddr) == 0)
	{
		return 0;
	}
	

	// Data  송신 
	if(I2C_SendData(Data) == 0)
	{
		return 0;
	}

	// Stop  송신 
	I2C_SendStop();

	return 1;
}

static uint8_t PCF8563_Read(uint8_t RegAddr)
{
	uint8_t Buffer;

	// Start 신호 송신 	
	if(I2C_SendStart() == 0)
	{
		return 0;
	}
	// Slave Address(쓰기 주소)  송신 
	if(I2C_SendMTSlaveAddr(PCF8563_I2C_SLV_ADDR & 0xFE) == 0)
	{
		return 0;
	}

	// 읽어올 레지스터 주소(0번부터 읽어온다)
	if(I2C_SendData(RegAddr) == 0)
	{
		return 0;
	}

	// Restart 신호 송신 	
	if(I2C_SendRestart() == 0)
	{
		return 0;
	}

	// Slave Address(읽기 주소)  송신 
	if(I2C_SendMRSlaveAddr(PCF8563_I2C_SLV_ADDR | 0x01) == 0)
	{
		return 0;
	}

	// 데이터를 읽어온다. 
	if(I2C_ReceiveLastData(&Buffer) == 0)
	{
		return 0;
	}		

	// STOP 신호 발생 
	I2C_SendStop();

	return Buffer;
}


/*
static uint8_t PCF8563_ReadSeq(uint8_t StartRegAddr, uint8_t *Buffer, uint8_t Length)
{
	uint8_t i;

	// Start 신호 송신 	
	if(I2C_SendStart() == 0)
	{
		return 0;
	}
	// Slave Address(쓰기 주소)  송신 
	if(I2C_SendMTSlaveAddr(PCF8563_I2C_SLV_ADDR & 0xFE) == 0)
	{
		return 0;
	}

	// 읽어올 레지스터 주소(초부터 읽어온다)
	if(I2C_SendData(PCF8563_REG_VL_SECONDS) == 0)
	{
		return 0;
	}

	// Restart 신호 송신 	
	if(I2C_SendRestart() == 0)
	{
		return 0;
	}

	// Slave Address(읽기 주소)  송신 
	if(I2C_SendMRSlaveAddr(PCF8563_I2C_SLV_ADDR | 0x01) == 0)
	{
		return 0;
	}

	// 데이터를 읽어온다. 
	for(i = 0; i < (Length - 1);i++)
	{
		if(I2C_ReceiveData(&Buffer[i]) == 0)
		{
			return 0;
		}		
	}

	// 마지막 데이터를 읽어온다. 
	if(	I2C_ReceiveLastData(&Buffer[i]) == 0)
	{
		return 0;
	}
	// STOP 신호 발생 
	I2C_SendStop();

	return 1;
}
*/

static uint8_t BCD2Hexa(uint8_t BCD_Value)
{
	uint8_t Hexa_Value;
	
	Hexa_Value = (BCD_Value >> 4) * 10;
	Hexa_Value += BCD_Value & 0x0F;

	return Hexa_Value;
}

static uint8_t Hexa2BCD(uint8_t Hexa_Value)
{
	uint8_t BCD_Value;
	
	BCD_Value = (Hexa_Value / 10) << 4;
	BCD_Value += (Hexa_Value % 10);

	return BCD_Value;
}



/*

ISR(INT5_vect)
{
	uint8_t Temp;	

	// 초
	Temp = PCF8563_Read(PCF8563_REG_VL_SECONDS);
	RTC_Time.Second = BCD2Hexa(Temp & 0x7F);

	// 분
	Temp = PCF8563_Read(PCF8563_REG_MINUTES);
	RTC_Time.Minute = BCD2Hexa(Temp & 0x7F);

	// 시 
	Temp = PCF8563_Read(PCF8563_REG_HOURS);
	RTC_Time.Hour = BCD2Hexa(Temp & 0x3F);
	
	// 일 
	Temp = PCF8563_Read(PCF8563_REG_DAYS);
	RTC_Time.Day = BCD2Hexa(Temp & 0x3F);
	
	// 월 
	Temp = PCF8563_Read(PCF8563_REG_CENTURY_MONTHS);
	RTC_Time.Month = BCD2Hexa(Temp & 0x1F);

	// 년 
	Temp = PCF8563_Read(PCF8563_REG_YEARS);
	RTC_Time.Year= BCD2Hexa(Temp & 0x1F);

	PCF8563_Time_Update = 1;

}
*/



