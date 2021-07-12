// ---------------------------------------------------------------------
//   name: ASM_1.s
//   date: 2019-01-01          
// author: Gerold Bausch
//
// Initialisierung des PB5 (LED) des Arduino UNO als Ausgang.
// Set und Reset von PB5.
//----------------------------------------------------------------------
    
#define __SFR_OFFSET 0
#include <avr/io.h>
    
.org 0x0000
    jmp main

main:
    ldi r16, 0b00100000	    ; load 0x20 -> R16
    ldi r17, 0b00000000	    ; load 0x00 -> R17
    out DDRB, r16           ; set PB5 as output
    
loop:
    out PORTB, r16	        ; enable PB5
    out PORTB, r17	        ; disable PB5
    
    jmp loop                ; jump to label 'loop'
