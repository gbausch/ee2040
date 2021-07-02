// ---------------------------------------------------------------------
// name: Timer_3.c
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Das Programm realisiert einen Reaktionstest mit Hilfe des 16-Bit 
// Timer/Counter1 bzw. der Input-Capture-Einheit.
// Am Mikrocontroller wird an PB0 (ICP1) ein Button angeschlossen 
// und nach Erlöschen der LEDs wird die Zeit gemessen, bis der
// Button gedrückt wurde. Die Zeit wird mittels UART ausgegeben.
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

void UART_init(unsigned int baudrate);
void UART_tx(char *string);

int main (void)
{
  char buffer[64];
  unsigned int t;
  
  DDRD  = 0xff;                         // set all pins on Port D as output
  PORTD = 0x00;                         // clear all outputs
  
  DDRB  &= (1 << 0);                    // set PB0 as input (button)
  
  UART_init(9600);                      // init uart with 9600 baud
                                        
  // timer/counter1 in normal mode; just counting ticks
  TCCR1B |= (1 << ICNC1);               // enable input capture noise canceler
  TCCR1B |= (1 << ICES1);               // rising edge triggers the capture
  
  //TCCR1B |= (1 << CS10);              // set prescaler to CLK/1 (62,5ns)
  TCCR1B |= (1 << CS12) | (1 << CS10);  // set prescaler to CLK/1024 (64us)
  
  
  while(1) {
    
    sprintf(buffer, "Push Button to start!\n");
    UART_tx(buffer);
    
    TIFR1 |= (1 << ICF1);               // clear input capture flag (by writing logic 1)
    while ((TIFR1 & (1<<ICF1)) == 0);   // wait for next game
    
    PORTD = 0xf0;                       // ready
    _delay_ms(1000);
    PORTD = 0x90;                       // set
    _delay_ms(1000);                
    PORTD = 0x00;                       // GO!
    
    TIFR1 |= (1 << ICF1);               // clear input capture flag
    TCNT1 = 0;                          // clear timer/counter1
    
    while ((TIFR1 & (1<<ICF1)) == 0);   // wait for button press
    t = ICR1;
    
    // print result
    sprintf(buffer, "t: %u\n", t);
    UART_tx(buffer);

  }
 
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