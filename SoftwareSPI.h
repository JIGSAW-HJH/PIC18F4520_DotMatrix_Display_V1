/* 
 * File:        The software SPI functions 
 * Author:      H Henning
 * Comments:    All the software SPI operations 
 * Revision history: V0.1
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SOFTWARESPI_H
#define	SOFTWARESPI_H

#include "SoftwarePins_SPI.h";//include the software SPI pins config

//INITIALISE THE SPI PIN CONFIGURATIONS FOR SPI
void initialise_SPI(void)
{
    SCLKpin     = 0;    //Set this pin as an output pin
    SDOUTpin    = 0;    //Set this pin as an output pin
    SDINpin     = 1;    //Set this pin as an input pin
    CS0pin      = 0;    //Set this pin as an output pin
    CS1pin      = 0;    //Set this pin as an output pin
}

//SPI TX: TRANSMIT DATA FUNCTION:
void write_SPI(char data)
{
  for(int Tx = 0 ; Tx < 8 ; Tx++ )
  {
    SCLK = 0;//toggle the clock pin
    //shift the data byte out one bit at a time:
    SDOUT = ( (data << Tx) & 0x80 ) ? 1 : 0; //MSB first.
    SCLK = 1;//toggle the clock pin
  }
}

//SPI RX: RECEIVE DATA FUNCTION:
char read_SPI(void)
{
    char data = 0;//declare a character variable to store the incomming data to
    
    for(int Rx = 0 ; Rx < 8 ; Rx++ )
  {
    SCLK = 0;//toggle the clock pin
    //build up the byte string bit by bit
    data += (SDIN << (7-Rx));  //MSB first.
    SCLK = 1;//toggle the clock pin
  }
    //once data is received, return it
    return data;
}

#endif	/* XC_HEADER_TEMPLATE_H */

