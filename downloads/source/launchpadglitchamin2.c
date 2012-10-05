// LaunchPad-based "glitchamin"
// A photo-sensitive theremin-like noise maker
// Based upon my previous work, the Arduino glitchamin
// (info at http://suspended-chord.info/portfolio/micros/glitchamin-arduino-2010/)
//
// written by suspended-chord/gatesphere (http://suspended-chord.info/)
// Released under the GPLv3.
// version 2 (20100924): Actually works like it's supposed to now.


#define __MSP430G2231__
#include <msp430.h>

#define PHOTOCELL INCH_0 // photocell divider on P1.0/A0
#define CUTTER INCH_1    // cutter pot on P1.1/A1
#define CYCLE INCH_2     // cycle pot on P1.2/A2

#define SPEAKER BIT5     // speaker on P1.5

#define DELAY 5 // adjust for best sound

int analogRead(unsigned int pin);
long map(long x, long in_min, long in_max, long out_min, long out_max);

void main() {
  volatile unsigned int val, cutter, cycle, i, j;
  WDTCTL = WDTPW + WDTHOLD; // kill wdt+
  P1OUT = 0x00;
  P1DIR = SPEAKER;
  
  ADC10CTL0 = ADC10ON + ADC10SHT_0 + SREF_0; // ACD10 on, 4 clock cycles per sample, Use Vcc/Vss references
  
  // change frequency to ~15.25mhz (DCO(15,3))
  BCSCTL1 |= (BIT0 + BIT1 + BIT2 + BIT3);
  DCOCTL &= ~(BIT7);
  DCOCTL |= (BIT6 + BIT5);
  
  for (;;) {
    val = analogRead(PHOTOCELL);
    cutter = map(analogRead(CUTTER), 0, 1023, 15, 2);
    cycle = map(analogRead(CYCLE), 0, 1023, 1, 1000);
    val = (val/cutter) * DELAY;
    
    for (i = 0; i < cycle; i++) {
      P1OUT |= SPEAKER;
      for (j = 0; j < val; j++);
      P1OUT &= ~SPEAKER;
      for (j = 0; j < val; j++);
    }
  }  
}

int analogRead(unsigned int pin) {
  ADC10CTL1 = ADC10SSEL_2 + pin;// Select MCLK and pin
  ADC10CTL0 |= ENC + ADC10SC; // enable and start conversion
  while (1) {
    if ((ADC10CTL1 ^ ADC10BUSY) & ((ADC10CTL0 & ADC10IFG)==ADC10IFG)) { // ensure conversion is complete
      ADC10CTL0 &= ~(ADC10IFG +ENC); // disable conversion and clear flag
      break;
    }
  }
  return ADC10MEM;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
