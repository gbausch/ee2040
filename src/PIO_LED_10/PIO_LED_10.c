// ---------------------------------------------------------------------
// name: PIO_LED_10
// date: 2019-01-01
// Entwickler: Gerold Bausch
//
// Das Programm schaltet alle Portpins des Port D zu Ausgängen 
// und gibt anschließend mit variabler Leuchtdauer verschiedene Bitmuster aus.
//
//----------------------------------------------------------------------

#include <avr/io.h>

#define MUSTER_ANZAHL 8

int main(void)
{
  
  typedef struct {
    char muster;
    unsigned long dauer;
  } werte;

  werte inhalte[MUSTER_ANZAHL] = {
    {0xFF, 20000},
    {0xE7, 30000},
    {0xC3, 40000},
    {0x81, 50000},
    {0x00, 60000},
    {0x18, 50000},
    {0x3C, 40000},
    {0x7E, 30000}
  };

  werte *zeiger = inhalte;
  
  volatile unsigned long i;

  DDRD  = 0xff;                   // set all PORTD pins to output
  PORTD = 0x00;                   // clear all outputs

  while(1)                        // repeat forever
  {
    PORTD = (*zeiger).muster;     // LED-Muster ausgeben
    i = (*zeiger).dauer;        
    zeiger++;

    while(i > 0) i--;             // wait

    if (zeiger == inhalte + MUSTER_ANZAHL) {
        zeiger = inhalte;
    }

  }       
}