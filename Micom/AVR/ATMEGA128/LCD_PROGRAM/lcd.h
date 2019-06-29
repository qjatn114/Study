#ifndef		__lcd__h
#define		__lcd__h

// HD44780 LCD controller command set (do not modify these)
// writing:
#define LCD_CLR             0      // DB0: clear display
#define LCD_HOME            1      // DB1: return to home position
#define LCD_ENTRY_MODE      2      // DB2: set entry mode
#define LCD_ENTRY_INC       1      // DB1: increment
#define LCD_ENTRY_SHIFT     0      // DB2: shift
#define LCD_ON_CTRL         3      // DB3: turn lcd/cursor on
#define LCD_ON_DISPLAY      2      // DB2: turn display on
#define LCD_ON_CURSOR       1      // DB1: turn cursor on
#define LCD_ON_BLINK        0      // DB0: blinking cursor
#define LCD_MOVE            4      // DB4: move cursor/display
#define LCD_MOVE_DISP       3      // DB3: move display (0-> move cursor)
#define LCD_MOVE_RIGHT      2      // DB2: move right (0-> left)
#define LCD_FUNCTION        5      // DB5: function set
#define LCD_FUNCTION_8BIT   4      // DB4: set 8BIT mode (0->4BIT mode)
#define LCD_FUNCTION_2LINES 3      // DB3: two lines (0->one line)
#define LCD_FUNCTION_10DOTS 2      // DB2: 5x10 font (0->5x7 font)
#define LCD_CGRAM           6      // DB6: set CG RAM address
#define LCD_DDRAM           7      // DB7: set DD RAM address
// reading:
#define LCD_BUSY            7      // DB7: LCD is busy

// Default LCD setup
// this default setup is loaded on LCD initialization
#define LCD_FDEF_1          (1<<LCD_FUNCTION_8BIT)
#define LCD_FDEF_2          (0<<LCD_FUNCTION_2LINES)  //9-1 1->0 modify
#define LCD_FUNCTION_DEFAULT    ((1<<LCD_FUNCTION) | LCD_FDEF_1 | LCD_FDEF_2)

#define LCD_MODE_DEFAULT        ((1<<LCD_ENTRY_MODE) | (1<<LCD_ENTRY_INC))


void lcd_init(void);
void lcd_home(void);
void lcd_clear(void);
void lcd_print_data(char* data, u08 n_bytes);
void lcd_control_write(u08 data);
void lcd_data_write(u08 data);  


#endif
