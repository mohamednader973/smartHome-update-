/*
 * ADC.c
 *
 * Created: 9/19/2020 9:32:20 PM
 *  Author: monad
 */
#include "ADC.h"
void ADC_Init(void)
{
	//ADMUX  |=(1<<REFS0)|(1<<REFS1);
	SETBIT(ADC_MUX,ADC_REFS0);
	SETBIT(ADC_MUX,ADC_REFS1);
	//ADCSRA |=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	SETBIT(ADC_CTRL_STAT,ADC_EN);
	SETBIT(ADC_CTRL_STAT,ADC_PS2);
	SETBIT(ADC_CTRL_STAT,ADC_PS1);
	SETBIT(ADC_CTRL_STAT,ADC_PS0);
}
unsigned short ADC_Read (unsigned char channel)
{
	unsigned short data =0;
	//ADMUX =(ADMUX & (0xE0))|(channel & (0x1F));
	ADC_MUX=(ADC_MUX & (0xE0))|(channel & (0x1F));
	//ADCSRA |=(1<<ADSC);
	SETBIT(ADC_CTRL_STAT,ADC_CVS);
	//while(((ADCSRA>>ADIF)& 1)==0);
	while(!(ADC_CTRL_STAT &(1<<ADC_INTFLAG)));
	//ADCSRA |=(1<<ADIF);
	ADC_CTRL_STAT |=(1<<ADC_INTFLAG);
	//data =ADCL;
	data =ADC_LOW_BYTE;
	//data |=(ADCH<<8);
	data |=(ADC_HIGH_BYTE<<8);
	// ADMUX, ADCSRA ,ADCL ,ADCH
	return data;
}