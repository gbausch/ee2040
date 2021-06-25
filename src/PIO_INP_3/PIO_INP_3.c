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

// Achtung: Externen Pull-Down-Widerstand am Taster verwenden!

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BIT_IS_SET(byte, bit) (byte & (1 << bit))
#define BIT_IS_CLEAR(byte, bit) (!(byte & (1 << bit)))

int main(void)
{
  DDRB &= ~(1 << PINB0);          // clear pin B0 for input
  
  DDRD  = 0xff;                   // set port D as output
  PORTD = 0x00;                   // disable all LEDs

  while(1) {
    
    if (BIT_IS_SET(PINB, 0)) {
      
      // toggle LED2
      //PORTD ^= PIN2;
      
      // increment PORTD
      PORTD++;
      
      // wait for next button
      _delay_ms(200);      
      
    }
  }
}