/* ************************************************************************** */
/** Descriptive File Name: hardware.c
  @ Author
    Richard Wall
 
  @ Date
    Created:    April 30, 2016
    Revised:    December 10, 2016
    Verified:   May 16, 2017
    Revised:    June 19, 2017 - Ported to Arduino 1.8.3

  @Company
    Digilent Inc.      

  @File Name
    hardware.c

  @Development Environment

	@Summary
    Configure Basys MX3 IO 

  @Description
    The #define statements and macro C code provide high level access to the 
    Basys MX3 Trainer boards switches, push buttons, and LEDs as well as analog inputs.
    
 */
/* ************************************************************************** */

// System included files
#include <arduino.h>
#include "hardware.h"
// *****************************************************************************
/**
  @Function
    void hardware(void);

  @Summary
    Initializes PIC32 pins commonly used for IO on the Basys MX3 Trainer 
    processor board.

  @Description
    Initializes PIC32 digital IO pins to provide functionality for the 
    slide switches, push buttons, and LEDs

  @Parameters
    None

  @Returns
    None
***************************************************************************** */    
void Hardware_Setup(void)
{
    pinMode(PIN_SW0, INPUT);
    pinMode(PIN_SW1, INPUT);
    pinMode(PIN_SW2, INPUT);
    pinMode(PIN_SW3, INPUT);
    pinMode(PIN_SW4, INPUT);
    pinMode(PIN_SW5, INPUT);
    pinMode(PIN_SW6, INPUT);
    pinMode(PIN_SW7, INPUT);

#ifndef DEBUG
    pinMode(PIN_BTNL, INPUT);
    pinMode(PIN_BTNU, INPUT);
#endif
    pinMode(PIN_BTNR, INPUT);
    pinMode(PIN_BTNC, INPUT);
    pinMode(PIN_BTND, INPUT);

    pinMode(PIN_LED0, OUTPUT);
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    pinMode(PIN_LED3, OUTPUT);
    pinMode(PIN_LED4, OUTPUT);
    pinMode(PIN_LED5, OUTPUT);
    pinMode(PIN_LED6, OUTPUT);
    pinMode(PIN_LED7, OUTPUT);
    
    digitalWrite(PIN_LED0, LOW);
    digitalWrite(PIN_LED1, LOW);
    digitalWrite(PIN_LED2, LOW);
    digitalWrite(PIN_LED3, LOW);
    digitalWrite(PIN_LED4, LOW);
    digitalWrite(PIN_LED5, LOW);
    digitalWrite(PIN_LED6, LOW);
    digitalWrite(PIN_LED7, LOW);

    pinMode(PIN_LEDR, OUTPUT);
    pinMode(PIN_LEDG, OUTPUT);
    pinMode(PIN_LEDB, OUTPUT);
    digitalWrite(PIN_LEDR, LOW);
    digitalWrite(PIN_LEDG, LOW);
    digitalWrite(PIN_LEDB, LOW);

/* ------------------------------------------------------------ */
/*          IrDA Pin Initialization                             */
/* ------------------------------------------------------------ */

    pinMode(PIN_IRDA_RX, INPUT);
    pinMode(PIN_IRDA_TX, OUTPUT);
    pinMode(PIN_IRDA_PWR, OUTPUT);

/* ------------------------------------------------------------ */
/*          Motor Control Initialization                        */
/* ------------------------------------------------------------ */
       
    pinMode(PIN_AIN1, OUTPUT);
    pinMode(PIN_AIN2, OUTPUT);
    pinMode(PIN_BIN1, OUTPUT);
    pinMode(PIN_BIN2, OUTPUT);
    pinMode(PIN_MOTOR_MODE, OUTPUT);
    
    digitalWrite(PIN_AIN1, LOW);
    digitalWrite(PIN_AIN2, LOW);
    digitalWrite(PIN_BIN1, LOW);
    digitalWrite(PIN_BIN2, LOW);
    digitalWrite(PIN_MOTOR_MODE, LOW);

/* ------------------------------------------------------------ */
/*          7 Segment Display LED Initialization                */
/* ------------------------------------------------------------ */

    pinMode(PIN_CA, OUTPUT);
    pinMode(PIN_CB, OUTPUT);
    pinMode(PIN_CC, OUTPUT);
    pinMode(PIN_CD, OUTPUT);
    pinMode(PIN_CE, OUTPUT);
    pinMode(PIN_CF, OUTPUT);
    pinMode(PIN_CG, OUTPUT);
    pinMode(PIN_DP, OUTPUT);
    pinMode(PIN_ANODE0, OUTPUT);
    pinMode(PIN_ANODE1, OUTPUT);
    pinMode(PIN_ANODE2, OUTPUT);
    pinMode(PIN_ANODE3, OUTPUT);

/* ------------------------------------------------------------ */
/*          7 Segment Display LED is active LOW                 */
/*          Turn all segments off                               */
/* ------------------------------------------------------------ */
    digitalWrite(PIN_CA, HIGH);
    digitalWrite(PIN_CB, HIGH);
    digitalWrite(PIN_CC, HIGH);
    digitalWrite(PIN_CD, HIGH);
    digitalWrite(PIN_CE, HIGH);
    digitalWrite(PIN_CF, HIGH);
    digitalWrite(PIN_CG, HIGH);
    digitalWrite(PIN_DP, HIGH                                                               );
    digitalWrite(PIN_ANODE0, HIGH);
    digitalWrite(PIN_ANODE1, HIGH);
    digitalWrite(PIN_ANODE2, HIGH);
    digitalWrite(PIN_ANODE3, HIGH);

} /* End of Basys MX3A hardware initialization */

/* End of hardware.c */
