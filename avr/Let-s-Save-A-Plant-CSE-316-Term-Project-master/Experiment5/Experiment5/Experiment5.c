
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define V_REF 5
#define V_MIN 0
int v;

ISR(ADC_vect){
	int adcl=ADCL;
	int adch=ADCH;
	v=(adcl>>6)|(adch<<2);
	ADCSRA |= (1 << ADSC);
}

int main(void){
	unsigned  digital;
	unsigned  temp;
	double analog;
	char buffer[5];
	char string[256];
	int value = 5;


	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRB = 0xFF; // for water pump

	ADMUX = 0b00100000;
	ADCSRA = 0b10001010;

	Lcd4_Init();
	Lcd4_Clear();

	analog=0;
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("Moisture:");
	//sei();
	ADCSRA |= 1<<ADSC;
	sei();
	while(1){
		PORTB = 0x00;
////	//	ADCSRA |= (1<<ADSC);
	//////	//while(ADCSRA & (1<<ADSC));

//////		digital=ADCL;
//////		temp=ADCH;

///////		digital=(digital>>6)|(temp<<2);
		//analog=digital*(V_REF - V_MIN)*1.0/1024.0;
		//analog=digital;
		//analog = 100-(digital*100.00)/1023.00;
		//analog = 2.3;
		//snprintf(buffer,sizeof(buffer),"%.2lf",analog);
		//sprintf(buffer,"%.2lf",analog);
		//buffer[0]=(int)(analog);
		digital = 100-(v*100.00)/1023.00;

		memset(string,0,sizeof(string[0])*256); // Clear all to 0 so string properly represented
		sprintf(string,"%d %%",digital);
		//buffer[1]='.';
		//buffer[2]='0'+(int)((analog-(int)analog)*10);
		//buffer[3]='\0';

		Lcd4_Set_Cursor(1,10);
		Lcd4_Write_String(string);
		if(digital<50){
			PORTB = 0b00001101; //00000001

		}
		_delay_ms(100);
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String("Moisture:");
	}
}
