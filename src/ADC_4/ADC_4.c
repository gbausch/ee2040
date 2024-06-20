// ---------------------------------------------------------------------
// name: ADC_4
// date: 2019-01-01          
// Entwickler: Gerold Bausch
//
// ADC wird zur Bestimmung eines unbekannten Widerstandes genutzt.
// Vorwiderstand Rv=10kOhm
// Unbekannter Widerstand Rx=?
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

void UART_init(uint16_t baudrate);
void UART_tx(uint8_t *string);

int main (void) {
  
  UART_init(9600);                                          // init UART w/9600 baud
  
// init adc
  ADMUX  |= (1 << REFS0);                                   // ADC_ref = AVcc
  
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);     // Prescaler=128 (16.000.000/128=125kHz)
  ADCSRA |= (1 << ADIE);                                    // enable ADC interrupt
  ADCSRA |= (1 << ADEN);                                    // enable ADC
  
  sei();                                                    // enable global interrupt  
  
  while(1) {
    ADCSRA |= (1 << ADSC);                                  // start single conversion    
    _delay_ms(1000);                                        // wait 1 sec
  }
}

ISR(ADC_vect) {
  
  uint8_t   buffer[64];
  float16_t ADC_voltage;
  
  // output of ADC value in volt    
  ADC_voltage = (float16_t)ADC * (5.0/1024.0);
  sprintf(buffer, "Rx: %d Ohm\n", (int)((ADC_voltage/(5.0-ADC_voltage))*10000.0));
  
  UART_tx(buffer);
}

void UART_init(uint16_t baudrate) {
  
  unsigned int prescale = ((F_CPU/(baudrate * 16UL))-1);
  
  // set baud rate
  UBRR0H = (uint8_t)(prescale>>8);                    // Upper 8 bits of the baud rate value
  UBRR0L = (uint8_t)(prescale);                       // Lower 8 bits of the baud rate value
  
  UCSR0B |= (1 << RXEN0);                             // enable receiver
  UCSR0B |= (1 << TXEN0);                             // enable transmitter
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);            // Use 8-bit character sizes
}

void UART_tx(uint8_t *string) {
  
  uint16_t i = 0;
  
  while (string[i] != 0) {                            // send data until end of buffer
    while ((UCSR0A & (1<<UDRE0)) == 0) {};           // wait for empty tx buffer
    UDR0 = string[i++];                               // send buffer
  }
}
