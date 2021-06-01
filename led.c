#include <msp430.h> 

#define LED1 BIT0
#define LED2 BIT6
#define BUTTON BIT3

unsigned int folds = 1;
int i=1;

void main(void)
{
WDTCTL = WDTPW + WDTHOLD; 	//Stop watchdog timer

P1OUT  = 0x00;				//make sure all default outputs are zero
P1DIR  = (LED1 | LED2); 	//set P1.0 and P1.6 to output direction

P1REN |= BUTTON; 			//enables resistor on the button pin
P1OUT |= BUTTON; 			//make that a pull up
P1IES |= BUTTON; 			//interrupt edge selec, hi to lo
P1IE  |= BUTTON; 			//enable interrupt on selected pin
__enable_interrupt(); 		//enable interrupts get (function call)__ executes enable interrupts

for (;;)
{
	P1OUT ^= (LED2); 	                                    //toggle P1.0 using XOR
	for(i = 1; i <= folds; i++) {__delay_cycles(1000000);}   //delay folds number of times 100,000 micro seconds = 100 milli seconds =.1 seconds
}
}// 10 million micro seconds = 10 seconds
// folds increase by button
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR // can be set = timer
__interrupt void Port_1(void)
{
   P1OUT |= LED1;											//LED1 on to indicate interrupt service
   folds ++; if (folds >= 4) {folds =1;}					//cycle folds for 1,2,3
   __delay_cycles(20000);									//allow some delay for switch debounce
   P1IFG &= ~BUTTON;  										//P1.3 IFG cleared (button inverted)
   __delay_cycles(20000);									//allow some delay for switch debounce
/*   P1IES &= ~BUTTON;
   __delay_cycles(500000)*/
   P1OUT &= ~LED1;											//LED1 off to indicate end of interrupt service
}
