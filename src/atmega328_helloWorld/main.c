/*
// compile
avr-gcc -O0 -DF_CPU16000000UL -mmcu=atmega328p -c -o main.o main.c

// link
avr-gcc -mmcu=atmega328p *.o -o main

// convert file to intel hex format
avr-objcopy -O ihex -R .eeprom main main.hex

// Upload
avrdude -F -V -c arduino -p atmega328p -P /dev/cu.usbmodem1101 -b 115200 -D -U flash:w:main.hex
*/

#define PINB  ((*(volatile unsigned char*)0x23))
#define DDRB  ((*(volatile unsigned char*)0x24))
#define PORTB ((*(volatile unsigned char*)0x25))

#define PINC  ((*(volatile unsigned char*)0x26))
#define DDRC  ((*(volatile unsigned char*)0x27))
#define PORTC ((*(volatile unsigned char*)0x28))

#define PIND  ((*(volatile unsigned char*)0x29))
#define DDRD  ((*(volatile unsigned char*)0x2A))
#define PORTD ((*(volatile unsigned char*)0x2B))

int main(void) {

  //DDRD = (1<<5);        // PIND5 => output

  // set pin5D as output
  /*asm("  ldi  r16, (1<<5)");
  asm("  out  0x2a, r16");
  asm("loop:");
  asm("  in   r17, 0x2b");
  asm("  eor  r17, r16");
  asm("  out  0x2b, r17");
  asm("  rjmp loop");*/


  DDRD = (1<<5);        // PIND5 => output
  
  while (1) {
    PIND = (1<<5);     // Toggle Pin5D
  }

}
