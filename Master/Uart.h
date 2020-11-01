/*
 * Uart.h
 *
 * Created: 10/3/2020 10:48:54 PM
 *  Author: monad
 */ 
#ifndef UART_H_
#define UART_H_
#define F_CPU    16000000UL
#define Baudrate 9600
#ifndef DoubleSpeed
#define MyUBBR           ((F_CPU/(16UL*Baudrate))-1)
#else
#define MyUBBR           ((F_CPU/(8UL*Baudrate))-1)
#endif
#define SEtBIT(Reg,BIT)    (Reg |=(1<<BIT))
#define CLearBIT(Reg,BIT)  (Reg &=~(1<<BIT))
#define Trans_EN             3
#define Recieve_EN           4
#define Reg_Select           7  
#define UART_CZ1             2
#define UART_CZ0             1
#define UART_DataReg_EM      5
#define UART_Recomp          7
#define UART_DataReg                (*((volatile unsigned char*)0x2C))  //UDR
#define UART_CTRSTATReg_A           (*((volatile unsigned char*)0x2B))  //UCSRA
#define UART_CTRSTATReg_B           (*((volatile unsigned char*)0x2A))  //UCSRB
#define BaudRate_Low_Reg            (*((volatile unsigned char*)0x29))  //UBRRL
#define UART_CTRSTATReg_C           (*((volatile unsigned char*)0x40))  //UBRRH &UCSRC
void UART_Init(void);
void UART_Send(unsigned char data);
unsigned char UART_Recieve(void);
void UART_Send_String(char* string);
#endif /* UART_H_ */