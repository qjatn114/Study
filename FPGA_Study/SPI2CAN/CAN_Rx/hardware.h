/* ************************************************************************** */
/** Descriptive File Name: hardware.h
  @ Author
    Richard Wall
 
  @ Date:       April 30, 2016
    Revised:    December 12, 2016
    Verified:   May 20, 2017
    Revised:    June 19, 2017 - Ported to Arduino 1.8.3

  @Company
    Digilent Inc.      

  @File Name
    hardware.h

  @Development Environment

  @Summary
    Definition of constants and macro routines for the Basys MX3A processor board 

  @Description
    The #define statements and macro C code provides high level access to the 
    Basys MX3A trainer boards switches, push buttons, and LEDs.
    
 */
/* ************************************************************************** */

#include <arduino.h>
#ifndef TRUE
  #define TRUE 1
#endif
#ifndef FALSE
  #define FALSE 0
#endif
  
/* Conditional inclusion prevents multiple definition errors */
#ifndef _HARDWARE_H_   
    #define	_HARDWARE_H_

/* Comment out the following define statement when programmer is NOT used to 
 * allow using BTNL and BTNU as user inputs. Inputs from push buttons BTNL and 
 * BRNU are not functional unless compiled and programmed for stand alone 
 * operation */

    #define DEBUG_MODE  

/* The following definitions are for IO assigned on the Digilent Basys MX3
   processor board. */

/* Macros to configure PIC pins as inputs to sense switch settings */

/* The following macro instruction seta the processor pins for all 8 switch inputs */

/* ------------------------------------------------------------ */
/*          IrDA Pin Declarations                               */
/* ------------------------------------------------------------ */

    #define PIN_IRDA_RX   63
    #define PIN_IRDA_TX   64
    #define PIN_IRDA_PWR  65

/* ------------------------------------------------------------ */
/*          Motor Control Pin Declarations            */
/* ------------------------------------------------------------ */

    #define PIN_AIN1    3
    #define PIN_AIN2    5
    #define PIN_BIN1    6
    #define PIN_BIN2    79
    #define PIN_MOTOR_MODE  78

/* ------------------------------------------------------------ */
/*          7 Segment Display LED Pin Declarations              */
/* ------------------------------------------------------------ */

    #define PIN_CA      69
    #define PIN_CB      70
    #define PIN_CC      71
    #define PIN_CD      72
    #define PIN_CE      73
    #define PIN_CF      74
    #define PIN_CG      75
    #define PIN_DP      76
    #define PIN_ANODE0  37
    #define PIN_ANODE1  38
    #define PIN_ANODE2  41
    #define PIN_ANODE3  42
    
    #define Switch2Binary() (((int) digitalRead(PIN_SW0) << 0 ) +\
                             ((int) digitalRead(PIN_SW1) << 1 ) +\
                             ((int) digitalRead(PIN_SW2) << 2 ) +\
                             ((int) digitalRead(PIN_SW3) << 3 ) +\
                             ((int) digitalRead(PIN_SW1) << 4 ) +\
                             ((int) digitalRead(PIN_SW1) << 5 ) +\
                             ((int) digitalRead(PIN_SW1) << 6 ) +\
                             ((int) digitalRead(PIN_SW1) <<7  ))


/* See http://umassamherstm5.org/tech-tutorials/pic32-tutorials/pic32mx220-tutorials/internal-pull-updown-resistors */
/* Macro instructions to set the push buttons as inputs */

    #define ADCMAX        1023

/* Based upon setting in config_bits.h These directly influence timed
 * events using the Tick module.  They also are used for UART I2C, and SPI
 * baud rate generation. */

    #define XTAL                 (8000000UL)     /* 8 MHz Xtal on Basys MX3A */
    #define GetSystemClock()     (80000000UL)    /* Instruction frequency */
    #define SYSTEM_FREQ          (GetSystemClock())
    #define GetCoreClock()       (GetSystemClock()/2) /* Core clock frequency */
    #define GetPeripheralClock() (GetSystemClock()/8) /* PCLK set for 80 MHz */

/* Used in core timer software delay */
    #define CORE_MS_TICK_RATE	 (unsigned int) (GetCoreClock()/1000UL)

#endif	/* End of _HARDWARE_H_ */

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
void Hardware_Setup(void);

// End of hardware.h 
