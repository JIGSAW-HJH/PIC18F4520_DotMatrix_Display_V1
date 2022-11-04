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
void writeToMax7219(int address[16]);

//Variables Goes Here:
//16 bit data packet order:
// D15 D14 D13 D12 D11 D10 D9 D8 D7 D6 D5 D4 D3 D2 D1 D0

//TODO: change this into one Byte packets, NOT 16Bit Packets!! 16Bit packets does not work...
int noDecodeModePacket[16]  = {0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0};//0x09 0x00
int setScanLimitPacket[16]  = {0,0,0,0,1,0,1,1,0,0,0,0,0,1,1,1};//0x0B 0x??
int ledTestModePacket[16]   = {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1};//0xFF 0x01
int NormalModePacket[16]    = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0};//0xFF 0xFE
int shutdownModeON[16]      = {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};//0xFC 0x00
int shutdownModeOFF[16]     = {1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1};//0xFC 0xFF

void main(void) {
    //ONE TIME SETUP:
    TRISB = 0;// make all pins outputs on portB
    TRISCbits.RC5 = 0;//SDO PIN SPI Serial data output
    TRISCbits.RC4 = 1;//SDI PIN SPI Serial data input
    TRISCbits.RC3 = 0;//SCLK PIN SPI Serial data clock output
    
    //Make these pins LOW:
    DIN = 0;
    LOAD = 0;
    CLK = 0;
    
    LOAD = 1;
    __delay_ms(250);
    LOAD = 0;
    //writeToMax7219(noDecodeModePacket);//set decode mode to NO-Decode
    //writeToMax7219(ledTestModePacket);//Test all leds on the matrix by switching them all on
    //writeToMax7219(setScanLimitPacket);//display all digits 0-7
    __delay_ms(250);
    //writeToMax7219(NormalModePacket);//switch back to normal mode, matrix leds off
    writeToMax7219(shutdownModeON);
    //INFINITE LOOP:
    while(1)
    {
        
    }//end while
}//end main

//
void writeToMax7219(int address[16])
{
    //make sure all pins are low:
    //Make these pins LOW:
    DIN = 0;
    LOAD = 0;
    CLK = 0;
    
    int i = 0;
    //Clock in the 16Bit packet to set decode mode to: No decode mode
    for(i = 0; i < 16; i++)//make this to one byte NOT 2 bytes!!!
    {
        CLK = 0;//Valid data OUT falls on falling edge of CLK
        if(address[i] == 1)
        {//if data bit is a 1, then set DIN to 1:
            DIN = 1;
        }
        else
        {//if data bit is a 0, then set DIN to 0:
            DIN = 0;
        }
        //After setting the DIN pin state, toggle the clock pin:
        CLK = 1;//Valid data IN falls on rising edge of the CLK
    }
    //Done setting Decode mode operation.
    //Latch Output to save data into memory of max7219
    LOAD = 1;
    __delay_ms(10);
    LOAD = 0;
}