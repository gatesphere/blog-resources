// LaunchPad Dual Waveform Generator 
// utilizes a TI TLV5618A to generate 2 wave forms simultaneously:
// rising sawtooth and falling sawtooth
// written by suspended-chord/gatesphere (http://suspended-chord.info/)
// released under the GNU GPLv3
#include <msp430.h>
#include "tlv5618a.h"

#define DATAPIN 0 // P1.0 data
#define DATAPORT 1

#define CLOCKPIN 1 // P1.1 clock
#define CLOCKPORT 1

#define LATCHPIN 2 // P1.2 load
#define LATCHPORT 1

#define DELAY 10 // change this value to change the delay between updates and thus frequency

void main() {
  unsigned int cycle = 0;
  volatile unsigned int i;
  // kill WDT+
  WDTCTL = WDTPW + WDTHOLD;
  // initialize things
  P1OUT = 0x00;
  P1DIR = 0xFF; // all output, unused set to low, to save power
  
  while (1) {
    if (cycle > 4095) cycle = 0;
    
    // feed data into DACBUFFER
    tlv5618a_sendData(DACBUFFER, FAST, (4095-cycle), CLOCKPIN, CLOCKPORT, 
                     DATAPIN, DATAPORT, LATCHPIN, LATCHPORT); // falling sawtooth on DACBUFFER
    
    // update DACA, which causes the value in BUFFER to be written to DACB simultaneously
    tlv5618a_sendData(DACA, FAST, cycle, CLOCKPIN, CLOCKPORT, 
                     DATAPIN, DATAPORT, LATCHPIN, LATCHPORT); // rising sawtooth on DACA
    
    cycle++;
    
    // power down to save power (messes up data from DACB)
    //tlv5618a_powerDown(CLOCKPIN, CLOCKPORT, DATAPIN, DATAPORT, LATCHPIN, LATCHPORT);
    
    for (i = 0; i<DELAY; i++);
  }
}
