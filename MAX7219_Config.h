/* 
 * File:        MAX7219 Registers and opcodes
 * Author:      H Henning
 * Comments:    All the register addresses and opcodes for the chip is defined here
 * Revision history: V0.1 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAX7219_CONFIG_H
#define	MAX7219_CONFIG_H

//ALL THE REGISTERS USED IN THE MAX7219 CHIP:
#define NO_OP_REG           0x00    //Used for Max7219 Cascading purposes
#define DECODE_MODE_REG     0x09    //Selecting the de-code 8 modes
#define INTESITY_REG        0x0A    //Selecting the LED intensity for display
#define SCAN_LIMIT_REG      0x0B    //Selecting the number of digits to display
#define SHUTDOWN_REG        0x0C    //Selecting the shutdown modes 
#define DISPLAY_TEST_REG    0x0F    //Toggle display test of all LEDs

//ALL THE OPCODES USED IN THE REGISTERS ABOVE:
#define DISABLE_DECODE      0x00    //Do no use decode B mode (7-Segment Mode)
#define MODE1_DECODE        0x01    //Code B decode for digit 0 only, no decode for digits 1-7
#define MODE2_DECODE        0x0F    //Code B decode for digits 0-3 only, no decode for digits 4-7
#define MODE3_DECODE        0xFF    //Code B decode for digits 0-7 (Enable Code B decoding)
#define BRIGHTNESS          0x05    //Can be alterterd to suite requirement, check datasheet
#define SCAN_ALL_DIGITS     0x07    //Display all the digits 0-7, check datasheet for other options
#define SHUTDOWN_MODE       0x00    //Shut off display
#define NORMAL_OPERATION    0x01    //Turn on display
#define DISABLE_TEST        0x00    //Stop LED display test

//PROTOTYPES OF ALL THE FUNCTIONS:
void MAX7219_init(char noChips);
void MAX7219_config(char chip);
void MAX7219_write(char regName,char data,char chip);
void MAX7219_displayText(char* text);
void MAX7219_NoOperation(void);
//------------------------------------------------------------------------------
#endif	/* XC_HEADER_TEMPLATE_H */

