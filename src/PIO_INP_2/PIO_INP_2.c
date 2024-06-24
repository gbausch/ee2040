// ---------------------------------------------------------------------
// name: PIO_INP_2
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm schaltet alle Portpins des Port D zu Ausgängen,
// den Portpins B0 zu einem Eingang und
// und gibt anschließend den Tasterzustand Bitmuster aus.
//
//----------------------------------------------------------------------

#include <avr/io.h>

int main(void)
{
  DDRB &= ~(1 << PINB0);          // clear pin B0 for input
  
  DDRD  = 0xff;                   // set port D as output
  PORTD = 0x00;                   // disable all LEDs

  while(1) {

    if (!(PINB & 0x01)) {         // check, if PB0 is clear
        
      // increment PORTD
      PORTD++;      
    }
  }
}