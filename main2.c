#include <msp430.h> 

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer

    int R5_SW=0, R6_LED=0, bonus=0;


    P1OUT = 0b00000000;  	// mov.b    #00000000b,&P1OUT
    P1DIR = 0b11111111;  	// mov.b    #11111111b,&P1DIR
    P2DIR = 0b00000000;  	// mov.b    #00000000b,&P2DIR

    while (1)
    {
        R5_SW = P2IN;  		//mov.b    &P2IN, R5
        if (R5_SW & BIT0)  	//checking P2.0 for read mode
        {
            R6_LED = R5_SW & (BIT3 | BIT4 | BIT5);
            P1OUT = R6_LED;
        }
        else   // display rotation mode
        {
        	R5_SW = P2IN;
        	if (R5_SW & BIT1) // checking for left or right
        	{

        		R6_LED = R6_LED >> 1 | R6_LED << 7; // ~ R6_LED; // rotate to the left
        		R6_LED &= 0x00FF; // mask
        		P1OUT = R6_LED;
        	}
        	else  // going right
        	{
        		R6_LED = R6_LED << 1 | R6_LED >> 7; // rotate to the right
        		R6_LED &= 0x00FF;
        		P1OUT = R6_LED;
        	}
        }

        R5_SW = P2IN;   // mov.b     &P2IN, R5
        if (R5_SW & BIT2) // checking P2.2 for delay speed
        {
        	__delay_cycles( 400000); // fast
        }
        else
		{
        	__delay_cycles( 800000); // slow
		}

    }
}
