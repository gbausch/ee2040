// ---------------------------------------------------------------------
//   name: ASM_1b.s
//   date: 2019-01-01          
// author: Gerold Bausch
//
// Initialisierung des PB5 (LED) des Arduino UNO als Ausgang.
// Toggeln des Pins OHNE Delay (Einzelschritt!).
//----------------------------------------------------------------------
    
#define __SFR_OFFSET 0
#include <avr/io.h>
    
.org 0x0000		        
    jmp main

main:
    ldi r16, 0x20	    ; load 0x20 -> R16
    out DDRB, r16     ; set PB5 as output
    
loop:
    out PINB, r16     ; toggle PB5
    
    jmp loop		      ; jump to label 'loop'
