#ifndef _I2C_H_
#define _I2C_H_


void I2C_Init(void);
unsigned char I2C_SendStart(void);
unsigned char I2C_SendRestart(void);
unsigned char I2C_SendMTSlaveAddr(unsigned char SlvAddr);
unsigned char I2C_SendMRSlaveAddr(unsigned char SlvAddr);
unsigned char I2C_SendData(unsigned char Data);
unsigned char I2C_ReceiveData(unsigned char *Data);
unsigned char I2C_ReceiveLastData(unsigned char *Data);
unsigned char I2C_SendStop(void);


#endif

