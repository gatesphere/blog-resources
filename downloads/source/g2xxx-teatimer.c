// MSP430 based Tea Timer
// Sets off a buzzer to let you know when your tea is done steeping
// Supports several types of tea

// suspended-chord (http://blog.suspended-chord.info)

/* Tea steeping chart
   Tea type             Time         DIP Code
   ------------------------------------------
   White                2 minutes         000
   Green                3 minutes         001
   Black/Oolong         4 minutes         010
   Herbal               5 minutes         011
   Chai                 8 minutes         100
   Rooibos              6 minutes         101
   Other                1 minute          110
   Other 2              30 seconds        111
*/

// circuit:
// LED on P1.0
// Piezo buzzer with driver on P1.1
// 3-switch dip (or 3 toggle switches) on P1.4, P1.5, and P1.6
// push button tact on P1.3, pullup resistor

//#define DEBUG

#define __MSP430G2231__
#include <msp430.h>

// pin for status LED
#define LED BIT0
// pin for buzzer
#define BUZZER BIT1
// pin for start switch
#define START BIT3
// three consecutive pins for mode selection
#define INPUT1 BIT4
#define INPUT2 BIT5
#define INPUT3 BIT6
// numeric value of the first pin
#define SHIFT 4
// unused bits
#define UNUSED BIT2 + BIT7

// variables
unsigned int goal = 0;
unsigned int tickCount = 0;
unsigned char statusCount = 0;
char statusMode = 0;
char mode = 0;
char reset = 0;
volatile unsigned int i = 0;

void main() {
  while(1) {
    WDTCTL = WDTPW + WDTHOLD; // kill wdt
    P1OUT = 0; // clear outputs
    P1DIR = LED + BUZZER + UNUSED; // setup outputs and unused to out/low to reduce power consumption
    
    
    BCSCTL1 = CALBC1_1MHZ; // setup DCO
    DCOCTL = CALDCO_1MHZ;
    
    // setup TimerA
    TACCR0 = 62499; // .5s cycle with 1MHZ clk and /8 divider
    
    // delay a few cycles to debounce
    i = 0;
    while (i < 50000) i++;
      
    while ((P1IN & START) == START) { // keep setting mode until start switch is pressed
      // setup mode
      mode = (P1IN & (INPUT1 + INPUT2 + INPUT3)) >> SHIFT;
      
      // setup goal
      switch (mode) {
        case 0: // white tea
          goal = 240; // 2 minutes
          break;
        case 1: // green tea
          goal = 360; // 3 minutes
          break;
        case 2: // black/oolong tea
          goal = 480; // 4 minutes
          break;
        case 3: // herbal tea
          goal = 600; // 5 minutes
          break;
        case 4: // chai tea
          goal = 960; // 8 minutes
          break;
        case 5: // rooibos tea
          goal = 720; // 6 minutes
          break;
        case 6: // other
          goal = 120; // 1 minute
          break;
        case 7: // other2
          goal = 60; // 30 seconds
            break;
          default:
            goal = 0;
       }
     }
      
#ifdef DEBUG
    goal = 30; // 15 seconds
#endif  
      
    // reset the TAR, and finish setting up TimerA
    TACTL = TASSEL_2 + ID_3 + MC_1 + TACLR; // select SMCLK/8, up mode, and clear the TAR
    TACCTL0 = CCIE; // enable interrupts
    
    // enable interrupts
    _enable_interrupt();
    
    // turn on LED
    P1OUT |= LED;
    
    // reset variables
    statusCount = statusMode = tickCount = reset = 0;
    
    // enter LPM1
    //LPM1;
    while (reset == 0);
  }
}

// timerA interrupt for CCR0
#pragma vector = TIMERA0_VECTOR
__interrupt void CCR0_ISR (void) {
  tickCount++; // increase tick count
  
  // toggle LED increasingly faster as the time counts towards the end
  statusCount++;
  if (tickCount >= goal/4) statusMode = 1;
  if (tickCount >= goal/2) statusMode = 2;
  if (tickCount >= 3*(goal/4)) statusMode = 3;
  switch (statusMode) {
    case 0:
      if (statusCount >= 4) { // blink every 2 seconds
        P1OUT ^= LED; // toggle LED
        statusCount = 0;
      }
      break;
    case 1:
      if (statusCount >= 3) { // blink every 1.5 seconds
        P1OUT ^= LED; // toggle LED
        statusCount = 0;
      }
      break;
    case 2:  
      if (statusCount >= 2) { // blink every 1 second
        P1OUT ^= LED; // toggle LED
        statusCount = 0;
      }
      break; 
    case 3: default: // blink every .5 second
      P1OUT ^= LED; // toggle LED
      statusCount = 0;
      break;
  }
  
  if (tickCount >= goal) {
    _disable_interrupt(); // kill interrupts
    TACCTL0 &= ~CCIE; // disable TimerA CCR0 interrupt
    //LPM1_EXIT; // exit LPM1
    P1OUT |= LED + BUZZER; // buzzer + LED on
    while ((P1IN & START) == START); // if START pressed, return to main()
    reset = 1;
  }
}


