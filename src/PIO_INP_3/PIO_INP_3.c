// ---------------------------------------------------------------------
// name: PIO_INP_3
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm schaltet alle Portpins des Port D zu Ausgängen,
// den Portpins B0 zu einem Eingang und
// und gibt anschließend den Tasterzustand Bitmuster aus.
//
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRB &= ~(1 << PINB0);          // clear pin B0 for input
  
  DDRD  = 0xff;                   // set port D as output
  PORTD = 0x00;                   // disable all LEDs

  while(1) {
  
    if (!(PINB & 0x01)) {         // check, if bit 0 is clear in PINB
      
      // increment PORTD
      PORTD++;
      
      // wait for next button
      _delay_ms(200);      
      
    }
  }
}