// ---------------------------------------------------------------------
// name: UART_5
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm konfiguriert die UART mit 9600 Baud (8N1) und aktiviert
// den Empfang von Zeichen mittels Interrupt.
// Wird ein Zeichen empfangen, toggeln die LEDS
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// Baud rate settings 
// see Data sheet page 164 (settings for F_OSC = 16000000UL)
#define BAUD_RATE_9600_BPS    103

int main (void) {
  
  DDRD  = 0xff;                                           // set PD as output
  PORTD = 0x00;                                           // clear
  
  // set baud rate
  UBRR0H = (unsigned char)(BAUD_RATE_9600_BPS>>8);        // Upper 8 bits of the baud rate value
  UBRR0L = (unsigned char)(BAUD_RATE_9600_BPS);           // Lower 8 bits of the baud rate value
  
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);  // enable receiver, transmitter and RX ISR
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);                // Use 8-bit character sizes 
  
  sei();                                                  // enable global interrupts
  
  while(1) {
    set_sleep_mode(SLEEP_MODE_IDLE);                      // config sleep mode
    sleep_mode();                                         // enable sleep mode
  }
  
  return 0;
}

ISR(USART_RX_vect) {
  
  PORTD ^= (1 << (UDR0-0x30));                            // fetch the received byte, remove ASCII offset and toggle LEDs
}
