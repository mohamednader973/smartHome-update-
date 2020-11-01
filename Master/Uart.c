/*
 * Uart.c
 *
 * Created: 10/3/2020 10:48:38 PM
 *  Author: monad
 */ 
#include "Uart.h"
#include <avr/io.h>
void UART_Init(void){
	//UCSRB |=(1<<RXEN)|(1<<TXEN);
	SEtBIT(UART_CTRSTATReg_B,Trans_EN);
	SEtBIT(UART_CTRSTATReg_B,Recieve_EN);
	//UCSRC |=(1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL);
	SEtBIT(UART_CTRSTATReg_C,Reg_Select);
	SEtBIT(UART_CTRSTATReg_C,UART_CZ1);
	SEtBIT(UART_CTRSTATReg_C,UART_CZ0);
	//UBRRL = MyUBBR;
	BaudRate_Low_Reg=MyUBBR;
	CLearBIT(UART_CTRSTATReg_C,Reg_Select);
	//UBRRH =(MyUBBR>>8);
	UART_CTRSTATReg_C=(MyUBBR>>8);
}
void UART_Send(unsigned char data){
	//while(!(UCSRA &(1<<UDRE)));
	while(!(UART_CTRSTATReg_A &(1<<UART_DataReg_EM)));
	//UDR =data;
	UART_DataReg =data;
}
unsigned char UART_Recieve(void){
	//while(!(UCSRA &(1<<RXC)));
	while(!(UART_CTRSTATReg_A &(1<<UART_Recomp)));
	//return UDR;
	return UART_DataReg;
}
void UART_Send_String(char* string){
	unsigned char i=0;
	while(string[i] !='\0')
	{
		UART_Send(string[i]);
		i++;
	}
	
}