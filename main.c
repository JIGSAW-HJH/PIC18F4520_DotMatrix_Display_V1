/*
 * File:   main.c
 * Author: Hendrik
 *
 * Created on 03 November 2022, 7:55 PM
 */

#include <xc.h>
#include "config.h"

#define DIN     LATBbits.LATB0
#define LOAD    LATBbits.LATB1
#define CLK     LATBbits.LATB2


void main(void) {
    //ONE TIME SETUP:
    TRISB = 0;// make all pins outputs on portB
    
    //Make these pins LOW:
    DIN = 0;
    LOAD = 0;
    CLK = 0;
    //INFINITE LOOP:
    while(1)
    {
        
    }//end while
}//end main

void ledTest(void)
{
    //16 bit data packet order:
    //D15 D14 D13 D12 D11 D10 D9 D8 D7 D6 D5 D4 D3 D2 D1 D0
    //D15 D14 D13 D12         -> Dont Care bits
    //D11 D10 D9 D8           -> Address bits
    //D7 D6 D5 D4 D3 D2 D1 D0 -> Data byte
    
    //Test all LEDs on the connected matrices:
    //Display test address: 0xXF    X -> Dont care, thus use 0xFF
    //Display test Data: 0xFF
    //Thus we need to send two bytes of 0xFF to max7219 chip
    
    
}
