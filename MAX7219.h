/* 
 * File:        All the MAX7219 driver functions
 * Author:      H Henning
 * Comments:    MAX7219 configurations and operation functions
 * Revision history: V0.1
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAX7219_H
#define	MAX7219_H

//INCLUDE THE OTHER HEADER FILES NEEDED FOR OPERATION:
#include "SoftwareSPI.h";       //Pins declarations and configurations
#include "MAX7219_Config.h";    //Chip register and opcodes addresses

//DECLARE NUMBER OF DRIVER CHIPS CASCADED:
void intialise_MAX7219(char numOfChips)
{
    //INITIALISE ALL THE SOFTWARE SPI PINS:
    initialise_SPI();
    //
    while(numOfChips)
    {
        MAX7219_setup(--numOfChips);
    }
}

//SETUP FUNCTION FOR THE MAX7219 CHIPS:
void MAX7219_setup(char chip)
{
  //SET THE MODE OF OPERATION: (7-Segment) or (Dot Matrix)
  MAX7219_write(DECODE_MODE_REG,DISABLE_DECODE,chip);//Set as dot matrix mode
  //SET THE INTENSITY OF THE LED LIGHTS:
  MAX7219_write(INTESITY_REG,BRIGHTNESS,chip);
  //DISPLAY ALL THE DIGITS (ENABLE ALL OF THEM):
  MAX7219_write(SCAN_LIMIT_REG,SCAN_ALL_DIGITS,chip);     
  //SET CHIP INTO NORMAL OPERATIONAL MODE:
  MAX7219_write(SHUTDOWN_REG,NORMAL_OPERATION,chip);
  //DISABLE THE DISPLAY TEST FOR ALL THE LEDS:
  MAX7219_write(DISPLAY_TEST_REG,DISABLE_TEST,chip);   
}

#endif	/* XC_HEADER_TEMPLATE_H */

