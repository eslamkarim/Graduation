/*
 * ExtruderControl.c
 *
 * Created: 10/24/2018 7:35:17 PM
 * Author : PRISCA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"
#include "sensor.h"
#define MAX_TEMP 400                  //After reaching to this temperature the heater will stop working
uint16_t result;                      //store current temperature
char S [4];                           //store the temp that convert to string to display

int main(void)
{
    DDRB = 0xFF;                  //Port B is output
	DDRA &=~ (1<<1);              //port A bin 0 is input
	Lcd4_Init();
    ADC_INIT ();
	//ADCSRA /= (1<<6);
    while (1) 
    {   
		result = ADC_READ();
		itoa (result , S ,10);                           //convert integer  to string
		/*
		Lcd4_Set_Cursor(0,1);                           // write on row 0 column 1
	    Lcd4_Write_String("The Temperature Is : ") ;
		_delay_ms(1000);
		
		Lcd4_Clear();*/
		
		Lcd4_Set_Cursor(1,5);                          // write on row 1 column 5
		Lcd4_Write_String(S) ;
		_delay_ms(1000);
	/*	
     	if (result <= MAX_TEMP)
		{
		  PORTB |= (1<<7);                            // turn on the heater
		  while (result <=MAX_TEMP);
		 
		}
		else if (result > MAX_TEMP)
		{
		  PORTB &=~  (1<<7);                         // turn off the heater
		  while (result > MAX_TEMP );
		}*/
    }
}

