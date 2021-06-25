// ---------------------------------------------------------------------
// name: PIO_LED_1
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm schaltet alle Portpins des Port D zu Ausgängen 
// und gibt anschließend ein Bitmuster aus.
//
//----------------------------------------------------------------------

#include <avr/io.h>

int main(void)
{
  DDRD  = 0xff;
  PORTD = 0xa5;

  while(1) {}
}

