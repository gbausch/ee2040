// ---------------------------------------------------------------------
// name: Timer_2b.c
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm konfiguriert den Timer0 im PWM-Modus und gibt ein
// pulsierendes PWM-Signal über den Pin PD6 aus.
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

int main (void) {
  
  DDRD  = 0xff;                               // set all pins on Port D as output
  PORTD = 0x00;                               // clear all outputs
  
  TCCR0A |= (1 << WGM01) | (1 << WGM00);      // Waveform Generation Mode: Fast PWM
  TCCR0A |= (1 << COM0A1);                    // Clear OC0A on compare match
  
  TCCR0B |= (1 << CS02);                      // CLK/256 (~122.04 Hz)   => slow
  
  TIMSK0 |= (1 << TOIE0);                     // Timer/Counter0 Overflow Interrupt Enabled
  sei();                                      // enable global interrupt
  
  while(1) {}
}

// interrupt service routine for Timer0 Overflow
ISR(TIMER0_OVF_vect) {
  
  static uint8_t dir  = 0;                    // 0 = up; 1 = down
  static uint8_t duty = 0;                    // duty cycle (0...255)

  if ((dir == 0) && (duty < 255)) duty++;     // increase duty cycle
  if ((dir == 1) && (duty > 0))   duty--;     // decrease duty cycle

  if ((duty == 255) || (duty == 0)) dir ^= 1; // toggle direction if TOP/BOTTOM reached
  
  OCR0A = duty;                               // update duty
}