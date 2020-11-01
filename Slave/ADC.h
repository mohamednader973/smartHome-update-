/*
 * ADC.h
 *
 * Created: 9/19/2020 9:32:31 PM
 *  Author: monad
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#define ADC_MUX       (*((volatile unsigned char*)0x27))
#define ADC_CTRL_STAT (*((volatile unsigned char*)0x26))
#define ADC_HIGH_BYTE (*((volatile unsigned char*)0x25))
#define ADC_LOW_BYTE  (*((volatile unsigned char*)0x24))
#define ADC_REFS0    6
#define ADC_REFS1    7
#define ADC_EN       7
#define ADC_CVS      6
#define ADC_INTFLAG  4
#define ADC_PS2      2
#define ADC_PS1      1
#define ADC_PS0      0
#define SETBIT(REG,BIT)     REG |=(1<<BIT)
#define CLEARBIT(REG,BIT)   REG &=~(1<<BIT)
void ADC_Init(void);
unsigned short ADC_Read (unsigned char channel);
#endif /* ADC_H_ */