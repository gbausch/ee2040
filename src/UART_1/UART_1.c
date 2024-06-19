// ---------------------------------------------------------------------
// name: UART_1
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm konfiguriert die UART mit 9600 Baud (8N1) und überträgt
// das Zeichen im Buffer alle Sekunden.
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

// Baud rate settings 
// see Data sheet page 164 (settings for F_OSC = 16000000UL)
#define BAUD_RATE_9600_BPS    103

// Alternative:
// #define USART_BAUDRATE 9600
// #define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) 

int main (void)
{
  // set baud rate
  UBRR0H = (uint8_t)(BAUD_RATE_9600_BPS>>8);  // Upper 8 bits of the baud rate value
  UBRR0L = (uint8_t)(BAUD_RATE_9600_BPS);     // Lower 8 bits of the baud rate value

  // config uart
  UCSR0B |= (1 << TXEN0);                     // enable transmitter 0
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);    // use 8-bit character sizes (8N1)
    
  uint8_t buffer = 'n';                       // data to transmit

  while(1) {
      
    UDR0 = buffer;                            // send data from buffer
    _delay_ms(1000);                          // wait for 1 sec
  }
    
  return 0;
}
