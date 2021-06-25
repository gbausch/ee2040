// ---------------------------------------------------------------------
// name: UART_3
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm konfiguriert die UART mit 9600 Baud (8N1).
// Wird ein Zeichen empfangen, sendet der Controller das Zeichen
// wieder zurück an den Sender.
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>

// Baud rate settings 
// see Data sheet page 164 (settings for F_OSC = 16000000UL)
#define BAUD_RATE_9600_BPS    103

int main (void) { 
  
  char buffer; 
  
  // set baud rate
  UBRR0H = (unsigned char)(BAUD_RATE_9600_BPS>>8);  // Upper 8 bits of the baud rate value
  UBRR0L = (unsigned char)(BAUD_RATE_9600_BPS);     // Lower 8 bits of the baud rate value
  
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);            // enable receiver and transmitter
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);          // Use 8-bit character sizes 
  
  while(1) {

    while ((UCSR0A & (1 << RXC0)) == 0) {};         // Do nothing until data have been received and is ready to be read from UDR 
    buffer = UDR0;                                  // Fetch the received byte value into the variable "buffer" 

    while ((UCSR0A & (1 << UDRE0)) == 0) {};        // Do nothing until UDR is ready for more data to be written to it 
    UDR0 = buffer;                                  // Echo back the received byte back to the computer 
//  UDR0 = buffer+1;                                // Was passiert, wenn man das hier macht?
    
  }
  return 0;
}
