/*
 * SmartHome_Reciever.c
 *
 * Created: 10/5/2020 2:08:27 AM
 * Author : monad
 */ 

#include <avr/io.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "ADC.h"
#include "SPI.h"
#include "LCD.h"
#include "DIO_INOUT.h"
int main(void)
{
	DDRB |=(1<<3);
	DDRB &=~(1<<6);
	DDRB &=~(1<<7);
	DDRC |=(1<<0);
	OCR0 =0;
	TCCR0 |=(1<<COM01)|(1<<CS00)|(1<<CS01)|(1<<WGM00); //Phase correct pwm (non inverting) with prescalar /64 
	ADC_Init();
	LCD_Init();
	SPI_Init();
	unsigned short temp=0;
	char array[16];
    /* Replace with your application code */
	unsigned char count=0;
	char var;
    while (1) 
    {
		var=SPI_Receive();
		if (var=='1')
		{
		    PORTC |=(1<<0);
		}
		else if (var=='2')
		{
			PORTC &=~(1<<0);
		}
	
		else if (var=='+')
		{
			count++;
			switch(count)
			{
				case 1:
				OCR0 =51;
				break;
				case 2:
				OCR0 =102;
				break;
				case 3:
				OCR0 =153;
				break;
				case 4:
				OCR0 =204;
				break;
				case 5:
				OCR0 =255;
				break;
			}
			if (count>5)
			{
				count=5;
			}
			
		}
		else if (var=='-')
		{
			count=count-1;
			if (count==0)
			{
				OCR0 =0;
			}
			switch(count)
			{
				case 1:
				OCR0 =51;
				break;
				case 2:
				OCR0 =102;
				break;
				case 3:
				OCR0 =153;
				break;
				case 4:
				OCR0 =204;
				break;
				case 5:
				OCR0 =255;
				break;
			}
			
		}
		if (var=='3')
		{
			temp=ADC_Read(1);
			temp /=4;
			itoa(temp,array,10);
			LCD_StartPOS(1,0);
			LCD_String("The temperature =");
			LCD_StartPOS(2,0);
			LCD_String(array);
			_delay_ms(20000);
			LCD_CMD(0x01);
			
		}
    }
}

