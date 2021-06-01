#include <msp430.h> 
int sw1=0;
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR = 0x00;
	P1DIR |= (BIT0 | BIT6);
	P1REN |= BIT3;  //makes it pull up
	P1OUT |= BIT3;
	
	for(;;)
	{
		sw1 = P1IN;
		sw1 &= BIT3;

	    if (sw1 == BIT3)
	    {
	    P1OUT &= ~BIT6;
	    P1OUT ^= BIT0;
	    __delay_cycles(100000);
	    }
	    else
	    {
	    P1OUT &= ~BIT0;
	    P1OUT ^= BIT6;
		__delay_cycles(100000);
	    }
	}
}
