/* CAN Receive Example
** 
**
** Ported to the Digilent Basys MX3 and PmodCAN
** Richard W. Wall
** July 8, 2017
** 
** Based on example code and CAN library functions
** Posted at https://github.com/Seeed-Studio/CAN_BUS_Shield/tree/master/examples
**
**  Based on code published at:
**  https://github.com/Seeed-Studio/CAN_BUS_Shield
*/

#include <arduino.h>
#include "hardware.h"     // Basys MX3 common hardware pin assignments
#include "LCDBBlib.h"     // Bit banged LCD library
#include "led7.h"         // 4 digit 7 segment LED library
#include "swDelay.h"      // Software delays
#include "MCP_CAN.h"      // MCP25625 library
#include "MCP_CAN_DFS.h"  // MCP25625 definitions
#include "spiJA.h"        // SPI2 library

long unsigned int rxId;   // Receive CAN ID
unsigned char len = 0;    // CAN message length
unsigned char rxBuf[8];   // CAN receive buffer
char msgString[128];      // Array to store serial string

extern int16_t led_value; // 4 digit 7 segment dispaly value
extern int16_t led_flag;  // 4 digit 7 segment dispaly on-off control


#define CAN0_INT 35       // Set INT to pin 35 (RC3)
MCP_CAN CAN0(10);         // Set CS to pin 10 (RC2)


void setup()
{
  Serial.begin(38400);
  lcdInit();
  lcdPuts("CAN Rx Demo");
  seg7Init();               // Turn on 7 segment displays
  
  // Initialize MCP25625 running at 20MHz with a baudrate of 250kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_250KBPS, MCP_20MHZ) == CAN_OK) 
    Serial.println("MCP25625 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP25625...");

  CAN0.setMode(MCP_NORMAL);      // Set operation mode to normal so the MCP25625 sends acks to received data.

  pinMode(CAN0_INT, INPUT);      // Configuring pin for /INT input
  
  Serial.println("MCP25625 Library Receive Example...");

  led_flag = 1;                 // Turn on 4 digit 7 segment display
  led_value = 0;                // Set LED display value to zero
}

void loop()
{
char lcdStr[33];
byte i;
int msg_cntr;

  if(!digitalRead(CAN0_INT))     // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    
    if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
  
    Serial.print(msgString);
  
    if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } 
    else 
    {
      for(i = 0; i<len; i++)
      {
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);
      }
    }

// Show message on LED
    msg_cntr = ((int) rxBuf[0]) + (((int) rxBuf[1]) << 8);
    led_value = msg_cntr % 9999; // 4 digit display
    
 // Show message count on LCD
    lcdGoto(16);                      // Set LCD cursor to 2nd line
    lcdPuts("                ");      // Clear LCD 2nd line
    lcdGoto(16);                      // Set LCD cursor to 2nd line
    sprintf(lcdStr,"Received: %d", led_value);  // format string
    lcdPuts(lcdStr);                  // Display count on LCD

    sprintf(msgString, "  -- %d", led_value); // Add message count to serial UART string
    Serial.print(msgString);
    Serial.println();
  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
