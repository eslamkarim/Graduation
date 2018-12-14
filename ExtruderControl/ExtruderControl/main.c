/*
 * ExtruderControl.c
 *
 * Created: 10/24/2018 7:35:17 PM
 * Author : PRISCA
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#define NOISE_REDUCTION 1
#include <avr/io.h>
#include "stepper.h"
#include "lcd.h"
#include <stdbool.h> // library for boolean variable
#include <avr/interrupt.h> // library to active external interrupts
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/sleep.h>
bool status; // to control the start and stop button
int val;
int temp;
long R;
double Thermister;
int thr ;
int dist ;
int stspeed ;
char output[100]; // variable to storage the value of converted integer in it
int mood = 0;
volatile int value; // to storage the instantaneous change in ADC converter
int ADC_value(bool x);// ADC setup
void Init(void);// initial library to set up the external devices
double getTemp();
int main(void)
{
	Init(); // set up the devices
    while (1) 
    {
		 switch(mood){
			 case 1: //enter the temp using the variable res
				thr=ADC_value(1)/(4.88E-3);
				Lcd4_Clear();
				itoa(thr, output, 10);
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("set the temperature");
				Lcd4_Set_Cursor(2,1);
				Lcd4_Write_String(output);
			case 2://enter the speed using the variable res
				stspeed=ADC_value(1)/(4.88E-3);
				Lcd4_Clear();
				itoa(stspeed, output, 10);
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("set the speed");
				Lcd4_Set_Cursor(2,1);
				Lcd4_Write_String(output);
			case 3://enter the distance using the variable res
				dist=ADC_value(1)/(4.88E-3);
				Lcd4_Clear();
				itoa(dist, output, 10);
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("set the distance");
				Lcd4_Set_Cursor(2,1);
				Lcd4_Write_String(output);
			case 4://control the temp ant set it cont.
				Lcd4_Clear();
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("pleas wait tell temperature set");
				PORTC |= (1<<PC5);
				while(getTemp()< thr + 3){}
				PORTC &= ~(1<<PC5);
				Lcd4_Clear();
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("the temperature is set");
				Lcd4_Set_Cursor(2,1);
				Lcd4_Write_String("pass extrude");	
		 }
		 if (getTemp() <= thr)
		 {
			 PORTC |= (1<<PC5);
		 }
		 if (getTemp() >= thr+3)
		 {
			 PORTC &= ~(1<<PC5);
		 }
		 if (getTemp() < thr-3){
			 PORTC |= (1<<PC5);
			 status = 0;
		 }
		 if (status == 1)
		 {
			 StepperInit(16,stspeed);
			 Stepper_A_rev(cw,dist);
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
	value=ADC*(4.88E-3);		 // to convert D/A (the analoge volt) * (5/1024) = (the analoge volt)*0.00488 
	return value;                // the output of lm35 is vt = T/100 => T = vt*100 ==>so the value = (the analoge volt)*0.00488*100
}
double getTemp()
{
	val = ADC_value(0);		/* store adc value on val register */
	R=((10230000/val) - 100000);/* calculate the resistance */
	Thermister = log(R);	/* calculate natural log of resistance */
	/* Steinhart-Hart Thermistor Equation: */
	/*  Temperature in Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)		*/
	/*  where A = 0.001129148, B = 0.000234125 and C = 8.76741*10^-8  */
	Thermister = 1 / (0.001129148 + (0.000234125 * Thermister) + (0.0000000876741 * Thermister * Thermister * Thermister));
	Thermister = Thermister - 273.15;/* convert kelvin to °C */
	return Thermister;
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
	DDRC |=(1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3)|(1<<PC4)|(1<<PC5);// use PC0,1,2,3,4 as output for a9488 driver
	Lcd4_Init();// setup LCD at 4 bit mode
}
ISR(INT0_vect)
{
	#if !NOISE_REDUCTION
	if (mood != 4)
	{
		mood++;
	}
	else{
		if (Thermister >= thr)
		{
			status = 1;// start extude
		}
	}
	#endif
}
ISR(INT1_vect)
{
	status = 0;// stop button is pressed
}



