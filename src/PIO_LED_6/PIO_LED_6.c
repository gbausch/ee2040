// ---------------------------------------------------------------------
// name: PIO_LED_6
// date: 2019-01-01
// Entwickler: Gerold Bausch
//
// Das Programm schaltet alle Portpins des Port D zu Ausgängen 
// und gibt anschließend zeitverzögert verschiedene Bitmuster aus.
//
//----------------------------------------------------------------------

#include <avr/io.h>

void pause(volatile uint32_t i);       // Prototyp Funktion 'Pause'

int main(void)
{
  
  DDRD  = 0xff;         // set all PORTD pins to output
  PORTD = 0x00;         // clear all outputs

  while(1)              // repeat forever
  {
    PORTD = 0xff;       // LEDs on
    pause(200000);      // wait
    PORTD = 0x00;       // LEDs off
    pause(200000);      // wait
    PORTD = 0x0f;       // LED 0-3 on, 4-7 off
    pause(200000);      // wait
    PORTD = 0xf0;       // LED 0-3 off, 4-7 on
    pause(200000);      // wait
  }       
}

void pause(volatile uint32_t i)
{
    while(i > 0) i--;
}