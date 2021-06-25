// ---------------------------------------------------------------------
// name: PIO_INP_1
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm schaltet alle Portpins des Port D zu Ausgängen,
// die Portpins 0, 1, 2, 3 des Port B zu Eingängen und
// und gibt anschließend den Tasterzustand Bitmuster aus.
//
//----------------------------------------------------------------------

#include <avr/io.h>

int main(void)
{
  DDRD = 0xff;  // set port D as output
  DDRB = 0xf0;  // set pin 0..3 on Port B as input (DDRx: 0 => Input, 1 => Output)

  while(1) {
      PORTD = PINB;    // map input from Port B to output Port D
  }
}