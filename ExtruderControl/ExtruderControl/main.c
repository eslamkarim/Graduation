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

double posx = 0.0; // the current position of x
double posy = 0.0; // the current position of y
bool statusx; // to control the direction of x rotation
bool statusy; // to control the direction of y rotation
void Init(void);// initial library to set up the external devices
int main(void)
{
	Init();
	while (1)
	{
		double x = 100; // variable to store the received x axis
		double y = 100; // variable to store the received y axis
		double X ; // variable to control the movement of x axis
		double Y ; // variable to control the movement of x axis
		if (posx == 0)
		{
			X = x;
		} 
		else
		{
			X = x - posx;
		}
		if (posy == 0)
		{
			Y = y;
		}
		else
		{
			Y = y - posy;
		}
		if (X < 0 ){ // if the distance give a negative number make it positive and change the direction of motor rotation
			X *=-1;
			statusx = 1;
		}
		if (Y < 0 ){
			Y *=-1;
			statusy = 1;
		}
		while (X>=0) // go to the received position
		{
			Stepper_A_rev(statusx,1);
			X--;
		}
		while (Y>=0)
		{
			Stepper_A_rev(statusy,1);
			Y--;
		}
		posx = x;
		posy = y;
		x = 0.0;
		y = 0.0;
	}
}
void Init(void){
	StepperInit(16,1000);
}
// extruder code //
/*
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
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
				thr=ADC_value(1);
				Lcd4_Clear();
				itoa(thr, output, 10);
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("set the temperature");
				Lcd4_Set_Cursor(2,1);
				Lcd4_Write_String(output);
				_delay_ms(100);
				break;
			case 2://enter the speed using the variable res
				stspeed=ADC_value(1);
				Lcd4_Clear();
				itoa(stspeed, output, 10);
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("set the speed");
				Lcd4_Set_Cursor(2,1);
				Lcd4_Write_String(output);
				_delay_ms(100);
				break;
			case 3://enter the distance using the variable res
				dist=ADC_value(1);
				Lcd4_Clear();
				itoa(dist, output, 10);
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("set the distance");
				Lcd4_Set_Cursor(2,1);
				Lcd4_Write_String(output);
				_delay_ms(100);
				break;
			case 4://control the temp ant set it cont.
				Lcd4_Clear();
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("pleas wait tell temperature set");
				PORTC |= (1<<PC5);
				while(getTemp(0)< thr + 3){
						itoa(getTemp(0), output, 10);
						Lcd4_Set_Cursor(2,1);
						Lcd4_Write_String(output);
						_delay_ms(100);			
				}
				PORTC &= ~(1<<PC5);
				Lcd4_Clear();
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("the temperature is set");
				Lcd4_Set_Cursor(2,1);
				//Lcd4_Write_String("pass extrude");
				_delay_ms(500);

				break;	
		 }
		 if (mood == 5)
		 {
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
		 }
		 if (status == 1)
		 {
			 StepperInit(16,stspeed);
			 Stepper_A_rev(cw,dist);
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
	while(ADCSRA & (1<<ADSC)==0);	 // wait the A/D to complete reading and converting
	ADCSRA |=(1<<ADIF);
	value=ADC*(4.88E-3);		 // to convert D/A (the analoge volt) * (5/1024) = (the analoge volt)*0.00488 
	return ADC;                // the output of lm35 is vt = T/100 => T = vt*100 ==>so the value = (the analoge volt)*0.00488*100
}
double getTemp()
{
	Vo = ADC_value(0);
	R2 = R1 * (1023.0 / (float)Vo - 1.0);
	logR2 = log(R2);
	T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
	T = T - 273.15;
	return T;
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
	DDRC |=(1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3)|(1<<PC4)|(1<<PC5);// use PC0,1,2,3,4 as output for a9488 driver && PC5 for heater
	Lcd4_Init();// setup LCD at 4 bit mode
}
ISR(INT0_vect)
{
// #if !NOISE_REDUCTION
	if (mood != 4)
	{
		mood++;
	}
	else{
		if (getTemp() >= thr)
		{
			mood = 5;
			status = 1;// start extude
		}
	}
/ *#endif* /
}
ISR(INT1_vect)
{
	status = 0;// stop button is pressed
}
*/



