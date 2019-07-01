#include "atmega128.h"

#define I2C_SPEED_100KHZ		8			// �� 100KHz 
#define I2C_SPEED_10KHZ			98			// �� 10KHz 

/* TWCR �ڵ�  */
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
	/* ��Ʈ �ʱ�ȭ */
	DDD0 = 0;
	DDD1 = 0;
	PORTD0 = 1;
	PORTD1 = 1;
	
	// I2C �ӵ� ���� : 100KHz
	TWPS1 = 0;	// Precaler : 1
	TWPS0 = 0;
	TWBR = I2C_SPEED_10KHZ;		
	// I2C Ȱ��ȭ 
	TWEN = 1;
}



unsigned char I2C_SendStart(void)
{
	// I2C Ȱ��ȭ 
//	TWEN = 1;

	
	I2C_START_SEND;		// START��Ʈ�� ������. 
	while(!TWINT);		// TWINT�� ���� ����� ���� �Ϸ�� ������ ��ٸ� 
	if((TWSR & I2C_TWISTATUS_MASK) != START_TRANSMITTED)
	{
		I2C_Error();
		return 0;
	}

	return 1;
}

unsigned char I2C_SendRestart(void)
{
	I2C_RESTART_SEND;	// START��Ʈ�� ������. 
	while(!TWINT);		// TWINT�� ���� ����� ���� �Ϸ�� ������ ��ٸ� 
	if((TWSR & I2C_TWISTATUS_MASK) != RE_START_TRANSMITTED)
	{
		I2C_Error();
		return 0;
	}

	return 1;
}

unsigned char I2C_SendMTSlaveAddr(unsigned char SlvAddr)
{
	TWDR = SlvAddr;		// Slave Address�� ����. 
	I2C_DATA_SEND;
	while(!TWINT);			// ���ͷ�Ʈ �÷��׸� ��ٸ�.
	if((TWSR & I2C_TWISTATUS_MASK) != MT_SLA_ACK)
	{
		I2C_Error();
		return 0;
	}

	return 1;
}

unsigned char I2C_SendMRSlaveAddr(unsigned char SlvAddr)
{
	TWDR = SlvAddr;		// Slave Address�� ����. 
	I2C_DATA_SEND;
	while(!TWINT);			// ���ͷ�Ʈ �÷��׸� ��ٸ�.
	if((TWSR & I2C_TWISTATUS_MASK) != MR_SLA_ACK)
	{
		I2C_Error();
		return 0;
	}

	return 1;
}

unsigned char I2C_SendData(unsigned char Data)
{
	TWDR = Data;		// �����͸� ������.
	I2C_DATA_SEND;
	while(!TWINT);			// ���ͷ�Ʈ �÷��׸� ��ٸ�.
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
	while(!TWINT);			// ���ͷ�Ʈ �÷��׸� ��ٸ�.
	if((TWSR & I2C_TWISTATUS_MASK) != MR_DATA_ACK)
	{
		I2C_Error();
		return 0;
	}
	
	*Data = TWDR;		// �����͸� �о�´�. 

	return 1;
}

unsigned char I2C_ReceiveLastData(unsigned char *Data)
{
	I2C_DATA_READ_NACK;
	while(!TWINT);			// ���ͷ�Ʈ �÷��׸� ��ٸ�.
	if((TWSR & I2C_TWISTATUS_MASK) != MR_DATA_NACK)
	{
		I2C_Error();
		return 0;
	}
	
	*Data = TWDR;		// �����͸� �о�´�. 

	return 1;
}


unsigned char I2C_SendStop(void)
{
	// STOP ��Ʈ�� ������.
	I2C_STOP_SEND;
	// ���ͷ�Ʈ �÷��� �ʱ�ȭ 
	while(TWSTO);			// TWSTO �� 0 �� �� ������(Stop ��ȣ�� ������) ��ٸ�.

//	TWINT = 1;
	// ���ͷ�Ʈ �÷��� �ʱ�ȭ 
	TWINT = 1;
	// I2C ��Ȱ��ȭ 
//	TWEN = 0;

	return 0;
}


static void I2C_Error(void)
{
	// ���ͷ�Ʈ �÷��� �ʱ�ȭ 
	TWINT = 1;
	// I2C ��Ȱ��ȭ 
	TWEN = 0;
}




/*
void I2C_Error(void);


void I2C_Init(void)
{
	// I2C �ӵ� ���� : 100KHz
	TWPS1 = 0;	// Precaler : 1
	TWPS0 = 0;
	TWBR = I2C_SPEED_10KHZ;		
	// I2C Ȱ��ȭ 
	TWEN = 1;
}


unsigned char I2C_Write(unsigned char Addr, unsigned char *Data, unsigned char Length)
{
	unsigned char i;

	// I2C Ȱ��ȭ 
	TWEN = 1;
	
	// 1. =====  START ��Ʈ�� ������. =====  
	I2C_START_SEND;		//START��Ʈ�� ������. 
	while(!TWINT);		// ���ͷ�Ʈ �÷��׸� ��ٸ�.
	if((TWSR & 0xF8) != START_TRANSMITTED)
	{
		I2C_Error();
		return 1;
	}

	// 2. =====  �ּҸ� ������. =====	
	TWDR = Addr & 0xFE;		// �ּҸ� ������. (�ݵ�� �ּҸ� ������ ���ͷ�Ʈ �÷��׸� �ʱ�ȭ�Ѵ�.)
	I2C_DATA_SEND;
	while(!TWINT);			// ���ͷ�Ʈ �÷��׸� ��ٸ�.
	if((TWSR & 0xF8) != MT_SLA_ACK)
	{
		I2C_Error();
		return 2;
	}

	// 3. =====  �����͸� ������. =====
	for(i = 0; i < Length; i++)
	{
		TWDR = *Data;		// �����͸� ������.
		I2C_DATA_SEND;
		while(!TWINT);			// ���ͷ�Ʈ �÷��׸� ��ٸ�.
		if((TWSR & 0xF8) != MT_DATA_ACK)
		{
			I2C_Error();
			return 3;
		}
		Data++;
	}
	
	// 4. =====  STOP ��Ʈ�� ������. =====
	I2C_STOP_SEND;


	// ���ͷ�Ʈ �÷��� �ʱ�ȭ 
	TWINT = 1;
	// I2C ��Ȱ��ȭ 
	TWEN = 0;

	return 0;
}

unsigned char I2C_Read(unsigned char Addr, unsigned char *Data, unsigned char Length)
{
	unsigned char i;

	// I2C Ȱ��ȭ 
	TWEN = 1;
	
	// 1. =====  START ��Ʈ�� ������. =====  
	I2C_START_SEND;		//START��Ʈ�� ������. 
	while(!TWINT);		// ���ͷ�Ʈ �÷��׸� ��ٸ�.
	if((TWSR & 0xF8) != START_TRANSMITTED)
	{
		I2C_Error();
		return 1;
	}

	// 2. =====  �ּҸ� ������. =====	
	TWDR = Addr | 0x01;		// �ּҸ� ������. (�ݵ�� �ּҸ� ������ ���ͷ�Ʈ �÷��׸� �ʱ�ȭ�Ѵ�.)
	I2C_DATA_SEND;
	while(!TWINT);			// ���ͷ�Ʈ �÷��׸� ��ٸ�.
	if((TWSR & 0xF8) != MR_SLA_ACK)
	{
		I2C_Error();
		return 2;
	}

	// 3. =====  �����͸� �о�´�. =====
	for(i = 0; i < Length; i++)
	{

		I2C_DATA_READ;
		while(!TWINT);			// ���ͷ�Ʈ �÷��׸� ��ٸ�.
		if((TWSR & 0xF8) != MR_DATA_ACK)
		{
			I2C_Error();
			return 3;
		}

		*Data = TWDR;		// �����͸� ������.
		Data++;		
	}
	
	// 4. =====  STOP ��Ʈ�� ������. =====
	I2C_STOP_SEND;


	// ���ͷ�Ʈ �÷��� �ʱ�ȭ 
	TWINT = 1;
	// I2C ��Ȱ��ȭ 
	TWEN = 0;

	return 0;
}

void I2C_Error(void)
{
	// ���ͷ�Ʈ �÷��� �ʱ�ȭ 
	TWINT = 1;
	// I2C ��Ȱ��ȭ 
	TWEN = 0;


}

*/

