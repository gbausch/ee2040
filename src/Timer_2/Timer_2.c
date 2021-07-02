// ---------------------------------------------------------------------
// name: Timer_2.c
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm konfiguriert den Timer0 im PWM-Modus und gibt das PWM-Signal
// über den Pin PD6 aus.
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>

int main (void)
{
  
  DDRD  = 0xff;     // set all pins on Port D as output
  PORTD = 0x00;     // clear all outputs
  
  TCCR0A |= (1 << WGM01) | (1 << WGM00);    // Waveform Generation Mode: Fast PWM
  TCCR0A |= (1 << COM0A1);                  // Clear OC0A on compare match
  
  OCR0A = 127;                              // duty cycle = 50%
                                            // duty cycle = 25% (64)
                                            // duty cycle = 75% (191)
  
//  TCCR0B |= (1 << CS00);                  // CLK/1 (no prescaling, ~31.2 kHz (=16.000.000/256/2))
//  TCCR0B |= (1 << CS01);                  // CLK/8   (~3.9 kHz)
//  TCCR0B |= (1 << CS01) | (1 << CS00);    // CLK/64  (~488.2 Hz)
//  TCCR0B |= (1 << CS02);                  // CLK/256 (~122.04 Hz)
  TCCR0B |= (1 << CS02) | (1 << CS00);      // CLK/1024  (~30Hz)

  while(1) {}
    
  return 0;
}