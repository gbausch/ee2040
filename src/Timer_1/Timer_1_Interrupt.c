// ---------------------------------------------------------------------
// name: Timer_1_Interrupt.c
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm konfiguriert den Timer0 im Normalmodus und aktiviert 
// den TOV0-Interrupt. Der Interrupt wird ausgelöst, sobald TCNT0 einen
// Overflow (>0xff) generiert. Aufgrund der immer noch hohen
// Frequenz (30Hz) wird ein zusätzlicher Zähler eingebaut, um die LED
// mit einer Frequenz von 30 Hz blinken zu lassen.
//----------------------------------------------------------------------

#include <avr/io.h>
#include <avr/interrupt.h>

int main (void) {
  
  // setup LEDs
  DDRD  = 0xff;                             // set all pins on Port D as output
  PORTD = 0x00;                             // clear all outputs
  
  // setup timer w/interrupt
  TCCR0B |= (1 << CS02) | (1 << CS00);      // CLK/1024  (~30Hz)
  TIMSK0 |= (1 << TOIE0);                   // Timer/Counter0 Overflow Interrupt Enabled
  sei();                                    // enable global interrupt

  while(1) {}
}

ISR(TIMER0_OVF_vect) {
  
  static uint8_t counter = 0;               // declare and initialize counter
  
  if (counter < 30) counter++;              // count up to 30; => 1Hz (because CLK/1024 is still 30 Hz)
  else {
    PORTD ^= (1 << 7);                      // toggle LED7
    counter = 0;                            // reset counter
  } 
}