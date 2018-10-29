/*
 * ExtruderControl.c
 *
 * Created: 10/24/2018 7:35:17 PM
 * Author : PRISCA
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include "stepper.h"
#include "lcd.h"
#include <stdbool.h> // library for boolean variable
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
bool status; // to control the start and stop button
char output[100]; // variable to storage the value of converted integer in it
volatile float value; // to storage the instantaneous change in ADC converter
// int pot_val(void);
// int them_val(void);
double ADC_value(bool x);
void Init(void);

int main(void)
{
	Init();
	
    while (1) 
    {
		
		float thr = ADC_value(0);
		if (status && thr>=27)
		{
			int speed = ADC_value(1);
			Lcd4_Clear();
			StepperInit(16,speed);
			itoa(speed, output, 10);// convert the value from integer to string to display
			Lcd4_Set_Cursor(1,1);
			Lcd4_Write_String("the speed is");
			Lcd4_Set_Cursor(2,1);
			Lcd4_Write_String(output);
			_delay_ms(500);
		} 
		else
		{
			ADC_value(0);
			Lcd4_Clear();
			sprintf(output,dtostrf(thr, 3,3,"%f"));
			Lcd4_Set_Cursor(1,1);
			Lcd4_Write_String(output);
			_delay_ms(500);
		}

    }
}

// int them_val(void)//ADC for thermistor lm35
// {
// 	ADCSRA |= 0x87; //to active A/D pins
// 	ADMUX |= (0 << MUX0)|(1 << REFS0); // to choose A/D pins
// 	ADCSRA |= (1 << ADSC); //active reading
// 	while(ADCSRA & (1<<ADSC)); // wait the A/D to complete reading and converting
// 	thr_value=ADC*0.00488; // final value
// 	return thr_value;
// }
// int pot_val(void)// ADC for speed pot.
// {
// 	ADCSRA |= 0x87; //to active A/D pins
// 	ADMUX |= (1 << MUX0)|(1 << REFS0); // to choose A/D pins
// 	ADCSRA |= (1 << ADSC); //active reading
// 	while(ADCSRA & (1<<ADSC)); // wait the A/D to complete reading and converting
// 	pot_value=ADC*0.00488; // final value
// 	return pot_value;
// }
double ADC_value(bool x)
{
		ADCSRA |= 0x87; //to active A/D pins
		ADMUX |= (1<<REFS0);
	switch (x){
		case 0:
			ADMUX |= (0 << MUX0);break;
		case 1:
			ADMUX |= (1 << MUX0);break;
	}	
	ADCSRA |= (1 << ADSC); //active reading
	while(ADCSRA & (1<<ADSC)); // wait the A/D to complete reading and converting
	value=ADC*(4.88E-3); // final value
	return value;
}
void Init(void){
	MCUCR |= (1 << ISC01)|(1 << ISC10);
	GICR |= (1 << INT0)|(1 << INT1);
	TCCR2 |= (1<<WGM20)|(1<<WGM21)|(1<<COM21)|(1<<CS20)|(1<<CS21)|(1<<CS22);
	sei();
	DDRB |=(1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5);
	DDRA |=(0<<PA0)|(0<<PA1);
	DDRC |=(1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3)|(1<<PC4);
	Lcd4_Init();
}
ISR(INT0_vect)
{
	status = 1;
}
ISR(INT1_vect)
{
	status = 0;
}



