/*
 * ADC_Atmega328p.c
 *
 * Created: 5/21/2019 5:07:20 PM
 * Author : Lucas
 */ 

#include "def_principais.h";
#include "LCD.h";
int temp;
unsigned char temp_str[3];
ISR(ADC_vect)
{
	temp = ADC + (ADC*19)/256;
}

int main(void)
{
	DDRD = 0xFF;
	ADMUX =  0b11000000;
	ADCSRA = 0b11101111;
	ADCSRB = 0x00;
	set_bit(DIDR0, 0);
	
	sei();
	inic_LCD_4bits();
    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(100);
		cmd_LCD(0x80, 0);
		ident_num(temp, temp_str);
		cmd_LCD(temp_str[2], 1);
		cmd_LCD(temp_str[1], 1);
		cmd_LCD(temp_str[0], 1);
    }
}

