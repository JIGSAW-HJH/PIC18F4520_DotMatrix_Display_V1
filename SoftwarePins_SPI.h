/* 
 * File:   Software SPI Pins declaration
 * Author: H Henning
 * Comments: using other pins for spi instead of built in SPI pins of PIC18F4520
 * Revision history: V0.1
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SoftwarePins_SPI_H
#define	SoftwarePins_SPI__H

#include <xc.h> // include processor files - each processor file is guarded.  
//SOFTWARE SPI PINS SELECTION:
#define SCLK       RC2         //Serial Clock
#define SDOUT      RC0         //Serial Data Out
#define SDIN       RC4         //Serial Data In
#define CS0        RC1         //Chip 1 Select
#define CS1        RC3         //Chip 2 Select

//PIN CONFIGURATION SELECTION INPUTS AND OUTPUTS:
#define SCLKpin   TRISC2      //ONLY Set the first half of the pin config
#define SDOUTpin  TRISC0      //ONLY Set the first half of the pin config
#define SDINpin   TRISC4      //ONLY Set the first half of the pin config
#define CS0pin    TRISC1      //ONLY Set the first half of the pin config
#define CS1pin    TRISC3      //ONLY Set the first half of the pin config
//------------------------------------------------------------------------------

#endif	/* XC_HEADER_TEMPLATE_H */

