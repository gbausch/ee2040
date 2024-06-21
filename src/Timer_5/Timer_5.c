// ---------------------------------------------------------------------
// name: Timer_5.c
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm demonstriert einen Watchdog-Timer-Reset.
// Wird der Mikrocontroller gestartet und initialisiert, leuchtet die
// LED (PD7) für eine Sekunde auf. Im Hauptprogramm wird der Watchdog
// bedient ("gefüttert"), so dass kein WDT-Reset ausgeführt wird.
// Modifikation: Super-Loop wird so erweitert, dass WDT ausgeführt wird
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>


int main (void)
{
  // config watchdog timer
  // IMPORTANT! Compiler Optimization != 0
  cli();                                                // disable all interrupts
  asm("WDR");                                           // reset watchdog
  WDTCSR |= (1<<WDE) | (1<<WDCE);                       // enable watchdog
  WDTCSR  = (1<<WDE) | (1<<WDP3);                       // 4s / System Reset
  sei();                                                // enable all interrupts
    
  DDRD  = 0xff;                                         // set all pins on Port D as output
  PORTD = 0x00;                                         // clear all outputs
  
  PORTD |= (1 << 7);                                    // set LED7
  _delay_ms(500);                                       // wait 500 ms
  PORTD &= ~(1 << 7);                                   // clear LED7
  
  while(1) {
    // do nothing here! WDT will reset device    
    // reset watchdog within 4 seconds prevents reset by watchdog
    // _delay_ms(2000);
    // asm("WDR");
  }
  return 0;
}