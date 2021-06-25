// ---------------------------------------------------------------------
// name: PIO_INP_4
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm schaltet alle Portpins des Port D zu Ausgängen,
// den Portpin 0 des Port B zu einem Eingang und
// und erhöht PORTD beim Tastendruck (Interrupt) mit der 
// steigenden Flanke
//
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
  DDRB &= ~(1 << PINB0);          // clear pin B0 for input
  
  DDRD  = 0xff;                   // set port D as output
  PORTD = 0x00;                   // clear all LEDs
            
  // config pin change interrupt for PCINT1 (PB0)
  PCICR  |= (1 << PCIE0);         // enable PCIE0 (PCINT7..0)
  PCMSK0 |= (1 << PCINT0);        // enable PCINT0
    
  SREG |= (1 << 7);               // set Global Interrupt Enable
//sei();                          // set global interrupt flag (alternative)
  
  while(1){};
}

// interrupt service routine on PCINT0 (PB0)
ISR(PCINT0_vect) {
  
  PORTD++;
}