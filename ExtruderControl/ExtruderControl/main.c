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
#include <avr/interrupt.h> // library to active external interrupts
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
bool status; // to control the start and stop button
int thr ;
int stspeed ;
char output[100]; // variable to storage the value of converted integer in it
volatile int value; // to storage the instantaneous change in ADC converter
int ADC_value(bool x);// ADC setup
void Init(void);// initial library to set up the external devices
int main(void)
{
	Init(); // set up the devices
    while (1) 
    {
		 
		if (status && ADC_value(0)>=27) // if start button is pressed and the temperature is 27 or greater the stepper is started
		{
			ADC_value(1);
			int ADC_speed = ADC*(0.0978);
			if (stspeed != ADC_speed)
			{
				stspeed = ADC_speed;// to make the change of speed from 0 to 100 mm/s
				Lcd4_Clear();
				itoa(stspeed, output, 10);// convert the value from integer to string to display
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("the speed is");
				Lcd4_Set_Cursor(2,1);
				Lcd4_Write_String(output);
				_delay_ms(100);
			}
			StepperInit(16,stspeed);
			Stepper_A_rev(cw,1);
		} 
		else // if the start button is not pressed or stop button is pressed or temperature is lower than 27 the stepper is stopped
		{
			if (thr != ADC_value(0))
			{
				thr = ADC_value(0);
				Lcd4_Clear();
				itoa(thr, output, 10);
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("the temperature");
				Lcd4_Set_Cursor(2,1);
				Lcd4_Write_String(output);
			}
		}

    }
}
int ADC_value(bool x)
{
	switch (x){// to choose between ADC0 and ADC1
		case 0:
			ADMUX &= ~(1 << MUX0);break; // reset MUX0 to select ADC0
		case 1:
			ADMUX |= (1 << MUX0);break; // set MUX0 to select ADC1
	}	
	ADCSRA |= (1 << ADSC);		  //active reading
	while(ADCSRA & (1<<ADSC));	 // wait the A/D to complete reading and converting
	value=ADC*(4.88E-1);		 // to convert D/A (the analoge volt) * (5/1024) = (the analoge volt)*0.00488 
	return value;                // the output of lm35 is vt = T/100 => T = vt*100 ==>so the value = (the analoge volt)*0.00488*100
}
void Init(void){
	ADCSRA |= 0x87; //to active A/D pins
	ADMUX |= (1<<REFS0);// external reference volt is selected
	MCUCR |= (1 << ISC01)|(1 << ISC10); // mean that the rising of the interrupt pin make external interrupt
	                                    //  rising mean that when the pulse goes from low to high
	GICR |= (1 << INT0)|(1 << INT1);// select the interrupts pins that will use
	sei(); // to active external interrupts
	DDRB |=(1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5);// use PB0,1,2,3,4,5 as output for LCD
	DDRA |=(0<<PA0)|(0<<PA1);// use PA0,1 as input for thermistor and pot_resestance
	DDRC |=(1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3)|(1<<PC4);// use PC0,1,2,3,4 as output for a9488 driver
	Lcd4_Init();// setup LCD at 4 bit mode
}
ISR(INT0_vect)
{
	status = 1; // start button is pressed
}
ISR(INT1_vect)
{
	status = 0;// stop button is pressed
}



