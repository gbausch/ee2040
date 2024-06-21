// ---------------------------------------------------------------------
// name: Timer_1_CTC.c
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm konfiguriert den Timer0 im CTC-Modus und aktiviert 
// den Compate/Match-Interrupt. Der Interrupt wird ausgelöst, sobald TCNT
// den Wert in OCR0A erreicht.
//----------------------------------------------------------------------

#include <avr/io.h>
#include <avr/interrupt.h>

void main (void) {
  
  // setup LEDs
  DDRD  = 0xff;     // set all pins on Port D as output
  PORTD = 0x00;     // clear all outputs
  
  // setup timer w/interrupt and capture/compare in CTC mode
  TCCR0A |= (1 << WGM01);                   // enable timer0 CTC mode
  TIMSK0 |= (1 << OCIE0A);                  // enable timer0 compare interrupt
  
  TCCR0B |= (1 << CS02) | (1 << CS00);      // set prescaler to CLK/1024  (~30Hz)
  
  OCR0A   = 127;                            // set Output Compare Register value  
  sei();                                    // enable global interrupt

  while(1) {}
}

ISR(TIMER0_COMPA_vect) {
  
  static uint8_t counter = 0;               // declare and initialize counter
  
  if (counter < 30) counter++;              // count up to 30; => 1Hz (because CLK/1024 is still 30 Hz)
  else {
    PORTD ^= (1 << 7);                      // toggle LED7
    counter = 0;                            // reset counter
  }
}