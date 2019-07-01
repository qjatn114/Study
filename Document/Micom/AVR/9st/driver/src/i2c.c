#include "atmega128.h"

#define I2C_SPEED_100KHZ		8			// 약 100KHz 
#define I2C_SPEED_10KHZ			98			// 약 10KHz 

/* TWCR 코드  */
#define I2C_START_SEND			TWCR=0xA4
#define I2C_RESTART_SEND		TWCR=0xA4
#define I2C_DATA_SEND			TWCR=0x84
#define I2C_DATA_READ_ACK		TWCR=0xC4
#define I2C_DATA_READ_NACK		TWCR=0x84
#define I2C_STOP_SEND			TWCR=0x94

/* TWI Status Code */
#define START_TRANSMITTED			0x08
#define RE_START_TRANSMITTED		0x10
#define MT_SLA_ACK					0x18
#define MT_SLA_NACK					0x20
#define MT_DATA_ACK					0x28
#define MT_DATA_NACK				0x30
#define ARBITRATION_LOST			0x38
#define MR_SLA_ACK					0x40
#define MR_SLA_NACK					0x48
#define MR_DATA_ACK					0x50
#define MR_DATA_NACK				0x58

#define I2C_TWISTATUS_MASK			0xF8


static void I2C_Error(void);


void I2C_Init(void)
{
	/* 포트 초기화 */
	DDD0 = 0;
	DDD1 = 0;
	PORTD0 = 1;
	PORTD1 = 1;
	
	// I2C 속도 설정 : 100KHz
	TWPS1 = 0;	// Precaler : 1
	TWPS0 = 0;
	TWBR = I2C_SPEED_10KHZ;		
	// I2C 활성화 
	TWEN = 1;
}



unsigned char I2C_SendStart(void)
{
	// I2C 활성화 
//	TWEN = 1;

	
	I2C_START_SEND;		// START비트를 보낸다. 
	while(!TWINT);		// TWINT를 보고 명령이 실행 완료될 때까지 기다림 
	if((TWSR & I2C_TWISTATUS_MASK) != START_TRANSMITTED)
	{
		I2C_Error();
		return 0;
	}

	return 1;
}

unsigned char I2C_SendRestart(void)
{
	I2C_RESTART_SEND;	// START비트를 보낸다. 
	while(!TWINT);		// TWINT를 보고 명령이 실행 완료될 때까지 기다림 
	if((TWSR & I2C_TWISTATUS_MASK) != RE_START_TRANSMITTED)
	{
		I2C_Error();
		return 0;
	}

	return 1;
}

unsigned char I2C_SendMTSlaveAddr(unsigned char SlvAddr)
{
	TWDR = SlvAddr;		// Slave Address를 쓴다. 
	I2C_DATA_SEND;
	while(!TWINT);			// 인터럽트 플래그를 기다림.
	if((TWSR & I2C_TWISTATUS_MASK) != MT_SLA_ACK)
	{
		I2C_Error();
		return 0;
	}

	return 1;
}

unsigned char I2C_SendMRSlaveAddr(unsigned char SlvAddr)
{
	TWDR = SlvAddr;		// Slave Address를 쓴다. 
	I2C_DATA_SEND;
	while(!TWINT);			// 인터럽트 플래그를 기다림.
	if((TWSR & I2C_TWISTATUS_MASK) != MR_SLA_ACK)
	{
		I2C_Error();
		return 0;
	}

	return 1;
}

unsigned char I2C_SendData(unsigned char Data)
{
	TWDR = Data;		// 데이터를 보낸다.
	I2C_DATA_SEND;
	while(!TWINT);			// 인터럽트 플래그를 기다림.
	if((TWSR & I2C_TWISTATUS_MASK) != MT_DATA_ACK)
	{
		I2C_Error();
		return 0;
	}

	return 1;
}

unsigned char I2C_ReceiveData(unsigned char *Data)
{
	I2C_DATA_READ_ACK;
	while(!TWINT);			// 인터럽트 플래그를 기다림.
	if((TWSR & I2C_TWISTATUS_MASK) != MR_DATA_ACK)
	{
		I2C_Error();
		return 0;
	}
	
	*Data = TWDR;		// 데이터를 읽어온다. 

	return 1;
}

unsigned char I2C_ReceiveLastData(unsigned char *Data)
{
	I2C_DATA_READ_NACK;
	while(!TWINT);			// 인터럽트 플래그를 기다림.
	if((TWSR & I2C_TWISTATUS_MASK) != MR_DATA_NACK)
	{
		I2C_Error();
		return 0;
	}
	
	*Data = TWDR;		// 데이터를 읽어온다. 

	return 1;
}


unsigned char I2C_SendStop(void)
{
	// STOP 비트를 보낸다.
	I2C_STOP_SEND;
	// 인터럽트 플래그 초기화 
	while(TWSTO);			// TWSTO 가 0 이 될 때까지(Stop 신호가 보내짐) 기다림.

//	TWINT = 1;
	// 인터럽트 플래그 초기화 
	TWINT = 1;
	// I2C 비활성화 
//	TWEN = 0;

	return 0;
}


static void I2C_Error(void)
{
	// 인터럽트 플래그 초기화 
	TWINT = 1;
	// I2C 비활성화 
	TWEN = 0;
}




/*
void I2C_Error(void);


void I2C_Init(void)
{
	// I2C 속도 설정 : 100KHz
	TWPS1 = 0;	// Precaler : 1
	TWPS0 = 0;
	TWBR = I2C_SPEED_10KHZ;		
	// I2C 활성화 
	TWEN = 1;
}


unsigned char I2C_Write(unsigned char Addr, unsigned char *Data, unsigned char Length)
{
	unsigned char i;

	// I2C 활성화 
	TWEN = 1;
	
	// 1. =====  START 비트를 보낸다. =====  
	I2C_START_SEND;		//START비트를 보낸다. 
	while(!TWINT);		// 인터럽트 플래그를 기다림.
	if((TWSR & 0xF8) != START_TRANSMITTED)
	{
		I2C_Error();
		return 1;
	}

	// 2. =====  주소를 보낸다. =====	
	TWDR = Addr & 0xFE;		// 주소를 보낸다. (반드시 주소를 보내고 인터럽트 플래그를 초기화한다.)
	I2C_DATA_SEND;
	while(!TWINT);			// 인터럽트 플래그를 기다림.
	if((TWSR & 0xF8) != MT_SLA_ACK)
	{
		I2C_Error();
		return 2;
	}

	// 3. =====  데이터를 보낸다. =====
	for(i = 0; i < Length; i++)
	{
		TWDR = *Data;		// 데이터를 보낸다.
		I2C_DATA_SEND;
		while(!TWINT);			// 인터럽트 플래그를 기다림.
		if((TWSR & 0xF8) != MT_DATA_ACK)
		{
			I2C_Error();
			return 3;
		}
		Data++;
	}
	
	// 4. =====  STOP 비트를 보낸다. =====
	I2C_STOP_SEND;


	// 인터럽트 플래그 초기화 
	TWINT = 1;
	// I2C 비활성화 
	TWEN = 0;

	return 0;
}

unsigned char I2C_Read(unsigned char Addr, unsigned char *Data, unsigned char Length)
{
	unsigned char i;

	// I2C 활성화 
	TWEN = 1;
	
	// 1. =====  START 비트를 보낸다. =====  
	I2C_START_SEND;		//START비트를 보낸다. 
	while(!TWINT);		// 인터럽트 플래그를 기다림.
	if((TWSR & 0xF8) != START_TRANSMITTED)
	{
		I2C_Error();
		return 1;
	}

	// 2. =====  주소를 보낸다. =====	
	TWDR = Addr | 0x01;		// 주소를 보낸다. (반드시 주소를 보내고 인터럽트 플래그를 초기화한다.)
	I2C_DATA_SEND;
	while(!TWINT);			// 인터럽트 플래그를 기다림.
	if((TWSR & 0xF8) != MR_SLA_ACK)
	{
		I2C_Error();
		return 2;
	}

	// 3. =====  데이터를 읽어온다. =====
	for(i = 0; i < Length; i++)
	{

		I2C_DATA_READ;
		while(!TWINT);			// 인터럽트 플래그를 기다림.
		if((TWSR & 0xF8) != MR_DATA_ACK)
		{
			I2C_Error();
			return 3;
		}

		*Data = TWDR;		// 데이터를 보낸다.
		Data++;		
	}
	
	// 4. =====  STOP 비트를 보낸다. =====
	I2C_STOP_SEND;


	// 인터럽트 플래그 초기화 
	TWINT = 1;
	// I2C 비활성화 
	TWEN = 0;

	return 0;
}

void I2C_Error(void)
{
	// 인터럽트 플래그 초기화 
	TWINT = 1;
	// I2C 비활성화 
	TWEN = 0;


}

*/

