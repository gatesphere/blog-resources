// LaunchPad Quad Waveform Generator
// utilizes a TI TLV5620 to generate 4 wave forms simultaneously:
// sine, rising sawtooth, triangle, and square
// written by suspended-chord/gatesphere (http://suspended-chord.info/)
// released under the GNU GPLv3
#include <msp430.h>
#include "tlv5620.h"

#define DATAPIN 0 // P1.0 data
#define DATAPORT 1

#define CLOCKPIN 2 // P1.2 clock
#define CLOCKPORT 1

#define LOADPIN 3 // P1.3 load
#define LOADPORT 1

#define LDACPIN 1 // P1.1 ldac
#define LDACPORT 1

#define DELAY 500 // change this value to change the delay between updates and thus frequency

unsigned char sinTable[32] = {
127,152,176,198,217,233,245,252,254, 
252,245,233,217,198,176,152,128,103,
79, 57, 38, 22, 10, 3,  0,  3,  10,
22, 38, 57, 79, 103};

void main() {
  unsigned char cycle, value;
  volatile unsigned int i;
  // kill WDT+
  WDTCTL = WDTPW + WDTHOLD;
  // initialize things
  P1OUT = 0x00;
  P1DIR = 0x0F;
  // change frequency to ~15.25mhz (DCO(15,3))
  BCSCTL1 |= (BIT0 + BIT1 + BIT2 + BIT3);
  DCOCTL &= ~(BIT7);
  DCOCTL |= (BIT6 + BIT5);
  
  tlv5620_updateMode(SIMULTANEOUS, LDACPIN, LDACPORT); // simultaneous update
  
  while (1) {
    if (cycle > 31) cycle = 0;
    
    tlv5620_sendData(DACA, GAIN1X, sinTable[cycle], CLOCKPIN, CLOCKPORT, 
                     DATAPIN, DATAPORT, LOADPIN, LOADPORT); // sine wave on DACA

    tlv5620_sendData(DACB, GAIN1X, cycle*8, CLOCKPIN, CLOCKPORT, 
                     DATAPIN, DATAPORT, LOADPIN, LOADPORT); // rising sawtooth on DACB
    
    if (cycle < 16) value = cycle*16; else value = (31-cycle)*16;
    tlv5620_sendData(DACC, GAIN1X, value, CLOCKPIN, CLOCKPORT, 
                     DATAPIN, DATAPORT, LOADPIN, LOADPORT); // triangle wave on DACC
   
    if (cycle < 16) value = 0; else value = 255;
    tlv5620_sendData(DACD, GAIN1X, value, CLOCKPIN, CLOCKPORT, 
                     DATAPIN, DATAPORT, LOADPIN, LOADPORT); // square wave on DACD
    
    tlv5620_simultaneousUpdate(LDACPIN, LDACPORT); // update simultaneously
    
    cycle++;
    
    for (i = 0; i<DELAY; i++);
  }
}
