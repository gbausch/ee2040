// ---------------------------------------------------------------------
// name: PIO_LED_3
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm schaltet alle Portpins des Port D zu Ausgängen 
// und manipuliert anschließend Bitmuster im PortD-Ausgangsregister
//
//----------------------------------------------------------------------

#include <avr/io.h>

#define PORT1_ALS_AUSGANG_DEFINIEREN 0xff

#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)

int main(void)
{
  
  DDRD = PORT1_ALS_AUSGANG_DEFINIEREN;       // set all PORTD pins to output
  
  PIND = 0x00;

  while(1) {

    PORTD &= ~BIT0;  // clear  D.0 (LED off)
    PORTD |=  BIT1;  // toggle D.1 (LED on)

    PORTD |=  BIT0;  // set D.0
    PORTD ^=  BIT1;  // toggle D.1
  
  }        // repeat forever
}
