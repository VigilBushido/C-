#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    P1DIR |= (BIT0 | BIT6);                   // set P1DIR with P0 and P6 to high (1)

    for (;;) {
        P1OUT ^= (BIT0 | BIT6);               // toggle the P0 and P6 of P1OUT with 1 and 0
        __delay_cycles(250000);               // 250000 microseconds between each cycle
    }
	return 0;
}