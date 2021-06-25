// ---------------------------------------------------------------------
// name: UART_6
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Modularisierung der UART-Funktionen in UART_init() und UART_tx
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdio.h>

void UART_init(unsigned int baudrate);
void UART_tx(char *string);

int main (void) {
  
  char buffer[64];
  char i = 0;
  
  UART_init(9600);
  
  while(1) {
    
    sprintf(buffer, "Hello World: %d\n", i++);
    UART_tx(buffer);
    
    _delay_ms(1000);
  }
  
  return 0;
}

void UART_init(unsigned int baudrate) {
  
  unsigned int prescale = ((F_CPU/(baudrate * 16UL))-1);
  
  // set baud rate
  UBRR0H = (unsigned char)(prescale>>8);        // Upper 8 bits of the baud rate value
  UBRR0L = (unsigned char)(prescale);           // Lower 8 bits of the baud rate value
  
  UCSR0B |= (1 << RXEN0);                       // enable receiver
  UCSR0B |= (1 << TXEN0);                       // enable transmitter
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);      // Use 8-bit character sizes
}

void UART_tx(char *string) {
  
  uint16_t i = 0;
  
  while(string[i] != 0) {                         // send data until end of buffer
    
    while (( UCSR0A & (1<<UDRE0)) == 0) {};       // wait for empty tx buffer
    UDR0 = string[i++];                           // send buffer
  }
}
