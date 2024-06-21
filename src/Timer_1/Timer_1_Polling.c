// ---------------------------------------------------------------------
// name: Timer_1_Polling.c
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm konfiguriert den Timer0 im Normalmodus.
// Timer zählt aufwärts und generiert einen TOV0-Flag, sobald TCNT0 einen
// Overflow (>0xff) generiert. Aufgrund der immer noch hohen
// Frequenz (30Hz) wird ein zusätzlicher Zähler eingebaut, um die LED
// mit einer Frequenz von 30 Hz blinken zu lassen.
//----------------------------------------------------------------------

#include <avr/io.h>

void main (void) {
  
  // setup LEDs
  DDRD  = 0xff;                             // set all pins on Port D as output
  PORTD = 0x00;                             // clear all outputs
  
  // setup timer
  TCCR0B |= (1 << CS02) | (1 << CS00);      // CLK/1024  (~30Hz)
  
  uint16_t counter = 0;                     // counter

  while(1) {
    
    while((TIFR0 & (1 << TOV0)) == 0) {};   // check TOV0 flag
    
    if (counter < 30) counter++;            // count up to 30; => 1Hz (because CLK/1024 is still 30 Hz)
    else {
      PORTD ^= (1 << 7);                    // toggle LED7
      counter = 0;                          // reset counter
    }
    
    TIFR0 |= (1 << TOV0);                   // clear TOV0 flag 
  }
}