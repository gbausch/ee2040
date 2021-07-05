// ---------------------------------------------------------------------
// name: Timer_5.c
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm demonstriert einen Watchdog-Timer-Reset.
// Wird der Mikrocontroller gestartet und initialisiert, leuchtet die
// LED (PD7) für 0,5 Sekunden auf. Im Hauptprogramm wird der Watchdog
// bedient ("gefüttert"), so dass kein WDT-Reset ausgeführt wird.
// Modifikation: Super-Loop wird so erweitert, dass WDT ausgeführt wird
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


int main (void)
{
  
  wdt_reset();
  wdt_enable(WDTO_4S);                                  // system reset, time-out: 4sec
  
  DDRD  = 0xff;                                         // set all pins on Port D as output
  PORTD = 0x00;                                         // clear all outputs
  
  PORTD |= (1 << 7);                                    // sets LED7
  _delay_ms(500);                                       // wait 500 ms
  PORTD &= ~(1 << 7);                                   // clear LED7
  
  while(1) {
    // do nothing here! WDT will reset device
    
    // reset watchdog within 4 seconds prevents reset by watchdog
//    _delay_ms(2000);
//    wdt_reset();
  }
 
}