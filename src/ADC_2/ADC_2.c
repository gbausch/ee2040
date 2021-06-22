// ---------------------------------------------------------------------
// name: ADC_2
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// ADC-Wert an Eingang 0 (ADC0) einlesen und als Zahlenwert ausgeben
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void UART_init(unsigned int baudrate);
void UART_tx(char *string);

int main (void) {
  
  char buffer[64];
  
  UART_init(9600);                                          // init UART w/9600 baud
  
// init adc
  ADMUX  |= (1 << REFS0);                                   // ADC_ref = AVcc
//ADMUX  |= (1 << MUX3);                                    // select ADC8 (internal temp sensor)
  
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);     // prescaler=128 (16.000.000/128=125kHz)
  ADCSRA |= (1 << ADEN);                                    // enable ADC
  
  ADCSRA |= (1 << ADSC);                                    // perform dummy conversion (see p. 210)
  while ((ADCSRA & (1<<ADSC)) != 0);                        // wait for dummy conversion to complete
  
  
  while(1) {
    
    ADCSRA |= (1 << ADSC);                                  // start single conversion
    while ((ADCSRA & (1<<ADSC)) != 0);                      // wait for conversion to complete
    
    sprintf(buffer, "ADC value: %d\n", ADC);                // format ADC value in string
    UART_tx(buffer);                                        // tx string
    
    _delay_ms(1000);
 
  }

}

void UART_init(unsigned int baudrate) {
  
  unsigned int prescale = ((F_CPU/(baudrate * 16UL))-1);
  
  // set baud rate
  UBRR0H = (unsigned char)(prescale>>8);                    // Upper 8 bits of the baud rate value
  UBRR0L = (unsigned char)(prescale);                       // Lower 8 bits of the baud rate value
  
  UCSR0B |= (1 << RXEN0);                                   // enable receiver
  UCSR0B |= (1 << TXEN0);                                   // enable transmitter
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);                  // Use 8-bit character sizes
}

void UART_tx(char *string) {
  
  uint16_t i = 0;
  
  while(string[i] != 0) {                                   // send data until end of buffer
    
    while (( UCSR0A & (1<<UDRE0)) == 0) {};                 // wait for empty tx buffer
    UDR0 = string[i++];                                     // send buffer
  }
}
