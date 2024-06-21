// ---------------------------------------------------------------------
// name: Timer_2.c
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm konfiguriert den Timer0 im PWM-Modus und gibt das PWM-Signal
// über den Pin PD6 aus.
//----------------------------------------------------------------------

#include <avr/io.h>

int main (void) {
  
  DDRD  = 0xff;                             // set Port D as output
  PORTD = 0x00;                             // clear all pins
  
  TCCR0A |= (1 << WGM02) | (1 << WGM00);    // Waveform Generation Mode: PWM
  TCCR0A |= (1 << COM0A1);                  // Clear OC0A on compare match
  TCCR0B |= (1 << CS02) | (1 << CS00);      // CLK/1024  (~30Hz)
  
  OCR0A = 127;                              // duty cycle = 50%
                                            // duty cycle = 25% (64)
                                            // duty cycle = 75% (191)

  while(1) {}
}