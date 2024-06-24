// ---------------------------------------------------------------------
// name: PIO_INP_1_ExtPulldown.c
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm schaltet alle Portpins des Port D zu Ausgängen,
// den Portpin 0 des Port B als Eingang und
// und gibt anschließend den Tasterzustand Bitmuster aus.
//
//----------------------------------------------------------------------

#include <avr/io.h>

int main(void)
{
  DDRD  = 0xff;           // set port D as output
  PORTD = 0x00;           // clear all outputs  

  DDRB &= ~(1 << PINB0);  // set PINB0 as input

  while(1) {
      PORTD = PINB;       // read input from Port B and output to Port D
  }
}
