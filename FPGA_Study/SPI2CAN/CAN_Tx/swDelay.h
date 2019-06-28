/* ************************************************************************** */
/** Descriptive File Name: swDelay.h - header file for software delay 
                           implemented by polling the core timer.

  @ Author
    Richard Wall
 
  @ Date
    Created:    May 28, 2016
    Verified:   May 19, 2017
    Revised:    July 8, 2017 - Ported to Arduino 1.8.3
 
  @Company
    Digilent Inc

  @File Name
    swDelay.h

  @Development Environment
     Arduino 1.8.3
     
  @Summary
    Software delay functoon
    
  @Description
    Provides interface to a millisecond and microsecond delay based on the 
    speed of Arduino core timer.
 
  @Precondition
    None

 **************************************************************************** */

#ifndef _SW_DELAY_H    // Guard against multiple inclusion 
    #define _SW_DELAY_H

#endif /* _SW_DELAY_H */

/*  Millisecond software blocking delay function */
void msDelay(unsigned int mS);

/*  Microsecond software blocking delay function */
void usDelay(unsigned int uS);

/*  Millisecond software nonblocking delay function */
int PeriodMs(unsigned int msec);

/* *****************************************************************************
  End of swDelay.h
 */
