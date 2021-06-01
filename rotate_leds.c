#include <msp430.h> 
void delay_ms(unsigned int delay);

#define TIME_START 7

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    P1DIR &= 0x00;                        // resetting the P1DIR registers
    P2DIR &= 0x00;                        // resetting the P2DIR registers

    P1DIR = 0xFF;                        // setting all the P1DIR registers to 1 (high) output

    P1OUT &= 0x00;                        // resetting the P1OUT registers


    P1OUT = (BIT0|BIT1|BIT2);                        // setting the P1OUT registers to turn on BIT0|BIT1|BIT2

    while (1337) {                        // infinite loop
        if (P1OUT == BIT7) {
            P1OUT = (BIT0|BIT1|BIT2);
            delay_ms(TIME_START);
        }
       else{
        P1OUT = P1OUT << 1;
        delay_ms(TIME_START);                // delay
       }
        r&=0Xff;
}
}
/**
* Takes a value in parameter in order to have a delay.
* 16,000 is equal to 16,000,000 / 1,000.
* -> 16,000,0000 = 16MHz (the CPU clock speed).
*/
void delay_ms(unsigned int delay)
{
    while (delay--)
    {
        __delay_cycles(32000);
    }
}

