/*
 * Adc_atmega328p_examples.c
 *
 * Created: 5/22/2019 2:02:32 PM
 * Author : Lucas
 */ 

#include "def_principais.h"
#include "LCD.h"

float readAdc(char chan)
{
	ADMUX = (1<<REFS0) | (chan & 0x0f);  //select input and ref
	ADCSRA |= (1<<ADSC);                 //start the conversion
	while (ADCSRA & (1<<ADSC));          //wait for end of conversion
	return ADCW;
}

int main(void)
{
	int v1;
	int v2;
	DDRB = 0xFF;
	DDRD = 0xFF;
	unsigned char print[4];
	ADMUX = (1<<REFS0);     //select AVCC as reference
	ADCSRA = 0b10000111;  //enable and prescale = 128 (16MHz/128 = 125kHz)
	sei();
	inic_LCD_4bits();
	/* Replace with your application code */
	while (1)
	{
		_delay_ms(5000);
		ident_num(readAdc(0), print);
		cmd_LCD(0x80, 0);
		cmd_LCD(print[3], 1);
		cmd_LCD(print[2], 1);
		cmd_LCD(print[1], 1);
		cmd_LCD(print[0], 1);
		cmd_LCD('>', 1);
		v1 = (int)(100*((readAdc(0)*5*2)/1024));
		ident_num(v1, print);
		cmd_LCD(print[2], 1);
		cmd_LCD('.', 1);
		cmd_LCD(print[1], 1);
		cmd_LCD(print[0], 1);
		cmd_LCD('V', 1);
		cmd_LCD(0xC0, 0);
		ident_num(readAdc(1), print);
		cmd_LCD(print[3], 1);
		cmd_LCD(print[2], 1);
		cmd_LCD(print[1], 1);
		cmd_LCD(print[0], 1);
		cmd_LCD('>', 1);
		v2 = (int)(100*((readAdc(1)*5*2)/1024));
		ident_num(v2, print);
		cmd_LCD(print[2], 1);
		cmd_LCD('.', 1);
		cmd_LCD(print[1], 1);
		cmd_LCD(print[0], 1);
		cmd_LCD('V', 1);
		_delay_ms(100);
		
	}
}