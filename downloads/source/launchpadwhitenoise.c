// white noise generator
// written as a way to become familiar with the MSP430G2 Launchpad
// based on an Arduino sketch available at the following address:
// https://code.google.com/p/greennoise/downloads/detail?name=prbsGen.pde
//
// based on the idea of a linear feedback shift register
//
// written by ~suspended-chord (http://suspended-chord.info/)
// placed into the public domain
// 20 August 2010

#include "msp430g2231.h"

// circuit:
// piezo buzzer from P1.0 to gnd

// definitions
#define BUZZER BIT0 // buzzer on P1.0


// function prototypes
void setup();
void loop();

// global variables
unsigned long int reg;

// Arduino-like paradigm
void main() {
	setup();
	for(;;) { // loop() indefinitely
		loop();
	}
} // end function main()

// initialize the system
void setup() {
	// kill watchdog timer
	WDTCTL = WDTPW + WDTHOLD;
	// set up pin direction and initialize register
  P1OUT = 0x00; // clear initial output, if any
	P1DIR |= BUZZER; // buzzer on P1.0 as output
	reg = 0x0badbeefL; // some arbitrary non-zero initial value
} // end function setup()

// the main workhorse of the program, loops continuously
void loop() {
	unsigned long int newr;
  unsigned char lobit;
  unsigned char b31, b29, b25, b24;
  
  // extract four chosen bits from the 32-bit register
  b31 = (reg & (1uL << 31)) >> 31;
  b29 = (reg & (1L << 29)) >> 29;
  b25 = (reg & (1L << 25)) >> 25;
  b24 = (reg & (1L << 24)) >> 24;
  
  // XOR the four bits together
  lobit = b31 ^ b29 ^ b25 ^ b24;
  
  // shift and incorporate new bit at bit position 0
  newr = (reg << 1) | lobit;
  
  // replace register with new value
  reg = newr;
  
  // drive buzzer from bit 0 of 'reg'
  if (reg & 1) {
  	P1OUT |= BUZZER;
  } else {
  	P1OUT &= ~BUZZER;
  }
} // end function loop()

