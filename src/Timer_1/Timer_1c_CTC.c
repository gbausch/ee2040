// ---------------------------------------------------------------------
// name: Timer_1c_CTC.c
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm konfiguriert den Timer0 im CTC-Modus und aktiviert 
// den COMPA-Interrupt. Der Interrupt wird ausgelöst, sobald COMPA
// den Wert in OCR0A erreicht. Aufgrund der immer noch hohen
// Frequenz (30Hz) wird ein zusätzlicher Zähler eingebaut, um die LED
// mit einer Frequenz von 30 Hz blinken zu lassen.
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

int main (void)
{
  
  DDRD  = 0xff;     // set all pins on Port D as output
  PORTD = 0x00;     // clear all outputs
  
  TCCR0A |= (1 << WGM01);                   // Waveform Generation Mode: CTC
  OCR0A   = 127;                            // set TOP = 127
  
//  TCCR0B |= (1 << CS00);                  // CLK/1 (no prescaling, ~31.2 kHz (=16.000.000/256/2))
//  TCCR0B |= (1 << CS01);                  // CLK/8   (~3.9 kHz)
//  TCCR0B |= (1 << CS01) | (1 << CS00);    // CLK/64  (~488.2 Hz)
//  TCCR0B |= (1 << CS02);                  // CLK/256 (~122.04 Hz)
  TCCR0B |= (1 << CS02) | (1 << CS00);      // CLK/1024  (~30Hz)
  
  TIMSK0 |= (1 << OCIE0A);                  // Timer/Counter0 Output Compare Match A Interrupt Enable
  sei();                                    // enable global interrupt

  while(1) {}
    
  return 0;
}


ISR(TIMER0_COMPA_vect) {
  
  static unsigned int counter = 0;          // declare and initialize counter
  
  if (counter < 30) counter++;              // count till 30; => 1Hz (because CLK/1024 is still 30 Hz)
  else {
    PORTD ^= (1 << 7);                      // toggle LED7
    counter = 0;                            // reset counter
  } 
  
}