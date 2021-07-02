// ---------------------------------------------------------------------
// name: Timer_1.c
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm konfiguriert den Timer0 im Normalmodus.
// Timer zählt aufwärts und generiert einen TOV0-Flag, sobald TCNT0 einen
// Overflow (>0xff) generiert. Aufgrund der immer noch hohen
// Frequenz (30Hz) wird ein zusätzlicher Zähler eingebaut, um die LED
// mit einer Frequenz von 30 Hz blinken zu lassen.
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>

int main (void)
{
  
  DDRD  = 0xff;     // set all pins on Port D as output
  PORTD = 0x00;     // clear all outputs
  
//  TCCR0B |= (1 << CS00);                  // CLK/1 (no prescaling, ~31.2 kHz (=16.000.000/256/2))
//  TCCR0B |= (1 << CS01);                  // CLK/8   (~3.9 kHz)
//  TCCR0B |= (1 << CS01) | (1 << CS00);    // CLK/64  (~488.2 Hz)
//  TCCR0B |= (1 << CS02);                  // CLK/256 (~122.04 Hz)
  TCCR0B |= (1 << CS02) | (1 << CS00);      // CLK/1024  (~30Hz)
  
  unsigned int counter = 0;                 // counter

  while(1) {
    
    while((TIFR0 & (1 << TOV0)) == 0) {};   // check TOV0 flag
    
    if (counter < 30) counter++;            // count till 30; => 1Hz (because CLK/1024 is still 30 Hz)
    else {
      PORTD ^= (1 << 7);                    // toggle LED7
      counter = 0;                          // reset counter
    }
    
    TIFR0 |= (1 << TOV0);                   // clear TOV0 flag   
    
  }
    
  return 0;
}