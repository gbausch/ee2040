// ---------------------------------------------------------------------
// name: ADC_5
// date: 2024-06-19          
// Entwickler: Gerold Bausch
//
// ADC-Wert an Eingang 0 (ADC0) einlesen und via UART ausgeben
// ADC im Freerunning-mode und 8-Bit
//----------------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define ADC_VREF 5
#define ADC_RES (1<<10)

void UART_init(uint16_t baudrate);

int main (void) {
  
  UART_init(9600);                                          // init UART w/9600 baud
  
// init adc
  ADMUX  |= (1 << REFS0);                                   // ADC_ref = AVcc
  ADMUX  |= (1 << ADLAR);                                   // left-adjust result, return only upper 8 bits
  
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);                    // Prescaler=8 (16.000.000/8=2MHz)
  ADCSRA |= (1 << ADEN);                                    // enable ADC
  ADCSRA |= (1 << ADATE);                                   // auto-trigger enable
  ADCSRA |= (1 << ADSC);                                    // start first conversion
  
  while(1) {
    while (( UCSR0A & (1<<UDRE0)) == 0) {};                 // wait for empty tx buffer
    UDR0 = ADCH;                                            // transmit only upper ADC value
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
