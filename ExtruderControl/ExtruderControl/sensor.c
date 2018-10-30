/*
 * sensor.c
 *
 * Created: 10/30/2018 12:35:47 AM
 *  Author: norha
 */ 
#include "sensor.h"
void ADC_INIT ()
{
	ADMUX = 0xB0;         //Choice right adjusted and ADC0
	ADCSRA = 0x87;        //Enable ADEN and ADSC and choice 64 Division Factor

}
uint16_t ADC_READ ()
{   uint16_t store_temp ;
	ADCSRA |= (1<<6);        //Enable ADSC
	while (ADCSRA & (1<<6) );
	uint16_t A_LH = ADCL +(ADCH * 256);
	store_temp = ((A_LH * NOS_VR) / P) ;   //convert from volt to temperature
	
	return store_temp;
	
}