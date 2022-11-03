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

//Prototypes goes here:
void setNoDecodeMode(void);
void ledTestMode(void);

//Variables Goes Here:
int noDecodeModePacket[16]  = {1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0};//0xF9 0x00
int ledTestModePacket[16]   = {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1};//0xFF 0x01
int NormalModePacket[16]    = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0};//0xFF 0xFE


void main(void) {
    //ONE TIME SETUP:
    TRISB = 0;// make all pins outputs on portB
    
    //Make these pins LOW:
    DIN = 0;
    LOAD = 0;
    CLK = 0;
    
    LOAD = 1;
    __delay_ms(250);
    LOAD = 0;
    setNoDecodeMode();
    ledTestMode();
    //INFINITE LOOP:
    while(1)
    {
        
    }//end while
}//end main

void setNoDecodeMode(void)
{
    //set chip to no decode mode:
    //decode mode address register: 0xF9
    //no decode mode data: 0x00
    //16 bit data packet order:
    // D15 D14 D13 D12 D11 D10 D9 D8 D7 D6 D5 D4 D3 D2 D1 D0
    //  1   1   1   1   1   0   0  1  0  0  0  0  0  0  0  0  
    //        F               9            0           0  
    //      0xF9    0x00
    
    //D15 D14 D13 D12         -> Dont Care bits
    //D11 D10 D9 D8           -> Address bits
    //D7 D6 D5 D4 D3 D2 D1 D0 -> Data byte
    
    //make sure all pins are low:
    //Make these pins LOW:
    DIN = 0;
    LOAD = 0;
    CLK = 0;
    
    int i = 0;
    //Clock in the 16Bit packet to set decode mode to: No decode mode
    for(i = 0; i < 16; i++)
    {
        if(noDecodeModePacket[i] == 1)
        {//if data bit is a 1, then set DIN to 1:
            DIN = 1;
        }
        else
        {//if data bit is a 0, then set DIN to 0:
            DIN = 0;
        }
        //After setting the DIN pin state, toggle the clock pin:
        CLK = 1;//Valid data IN falls on rising edge of the CLK
        //__delay_ms(1);
        CLK = 0;//Valid data OUT falls on falling edge of CLK
        //__delay_ms(1);
    }
    //Done setting Decode mode operation.
    //Latch Output to save data into memory of max7219
    LOAD = 1;
    //__delay_ms(10);
    LOAD = 0;
}

void ledTestMode(void)
{
    //16 bit data packet order:
    // D15 D14 D13 D12 D11 D10 D9 D8 D7 D6 D5 D4 D3 D2 D1 D0
    //  1   1   1   1   1   1   1  1  0  0  0  0  0  0  0  1
    //        F               F             0       1
    //     0xFF     0x01
    
    //D15 D14 D13 D12         -> Dont Care bits
    //D11 D10 D9 D8           -> Address bits
    //D7 D6 D5 D4 D3 D2 D1 D0 -> Data byte
    
    //Test all LEDs on the connected matrices:
    //Display test address: 0xXF    X -> Dont care, thus use 0xFF
    //Display test Data: 0xFF
    //Thus we need to send two bytes of 0xFF to max7219 chip
    
    //make sure all pins are low:
    //Make these pins LOW:
    DIN = 0;
    LOAD = 0;
    CLK = 0;
    
    int i = 0;
    //Clock in the 16Bit packet to set decode mode to: No decode mode
    for(i = 0; i < 16; i++)
    {
        if(ledTestModePacket[i] == 1)
        {//if data bit is a 1, then set DIN to 1:
            DIN = 1;
        }
        else
        {//if data bit is a 0, then set DIN to 0:
            DIN = 0;
        }
        //After setting the DIN pin state, toggle the clock pin:
        CLK = 1;//Valid data IN falls on rising edge of the CLK
        //__delay_ms(1);
        CLK = 0;//Valid data OUT falls on falling edge of CLK
        //__delay_ms(1);
    }
    //Done setting Decode mode operation.
    //Latch Output to save data into memory of max7219
    LOAD = 1;
    //__delay_ms(10);
    LOAD = 0;
    
    
}
