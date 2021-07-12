// ---------------------------------------------------------------------
//   name: ASM_1c.s
//   date: 2019-01-01          
// author: Gerold Bausch
//
// Initialisierung des PB5 (LED) des Arduino UNO als Ausgang.
// Toggeln des Pins mit einem Delay von 500ms
//----------------------------------------------------------------------

#define __SFR_OFFSET 0
#include <avr/io.h>
    
.org 0x0000		   
    jmp main

main:
    ldi r16, 0x20       ; load 0x20 -> R16
    out DDRB, r16       ; set PB5 as output
    
loop:
    out  PINB, r16      ; toggle PB5
    
    ldi  r17, 41        ; using 3 registers (r17, r18, r20)
    ldi  r18, 150       ; to generate long delay (500ms)
    ldi  r19, 127       ; see: http://darcy.rsgc.on.ca/ACES/TEI4M/AVRdelay.html
    
wait:
    dec  r19
    brne wait
    dec  r18
    brne wait
    dec  r17
    brne wait
    
    rjmp loop           ; jump to label 'loop'
