// ---------------------------------------------------------------------
// name: ADC_1
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// Initialisierung des ADC und Auslesen des internen Temperatursensors
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void UART_init(uint16_t baudrate);
void UART_tx(uint8_t *string);

int main (void) {
  
  uint8_t buffer[64];
  uint16_t adc_val;
  
  UART_init(9600);                                          // init UART w/9600 baud
  
  // init adc
  ADMUX  |= (1 << REFS0) | (1 << REFS1);                    // internal ref 1.1V
  ADMUX  |= (1 << MUX3);                                    // select ADC8 (internal temp sensor)
  
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);     // prescaler=128 (16.000.000/128=125kHz)
  ADCSRA |= (1 << ADEN);                                    // enable ADC
  
  ADCSRA |= (1 << ADSC);                                    // perform dummy conversion (see p. 210)
  while ((ADCSRA & (1<<ADSC)) != 0);                        // wait for dummy conversion to complete
  
  while(1) {
    
    ADCSRA |= (1 << ADSC);                                  // start single conversion
    while ((ADCSRA & (1<<ADSC)) != 0);                      // wait for conversion to complete
    
    adc_val = (uint16_t)(ADCH<<8) + (uint16_t)(ADCL);       // get high/low byte from ADC register
  //adc_val = ADC;                                          // get 16 bit ADC value (same as above)

    sprintf(buffer, "Internal temperature: %d\n", adc_val);
    UART_tx(buffer);                                        // format string and tx
    
    _delay_ms(1000);                                        // wait 1 sec
  }
}

void UART_init(uint16_t baudrate) {
  
  uint16_t prescale = ((F_CPU/(baudrate * 16UL))-1);
  
  // set baud rate
  UBRR0H = (uint8_t)(prescale>>8);                    // Upper 8 bits of the baud rate value
  UBRR0L = (uint8_t)(prescale);                       // Lower 8 bits of the baud rate value
  
  UCSR0B |= (1 << RXEN0);                             // enable receiver
  UCSR0B |= (1 << TXEN0);                             // enable transmitter
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);            // Use 8-bit character sizes
}

void UART_tx(uint8_t *string) {
  
  uint16_t i = 0;
  
  while(string[i] != 0) {                             // send data until end of buffer    
    while (( UCSR0A & (1<<UDRE0)) == 0) {};           // wait for empty tx buffer
    UDR0 = string[i++];                               // send buffer
  }
}