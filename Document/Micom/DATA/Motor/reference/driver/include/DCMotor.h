#ifndef _DCMOTOR_H_
#define _DCMOTOR_H_


void DCMotor_Init(void);
void DCMotor_Start(void);
void DCMotor_Stop(void);
void DCMotor_SetDuty(unsigned short Duty);				// Duty : 0 ~ 1023	
unsigned short DCMotor_GetDuty(void);			
void DCMotor_SetDirection(unsigned char Direction);		// 0 : CW,  1 : CCW


#endif
