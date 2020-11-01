/*
 * SPI.c
 *
 * Created: 10/4/2020 1:11:53 AM
 *  Author: monad
 */ 
#include "SPI.h"
#include <avr/io.h>
void SPI_Init()					/* SPI Initialize function */
{
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);	/* Make MOSI, SCK, SS 
						as Output pin */
	DDRB &= ~(1<<MISO);			/* Make MISO pin 
						as input pin */
	PORTB |= (1<<SS);			/* Make high on SS pin */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	/* Enable SPI in master mode
						with Fosc/16 */
	SPSR &= ~(1<<SPI2X);			/* Disable speed doubler */
}
void SPI_Write(char data)		/* SPI write data function */
{
	SPDR = data;			/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));	/* Wait till transmission complete */
			/* Flush received data */
	/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */
}
char SPI_Read()				/* SPI read data function */
{
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}
