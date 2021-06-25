// ---------------------------------------------------------------------
// name: UART_2
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm konfiguriert die UART mit 9600 Baud (8N1) und überträgt
// eine Zeichenkette alle Sekunden. Dafür wurde eine eigene Funktion
// implementiert
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

// siehe Datasheet Seite 164 (settings for F_OSC = 16000000UL)
#define BAUD_RATE_9600_BPS    103

// Alternative:
// #define USART_BAUDRATE 9600
// #define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) 

void send_usart(unsigned char *data);   // function prototype

int main (void)
{ 
  // set baud rate
  UBRR0H = (unsigned char)(BAUD_RATE_9600_BPS>>8);  // Upper 8 bits of the baud rate value
  UBRR0L = (unsigned char)(BAUD_RATE_9600_BPS);     // Lower 8 bits of the baud rate value

  // enable receiver and transmitter
  UCSR0B |= (1 << TXEN0);                           // enable transmitter 0
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);          // use 8-bit character sizes (8N1)
    
  // buffer
  unsigned char buffer[] = "Hallo Welt\n";          // buffer to transmit

  while(1) {

    send_usart(&buffer[0]);                         // send data from buffer
    _delay_ms(1000);                                // wait for 1 sec
    
  }
  return 0;
}

void send_usart(unsigned char *data) {
  
  uint16_t i = 0;
  
  while(data[i] != 0) {                         // send data until end of buffer
    
    while (( UCSR0A & (1<<UDRE0)) == 0) {};     // wait for empty tx buffer
    UDR0 = data[i];                             // fill buffer, send buffer
    i++;                                        // increment counter
  }
}
