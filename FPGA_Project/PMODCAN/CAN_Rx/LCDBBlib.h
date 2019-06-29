/* ************************************************************************** */
/** Descriptive File Name

  @ Author  
     Richard Wall
  @ Date: 
     Created:    August 12, 2013
     Revised:    June 17, 2016 for Basys MX3
                 October 27, 2016 - relabeled defined constants macros
     Verified:   May 20, 2017
     Revised:    July 8, 2017 - Ported to Arduino 1.8.3

  @Company
    Digilent Inc

  @File Name
    LCDBBlib.h

***************************************************************************** */

#include "swDelay.h"
#include <arduino.h>

#ifndef __LCDBBLIB_H__
    #define __LCDBBLIB_H__

    #define lcdRSpin        BIT_15      // RB15
    #define LCDDATA         1           /* address of data register */
    #define LCDCMD          0           /* address of command register */
//	  #define LCD_RS(a)       {if(a) LATBSET = lcdRSpin; else LATBCLR = lcdRSpin;}
	
    #define HLCD            16          /* LCD width = 16 characters */
    #define VLCD            2           /* LCD height = 2 rows */

    #define LCD_CFG         0x38    // Configuration mode for 8 bit data bus
    #define LCD_ENTRY       0x06    // Block flashing cursor - increment power
    #define LCD_ON          0x0F    // Activate LCD
    #define LCD_HOME        0x02    // Put cursor in left most position
    #define LCD_CLR         0x01    // Clear characers off LCD
    #define LCD_MAX_POS     32      // Maximum number of positions for LCD
    #define LCD_NEW_LINE    16      // number of spaces before a new line

//LCD status definitions
    #define LCD_ADDR        0x7F    // Address mask for status register
    #define LCD_BF          0x80    // Busy flag mask for status register
    #define LCD_BF_bit      7       // Busy flag bit for status register
    #define LCD_WRITE       0
    #define LCD_READ        1
    #define LCD_DATAbits    0xFF

/* ------------------------------------------------------------ */
/*          LCD Declarations            */
/* ------------------------------------------------------------ */
    #define PIN_DISP_RW  67
    #define PIN_DISP_RS  68
    #define PIN_DISP_EN  66
    #define PIN_LCD_DB0  26
    #define PIN_LCD_DB1  27
    #define PIN_LCD_DB2  28
    #define PIN_LCD_DB3  29
    #define PIN_LCD_DB4  30
    #define PIN_LCD_DB5  31
    #define PIN_LCD_DB6  32
    #define PIN_LCD_DB7  33

    #define SetLCDOutput() ( pinMode(PIN_LCD_DB0, OUTPUT),\ 
                              pinMode(PIN_LCD_DB1, OUTPUT),\
                              pinMode(PIN_LCD_DB2, OUTPUT),\
                              pinMode(PIN_LCD_DB3, OUTPUT),\
                              pinMode(PIN_LCD_DB4, OUTPUT),\
                              pinMode(PIN_LCD_DB5, OUTPUT),\
                              pinMode(PIN_LCD_DB6, OUTPUT),\
                              pinMode(PIN_LCD_DB7, OUTPUT) )
                              
    #define SetLCDInput()  ( pinMode(PIN_LCD_DB0, INPUT),\ 
                              pinMode(PIN_LCD_DB1, INPUT),\
                              pinMode(PIN_LCD_DB2, INPUT),\
                              pinMode(PIN_LCD_DB3, INPUT),\
                              pinMode(PIN_LCD_DB4, INPUT),\
                              pinMode(PIN_LCD_DB5, INPUT),\
                              pinMode(PIN_LCD_DB6, INPUT),\
                              pinMode(PIN_LCD_DB7, INPUT) )

    #define LCDDataWrite(a) ( digitalWrite( PIN_LCD_DB0, a&0x01),\
                              digitalWrite( PIN_LCD_DB1, a&0x02),\
                              digitalWrite( PIN_LCD_DB2, a&0x04),\
                              digitalWrite( PIN_LCD_DB3, a&0x08),\
                              digitalWrite( PIN_LCD_DB4, a&0x10),\
                              digitalWrite( PIN_LCD_DB5, a&0x20),\
                              digitalWrite( PIN_LCD_DB6, a&0x40),\
                              digitalWrite( PIN_LCD_DB7, a&0x80))

    #define LCDDataRead()   ( (digitalRead ( PIN_LCD_DB0) << 0) +\
                              (digitalRead ( PIN_LCD_DB1) << 1) +\
                              (digitalRead ( PIN_LCD_DB2) << 2) +\
                              (digitalRead ( PIN_LCD_DB3) << 3) +\
                              (digitalRead ( PIN_LCD_DB4) << 4) +\
                              (digitalRead ( PIN_LCD_DB5) << 5) +\
                              (digitalRead ( PIN_LCD_DB6) << 6) +\
                              (digitalRead ( PIN_LCD_DB7) << 7) )

//LCD Address control constants
    #define LCD_DDRAM       0x80    // DD Ram Set Control
    #define LCD_LINE1       0x10    // End of LCD line #1
    #define LCD_LINE2       0x40    // Start of LCD line #2

/* Read LCD busy flag-no delay */
    #define lcdBusy()       lcdRead( LCDCMD) & LCD_BF  
/* Wait for not LCD busy flag-no delay */
    #define lcdWait()       while(lcdBusy()) 
/* Read cursor address with */
    #define lcdAddr()       lcdRead( LCDCMD) & LCD_ADDR  
/* Read RAM at cursor position */
    #define lcdGet()        lcdRead( LCDDATA) 


/* Write single BYTE to CMD with 50 us execution time */
    #define lcdCmd( c)  lcdWait(); lcdWrite( LCDCMD, (c)) 

/* Clear LCD with 1750 us execution time (1530 minimum) */
    #define lcdClr();   {lcdWait(); lcdWrite( LCDCMD, 1); usDelay(1750);}
 /* Set cursor to left with 1750 us execution time (1530 minimum) */
    #define lcdHome();  {lcdWait(); lcdWrite( LCDCMD, 2); usDelay(1750);}

/* Set cursor position.  0 <= pos <= 31 */
    #define lcdGoto(p); {lcdWait(); (p>=16)?lcdWrite(LCDCMD,((p+0x30)|LCD_DDRAM)):lcdWrite(LCDCMD,(p|LCD_DDRAM));}

/* Set address pointer for CGRAM  */
    #define lcdSetG( a) lcdWait(); lcdWrite( LCDCMD, (a & 0x3F) | 0x40)
/* Set address pointer for DDRAM */
    #define lcdSetC( a) lcdWait(); lcdWrite( LCDCMD, (a & 0x7F) | 0x80)

#endif  //__LCDBBLIB_H__

/* initLCD Function Description *********************************************
 * SYNTAX:          void initLCD( void);
 * KEYWORDS:        LCD, Character, Display
 * DESCRIPTION:     Sets up the PMP interface and Initializes a 16x2
 *                  character LCD
 * PARAMETERS:      None
 * RETURN VALUE:    None
 * Notes:           None
 * END DESCRIPTION **********************************************************/
void lcdInit( void);

void lcdWrite( int rs, char c);

/* lcdRead Function Description *******************************************
 * SYNTAX:          char lcdRead( int rs );
 * KEYWORDS:        LCD, Character, read
 * DESCRIPTION:     Writes a single character from the LCD.
 * PARAMETER1:      The RS pin - high for reading DDRAM or CGRAM else low to
 *                  read the address of the DDRAM or CGRAM
 * RETURN VALUE:    Byte read from LCD
 * Notes:           Implements minimum delays for setup and hold times. The 
 *                  Busy flag does not require an execution time delay.
 * 
 * END DESCRIPTION **********************************************************/
char lcdRead( int addr);

/* lcdPuts Function Description ********************************************
 * SYNTAX:          void lcdPuts( char *s);
 * KEYWORDS:        LCD, string, PMP, write
 * DESCRIPTION:     Writes a NULL terminated ASCII string of characters to
 *                  the LCD.
 * PARAMETER1:      character pointer to text string
 * RETURN VALUE:    None
 *
 * Notes:           LF is converted to CLEAR DISPLAY.  CR is converted to
 *                  LINE RETURN, TAB inserts SPACE character to the end 
 *                  of line.
 * END DESCRIPTION *********************************************************/
void lcdPuts( char *s);

/* lcdPutc Function Description *******************************************
 * SYNTAX:          void lcdPutc( int rs, char c);
 * KEYWORDS:        LCD, Character, write
 * DESCRIPTION:     Writes a single character to the LCD.
 * PARAMETER1:      the RS pin
 * PARAMETER2:      c - 8 bit data to write to LCD
 * RETURN VALUE:    None
 * NOTES:           This is a blocking function waiting for the LCD busy flag
 *                  to be set clear.
 *                  
 *                  The LCD data pins must use bit set and bit clear 
 *                  instructions to prevent altering PORT E pins that are not 
 *                  connected to the LCD.
 *                  
 *                  Implements minimum delays for setup and hold times.
 * 
END DESCRIPTION ************************************************************/
void lcdPutc(int rs,  char c);
 
/* End of LCDBBlib.h */
