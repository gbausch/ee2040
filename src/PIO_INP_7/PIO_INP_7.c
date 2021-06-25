// ---------------------------------------------------------------------
// name: PIO_INP_7
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm konfiguriert PD2 als Eingang, alle anderen PD-Pins als Ausgang.
// Für PD2 wird zusätzlich der interne Pull-Up-Widerstand aktiviert.
// An PD2 wird ein Taster gegen GND angeschlossen. An PD4 eine LED.
// Beim Betätigen des Tasters an PD2 wird die LED für 1 Sekunde aktiviert.
// Zwischendurch geht der Controller in den Schlafmodus.
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

int main(void)
{
  // Taster an PD2 (Digital Pin 2 => ohne externen Pull-Down-Widerstand)
  // LED an PD4 (Digital Pin 4)
  DDRD  = 0xfb;                     // set D2 as input, all others to output
  PORTD = 0x04;                     // set pull-up active on D2
  
  // config external interrupts  
  EICRA |= (1<<ISC00);                    // enable INT0 on any logical change  
//EICRA |= (1<<ISC01);                    // enable INT0 on falling change (button push)
//EICRA |= (1<<ISC00) | (1<<ISC01);       // enable INT0 on rising edge (button release)
  
  //SREG |= (1 << 7);                     // set Global Interrupt Enable
  sei();                                  // set global interrupt flag
    
  while(1){
    
    EIMSK |= (1<<INT0);                   // enable INT0 (PD2)
    
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Schlafmodus 
    sleep_mode();                         // in den Schlafmodus wechseln
    
    EIMSK &= ~(1<<INT0);                  // disable INT0 (PD2) (falls interrupt sehr lange dauert)

  };
}

// Die Interruptroutine kann leer sein, ABER sie muss existieren!
// Sonst springt der AVR nach dem Aufwachen zum Reset, weil kein sinnvoller
// Interruptvektor eingetragen ist!
ISR(INT0_vect) {
  PORTD |= (1 << PD4);                  // LED für eine Sekunde anschalten
  _delay_ms(1000);
  PORTD &= ~(1 << PD4);
}