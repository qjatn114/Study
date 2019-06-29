/* ************************************************************************** */
/** Descriptive File Name

  @ Author  
     Richard Wall
  @ Date: 
     Created:    August 12, 2013
     Revised:    June 17, 2016 for Basys MX3
                 October 27, 2016 - relabeled defined constants macros, and 
                                   function names to put "lcd" at the front.
     Revised:    July 8, 2017 - Ported to Arduino 1.8.3


  @Company
    Digilent Inc

  @File Name
    LCDBBlib.c

  @Development Environment
    MPLAB X IDE x3.61 - http://www.microchip.com/mplab/mplab-x-ide 
	XC32 1.43 - http://www.microchip.com/mplab/compilers
	PLIB 3/7/20162 - http://www.microchip.com/SWLibraryWeb/product.aspx?product=PIC32%20Peripheral%20Library

  @Summary
    Character LCD control using bit-banging.
	
  @Description
    This program provides low level LCD IO control using bit-banging of
    the PIC32 IO pins. The initLCD function must be called before any 
    ASCII characters can be written to the LCD. The readLCD and writeLCD
    functions handle access to both the LCD control registers (RS = 0)
    and the LCD DDRAM/CGRAM (RS = 1). The putsLCD function processes 
    an ASCII string of characters that can contain ASCII control 
    characters LF, CR, and TAB.  The TAB control moves the
    cursor 8 spaces to the right.
 
    Macros provided in LCDBBlib.h provide LCD cursor control and
    character based operations
***************************************************************************** */

/* System included files */
#include <arduino.h>
#include "hardware.h"

/* Application included files */
#include "swDelay.h"		// Required for DelayMs and DelayUs functions
#include "LCDBBlib.h"

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
char lcdRead( int rs)
{
int lcd_ch;
    SetLCDInput();                  // Set processor pins for input
    delayMicroseconds(1);
    digitalWrite(PIN_DISP_RS, rs);  // select command register 
    delayMicroseconds(1);
    digitalWrite(PIN_DISP_RW, LCD_READ);      
    delayMicroseconds(1);
    digitalWrite(PIN_DISP_EN, HIGH);      
	  delayMicroseconds(1);
	  lcd_ch = LCDDataRead();         // read all LCD data pins
    delayMicroseconds(1);
    digitalWrite(PIN_DISP_EN, LOW );      
    delayMicroseconds(1);
    return lcd_ch & LCD_DATAbits;   // mask for actual data
} /* readLCD */

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
void lcdPutc( int rs, char c)    
{
    while(lcdBusy());
    lcdWrite(rs, c);
} // End of lcdPutc 
    

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
void lcdPuts( char *s)
{  
char c = 0;
    while( *s) 
    {
        switch (*s)
        {
        case '\n':          // point to second line 
            lcdSetC( 0x40);
            break;
        case '\r':          // home, point to first line 
            lcdSetC( 0);
            break;
        case '\t':          /* advance next tab (8) positions */
            c = lcdAddr();
            while( c & 7)
            {
                lcdPutc(LCDDATA, ' '); 
                c++;
            }
            if ( c > 15)    // if necessary move to second line
                lcdSetC( 0x40);
            break;                
        default:            // display character 
            c = *s;
            lcdPutc(LCDDATA, c);
            break;
        } /* end switch-case */
        s++;
    } /* End while */
} /* lcdPuts */

/* initLCD Function Description *********************************************
 * SYNTAX:          void initLCD( void);
 * KEYWORDS:        LCD, Character, Display
 * DESCRIPTION:     Sets up the PMP interface and Initializes a 16x2
 *                  character LCD
 * PARAMETERS:      None
 * RETURN VALUE:    None
 * Notes:           None
 * END DESCRIPTION **********************************************************/
void lcdInit( void)
{
/* Set all LCD pins a outputs except the data pins */
    digitalWrite(PIN_DISP_RS, 0);     // select command register 
    digitalWrite(PIN_DISP_RW, LCD_WRITE);      
    SetLCDOutput();                   // Set processor pins for output
    pinMode(PIN_DISP_RW, OUTPUT);     // RD5
    pinMode(PIN_DISP_RS, OUTPUT);     // RB15
    pinMode(PIN_DISP_EN, OUTPUT);     // RD4

// initialize the HD44780 display 8-bit init sequence
    lcdWrite( LCDCMD, LCD_CFG);     // 8-bit int, 2 lines, 5x7
    delay( 50 );                    // > 48ms 

    lcdWrite( LCDCMD, LCD_ON);      // ON, cursor on, blinking
    delay( 40 );                    // > 37ms

    lcdWrite( LCDCMD,  LCD_CLR);    // clear display 
    delay( 2 );                    // > 1.6ms
    
	  lcdWrite( LCDCMD, LCD_ENTRY);   // Entry mode  I/D = 1, SH = 0
    delay( 50 );                    // > 48ms

} /* End of initLCD */

/* lcdWrite Function Description *******************************************
 * SYNTAX:          void lcdWrite( int rs, char c);
 * KEYWORDS:        LCD, Character, PMP, write
 * DESCRIPTION:     Writes a single control character, CGRAMM or DDRAM address, 
 *                  or text character to the LCD.  The busy flag is not checked.
 * PARAMETER1:      Sets the LCD RS pin
 * PARAMETER2:      c - 8 bit data to write to LCD
 * RETURN VALUE:    None
 * Notes:           This is a nonblocking function and may require additional
 *                  delay after calling to meet the LCD timing requirements.
 *                  
 *                  Implements minimum delays for setup and hold times.
 * 
END DESCRIPTION ************************************************************/
void lcdWrite(int rs,  char c)    
{
    
    digitalWrite(PIN_DISP_RS, rs);    // select command register 
	  digitalWrite(PIN_DISP_RW, LCD_WRITE);      
    SetLCDOutput();                   // Set processor pins for output
    delayMicroseconds(1);             // usDelay(1);    
	  LCDDataWrite(c);                  // initiate write sequence
	  delayMicroseconds(1);             // usDelay(1);    
	  digitalWrite(PIN_DISP_EN, HIGH);  // LCD_EN(LCD_HIGH);
	  delayMicroseconds(1);             // usDelay(1);
	  digitalWrite(PIN_DISP_EN, LOW );  // LCD_EN(LCD_LOW);
	  delayMicroseconds(1);             // usDelay(1);
} // lcdWrite 

/* End of LCDBBlib.c */
