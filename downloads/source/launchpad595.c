// LaunchPad 74HC595 Test
// uses a 74HC595 chip to make a binary counter which counts from 0 to 255 and then resets

// written by gatesphere/suspended-chord (http://suspended-chord.info/)
// 27 August 2010
// placed into the public domain

#define __MSP430G2231__
// #define MSBFIRST //uncomment this line to shift bits out in reverse (most significant bit to least significant bit)
#include <msp430.h>

// pins:
// P1.0 -> data pin DS (pin 14)
// P1.1 -> latch pin RCK (pin 12)
// P1.2 -> clock pin SCK (pin 11)

#define DATAPIN BIT0
#define CLOCKPIN BIT2
#define LATCHPIN BIT1

void shiftOut(char data);

void main() {
  WDTCTL = WDTPW + WDTHOLD;   // kill WDT
  P1OUT = 0x00;
  P1DIR = DATAPIN + CLOCKPIN + LATCHPIN;
  
  
  while(1) {
    volatile unsigned char i = 0;
    volatile unsigned int j;
    while (i < 256) {
      P1OUT &= ~LATCHPIN;           // take latch low
      shiftOut(i);                  // push out i
      P1OUT |= LATCHPIN;            // enable LEDs
      i++;
      for (j = 0; j < 25000; j++);  // delay 25000 cycles
    }
  }
}

void shiftOut(char data) {
  volatile int i;
  char temp, temp2;
#ifdef MSBFIRST // reverse order of the bits
  for (i = 0; i < 8; i++) {
    temp = (0x01 & data);
    data = data >> 1;
    temp2 = (temp2 << 1) + temp;
  }
  data = temp2;
#endif
  for (i = 0; i < 8; i++) {         // 8 bits to a char
    char bittowrite = (0x01 & data); // get bit
    data = data >> 1; // shift data left
    if (bittowrite == 1) {  // send bit
      P1OUT |= DATAPIN;
    } else {
      P1OUT &= ~DATAPIN;
    }
    // pulse clockpin
    P1DIR |= CLOCKPIN;
    P1DIR &= ~CLOCKPIN;
  }
}
