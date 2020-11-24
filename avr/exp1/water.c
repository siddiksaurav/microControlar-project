//#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0x00  ;	// PORTB pins as input
	DDRD = 0xFF;	// PORTD as output
	DDRC = 0xFF;		// Buzzer

	
    while(1)
    { 
	
	
        if((PINB & (1 << DDB0)))			// 8th probe, Tank full	
		{
			PORTD = 0b00000001;
			PORTC=0b00000010;
			
		}
		else
		{
		PORTD=0b00000000;
		PORTC=0b00000001;
		}
					
    }
}