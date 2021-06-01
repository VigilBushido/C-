;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
ARY1		.set	0x0200			;Memory allocation 	ARY1
SetMem1		mov.w   #0x0000,&0200h      ;set a number on location $0200
		    mov.w   #0x0000,&0202h      ;set a number on location $0202
		    mov.w   #0x0000,&0204h      ;set a number on location $0204
		    mov.w   #0x0000,&0206h      ;set a number on location $0204
		    mov.w   #0x0000,&0208h      ;set a number on location $0204
            mov.w   #0x0000,&020Ah      ;set a number on location $0204

Clean1		clr R4
			clr	R5		;clear the entire R7 register
		    clr	R6		;clear the entire R8 register
		    clr R7
		    clr R8
		    clr R9


SetFlags1     	mov.w	#0x1234, R5	; fill register
                mov.w   #0x1234, R6 ;
                ;BIS #4, SR; //negative bit set
                ;BIS #2, SR; //zero bit set
                ;BIS #1, SR; //carry bit set

Instruct1   mov.w	#ARY1,	R4
			mov.b	#17,	0(R4)	;Define the number of elements in the array
			mov.b	#55, 	1(R4)	;store an element
			mov.b	#-9, 	2(R4)	;store an element
			mov.b	#22, 	3(R4)	;store an element
			mov.b   #36,    4(R4)   ;
			mov.b   #-7,    5(R4)   ;
			mov.b   #37,    6(R4)   ;
			mov.b   #8,     7(R4)   ;
			mov.b   #-77,   8(R4)   ;
			mov.b   #8,     9(R4)   ;


Mainloop	jmp     Mainloop        ;Infinite Loop
;-------------------------------------------------------------------------------

                                            

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
