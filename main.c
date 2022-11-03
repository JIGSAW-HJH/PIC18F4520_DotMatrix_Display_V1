/*
 * File:   main.c
 * Author: Hendrik
 *
 * Created on 03 November 2022, 7:55 PM
 */

#include <xc.h>
#include "config.h"

void main(void) {
    //ONE TIME SETUP:
    TRISB = 0;// make all pins outputs on portB
    
    //Make these pins LOW:
    LATBbits.LATB0 = 0;
    LATBbits.LATB1 = 0;
    LATBbits.LATB2 = 0;
    //INFINITE LOOP:
    while(1)
    {
        LATBbits.LATB0 = 0;
        __delay_ms(250);
        LATBbits.LATB1 = 0;
        __delay_ms(250);
        LATBbits.LATB2 = 0;
        __delay_ms(250);
    }//end while
}//end main
