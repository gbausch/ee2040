// ---------------------------------------------------------------------
// name: PIO_LED_9
// date: 2019-01-01
// Entwickler: Gerold Bausch
//
// Das Programm schaltet alle Portpins des Port D zu Ausgängen 
// und gibt anschließend zeitverzögert verschiedene Bitmuster aus.
//
//----------------------------------------------------------------------

#include <avr/io.h>

#define MUSTER_ANZAHL 8

int main(void) {  
  
  char muster[MUSTER_ANZAHL] = {0xFF, 0xE7, 0xC3, 0x81, 0x00, 0x18, 0x3C, 0x7E};  // Feld/Array/Vektor mit Ausgabemustern
  char *position_im_array = &muster[0];       // Zeiger auf Ausgabemuster
  
  // Feld mit Wartezeiten
  unsigned long dauer[MUSTER_ANZAHL] = {200000, 300000, 400000, 500000, 600000, 500000, 400000, 300000};
  unsigned long *zeiger_auf_dauer = &dauer[0];
  
  volatile unsigned long i;
  
  /***** Setup *****/  
  DDRD = 0xff;
  PORTD = 0x00;
  
  /***** Hauptprogramm ****/
  while(1) {
    
    PORTD = *position_im_array;       // LEDs 1-8 einschalten
    position_im_array++;              // Zeiger auf nächstes Element positionieren 
    
    i = *zeiger_auf_dauer;            // Variable i auf Wert aus Feld setzt
    zeiger_auf_dauer++;               // Zeiger auf nächstes Element positionieren
    while(i > 0) i--;                 // warten
    
    // Zeiger auf erste Position im Muster setzen, wenn Ende des Arrays erreicht
    if (position_im_array == &muster[0] + MUSTER_ANZAHL) {
      position_im_array = &muster[0];
      zeiger_auf_dauer  = &dauer[0];
    }
  }  
}