// ---------------------------------------------------------------------
// name: PIO_LED_2
// date: 2019-01-01
// Entwickler: Gerold Bausch
//
// Das Programm schaltet alle Portpins des Port D zu Ausgängen 
// und gibt anschließend ein Bitmuster aus.
//
//----------------------------------------------------------------------

#include <avr/io.h>

#define MUSTER_1 0xA5
#define MUSTER_2 0x5A

int main(void)
{
  
  DDRD = 0xff;       // set all PORTD pins to output
  
  PORTD = MUSTER_1;
  PORTD = MUSTER_2;

  while(1) {}        // repeat forever
}
