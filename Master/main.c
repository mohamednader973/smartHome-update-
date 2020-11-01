/*
 * SmartHome_Master.c
 *
 * Created: 10/5/2020 11:23:42 PM
 * Author : monad
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "SPI.h"
#include "Uart.h"
#include "LCD.h"
int main(void)
{
	UART_Init();
	SPI_Init();
	LCD_Init();
	PORTB &=~(1<<4);
    /* Replace with your application code */
    while (1) 
    {
		LCD_String("My Smart Home");
		if (UART_Recieve()=='1')
		{
			SPI_Write('1');
			LCD_StartPOS(2,0);
			LCD_String("LED is ON");
			_delay_ms(500);
			LCD_CMD(0x01);
			
		}
		if (UART_Recieve()=='2')
		{
			SPI_Write('2');
			LCD_StartPOS(2,0);
			LCD_String("LED is OFF");
			_delay_ms(500);
			LCD_CMD(0x01);
		}
		if (UART_Recieve()=='3')
		{
			SPI_Write('3');
			LCD_StartPOS(2,0);
			LCD_String("Reading Temp.");
			_delay_ms(500);
			LCD_CMD(0x01);
		}
		if (UART_Recieve()=='+')
		{
			   SPI_Write('+');
			    LCD_StartPOS(2,0);
			   LCD_String("Motor is accel.");
			   _delay_ms(500);
			   LCD_CMD(0x01);
		}
		if (UART_Recieve()=='-')
		{
			SPI_Write('-');
			LCD_StartPOS(2,0);
			LCD_String("Motor is decel.");
			_delay_ms(500);
			LCD_CMD(0x01);

		}
    }
}

