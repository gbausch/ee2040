// ---------------------------------------------------------------------
// name: Timer_4.c
// date: 2024-06-19          
// Entwickler: Gerold Bausch
//
// ADC-0 wird eingelesen und damit die Pulsbreite der PWM gesteuert
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>

void main (void)
{
  // init gpio
  DDRD  = 0xff;     // set all pins on Port D as output
  PORTD = 0x00;     // clear all outputs
  
  // init adc
  ADMUX  |= (1 << REFS0);                   // ADC_ref = AVcc
  ADMUX  |= (1 << ADLAR);                   // left-adjust result, return only upper 8 bits

  
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);    // Prescaler=8 (16.000.000/8=2MHz)
  ADCSRA |= (1 << ADEN);                    // enable ADC
  ADCSRA |= (1 << ADATE);                   // auto-trigger enable
  ADCSRA |= (1 << ADSC);                    // start first conversion
  
  //init timer/counter
  TCCR0A |= (1 << WGM01) | (1 << WGM00);    // Waveform Generation Mode: Fast PWM
  TCCR0A |= (1 << COM0A1);                  // Clear OC0A on compare match
  
  TCCR0B |= (1 << CS02) | (1 << CS00);      // CLK/1024  (~30Hz)

  while(1) {
    OCR0A = ADCH;                           // update OCR0A from ADC high byte
  }
}