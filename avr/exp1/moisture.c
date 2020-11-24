
#include<avr/io.h>

//#define	F_CPU	1000000

#include<util/delay.h>

#define		LCD_DATA_PORT		PORTB

#define 	LCD_CONT_PORT		PORTD

#define 	LCD_RS 		PD0
#define 	LCD_RW 		PD1
#define 	LCD_EN 		PD2

#define		SENSOR_REF		50

#include<stdlib.h>

//adc functions
void adc_init(void);
int read_adc_channel(unsigned char channel);

//lcd functions
void lcd_data_write(char data);
void lcd_command_write( char command);
void lcd_init();
void lcd_string_write( char *string);
void lcd_number_write(int number,unsigned char radix);


int main(void)
{
	DDRB=0xFF;	

	DDRD=0xFF;
	DDRC=0b11111110;
	
	

	 DDRA=0b00000110;

	int sensor_output=0;

	lcd_init();

	adc_init();

	lcd_string_write("automatic plant ");

	lcd_command_write(0xc0);


	lcd_string_write("watering system");


	_delay_ms(500);
	//_delay_ms(500);
	//_delay_ms(500);
	//_delay_ms(500);


	/*Start of infinite loop*/
	while(1)
	{
		lcd_command_write(0x01);
		
        if((PINC & (1 << DDC0)))			// 8th probe, Tank full	
		{
			//PORTD |= (1 << DDD7);
			PORTC=0b10000000;
			lcd_string_write("moisture: ");
			lcd_number_write(sensor_output,10);
			lcd_string_write("% ");
			
		}
		
		else
{	

		 if (sensor_output > SENSOR_REF)
		 {
			lcd_string_write("moisture: ");
			lcd_number_write(sensor_output,10);
			
			lcd_string_write("% ");

		 	PORTC=0b00000000;
			PORTA=0b00000000;
		}  
			 
		else if(sensor_output < SENSOR_REF) 
		{
			lcd_string_write("Moisture: ");
			lcd_number_write(sensor_output,10);
			lcd_string_write("% ");

			PORTC=0b00011110;
			PORTA=0b00000100;
		}
		
}
		lcd_command_write(0xc0);

		sensor_output=read_adc_channel(0);
		sensor_output=100-(sensor_output*100.0)/1023;

		//lcd_number_write(sensor_output,10);


		_delay_ms(100);

	}
}



void adc_init(void)
{
	ADCSRA=(1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2);
	SFIOR=0x00;
}

int read_adc_channel(unsigned char channel)
{
	int adc_value;
	unsigned char temp;
	ADMUX=(1<<REFS0)|channel;
	_delay_ms(1);
	temp=ADCL;
	adc_value=ADCH;
	adc_value=(adc_value<<8)|temp;
	return adc_value;
}

/*Alphanumeric LCD Function Definitions*/
void lcd_data_write(char data)
{
	LCD_CONT_PORT=_BV(LCD_EN)|_BV(LCD_RS);
	LCD_DATA_PORT=data;
	_delay_ms(1);
	LCD_CONT_PORT=_BV(LCD_RS);
	_delay_ms(1);
}

void lcd_command_write(char command)
{
	LCD_CONT_PORT=_BV(LCD_EN);
	LCD_DATA_PORT=command;
	_delay_ms(1);
	LCD_CONT_PORT=0x00;
	_delay_ms(1);
}

void lcd_init()
{
	lcd_command_write(0x38);
	lcd_command_write(0x01);
	lcd_command_write(0x06);
	lcd_command_write(0x0e);
}

void lcd_string_write(char *string)
{
	while (*string)
	lcd_data_write(*string++);
}

void lcd_number_write(int number,unsigned char radix)
{
	char *number_string="00000";
	itoa(number,number_string,radix);
	lcd_string_write(number_string);
}
