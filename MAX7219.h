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

//WRITE FUNCTION FOR THE MAX7219 CHIP:
void MAX7219_write(char registerName,char registerData,char chip)
{
  CS0 = 0;  //Pull the LOAD pin of the max7219 to 0
   
  write_SPI(registerName); //First write the register to update,
  write_SPI(registerData); //Then write the data for that register to update
  //For the rest of the other chips, do not update anything to them:
  while(chip--)
       MAX7219_NoOperation();        //Used for daisy chained (Cascaded) arrangements
  
  CS0 = 1;  //Set the LOAD pin of the max7219 to 1 (latch the output)
}

//FUNCTION TO DISPLAY TECT ON TO THE DOT MATRIC DISPLAY:
void MAX7219_displayText(char* text)// example of text: "HELLO", thus its actually an array of chars, thats why the pointer is there...
{ 
  char chip = 0;// start at the 1st chip (aka the MSB chip, the last one)
 
  while(*text)
  { 
    //(Text-32)...because the first 32 ASCII character codes are none Printable (control chars)
    char row = (*text++) - 32;//convert your text to ascii range..
    //the ++ next to text is to increment the "array" of text to the next character
    for(int col = 0; col < 8; col++)
    {
      MAX7219_write( col, symbol[row][col], chip );
    }
    
    chip++;// go to the next chip, (aka previous chip)
  }
}

//FUNCTION TO PASS ON THE DATA TO THE NEXT CHIP: (Basically its a NOP)
void MAX7219_NoOperation()
{
  write_SPI(NO_OP_REG);           
  write_SPI(0x00);       //Don't care (Can be any arbitrary value)
}

#endif	/* XC_HEADER_TEMPLATE_H */

