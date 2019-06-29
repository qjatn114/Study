#ifndef _PWM_H_
#define _PWM_H_

/* PWM 채널 정의 */
#define PWM_CH_A	0x01
#define PWM_CH_B	0x02
#define PWM_CH_C	0x04

void PWM_Init(unsigned char Channels);
void PWM_A_Enable(void);
void PWM_B_Enable(void);
void PWM_C_Enable(void);
void PWM_A_Disable(void);
void PWM_B_Disable(void);
void PWM_C_Disable(void);

void PWM_SetDuty(unsigned short Duty);		// Duty : 0 ~ 1023
void PWM_A_SetDuty(unsigned short Duty);	// Duty : 0 ~ 1023
void PWM_B_SetDuty(unsigned short Duty);	// Duty : 0 ~ 1023
void PWM_C_SetDuty(unsigned short Duty);	// Duty : 0 ~ 1023
unsigned short PWM_A_GetDuty(void);			// Duty : 0 ~ 1023
unsigned short PWM_B_GetDuty(void);			// Duty : 0 ~ 1023
unsigned short PWM_C_GetDuty(void);			// Duty : 0 ~ 1023



#endif
