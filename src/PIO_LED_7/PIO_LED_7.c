// ---------------------------------------------------------------------
// name: PIO_LED_7
// date: 2019-01-01
// Entwickler: Gerold Bausch
//
// Das Programm schaltet alle Portpins des Port D zu Ausgängen 
// und gibt anschließend zeitverzögert verschiedene Bitmuster aus.
//
//----------------------------------------------------------------------

#include <avr/io.h>

char muster[8] = {0xFF,0xE7,0xC3,0x81,0x00,0x18,0x3C,0x7E}; // Feld mit Ausgabemustern

char *position_im_array = &muster;

void pause(volatile uint32_t i);       // Prototyp Funktion 'Pause'

int main(void)
{
  
  DDRD  = 0xff;                   // set all PORTD pins to output
  PORTD = 0x00;                   // clear all outputs

  while(1)                        // repeat forever
  {
    PORTD = *position_im_array;   // LED-Muster ausgeben
    position_im_array++;          // Zeiger auf nächstes Element positionieren
    pause(200000);                // wait

    PORTD = *position_im_array;   // LED-Muster ausgeben
    position_im_array++;          // Zeiger auf nächstes Element positionieren
    pause(200000);                // wait

    PORTD = *position_im_array;   // LED-Muster ausgeben
    position_im_array++;          // Zeiger auf nächstes Element positionieren
    pause(200000);                // wait

    PORTD = *position_im_array;   // LED-Muster ausgeben
    position_im_array++;          // Zeiger auf nächstes Element positionieren
    pause(200000);                // wait

    PORTD = *position_im_array;   // LED-Muster ausgeben
    position_im_array++;          // Zeiger auf nächstes Element positionieren
    pause(200000);                // wait

    PORTD = *position_im_array;   // LED-Muster ausgeben
    position_im_array++;          // Zeiger auf nächstes Element positionieren
    pause(200000);                // wait

    PORTD = *position_im_array;   // LED-Muster ausgeben
    position_im_array++;          // Zeiger auf nächstes Element positionieren
    pause(200000);                // wait

    PORTD = *position_im_array;   // LED-Muster ausgeben
    position_im_array++;          // Zeiger auf nächstes Element positionieren
    pause(200000);                // wait
    
    position_im_array = muster;
  }       
}

void pause(volatile uint32_t i)
{
    while(i > 0) i--;
}