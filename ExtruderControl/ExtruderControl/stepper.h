/*
 * stepper.h
 *
 * Created: 25/10/2018 10:14:48 م
 *  Author: eng_s
 * This library controls the bipolar Stepper Motor with the A9488 controller 
 */
#include<util/delay.h>
#include <avr/io.h>
#ifndef stepper_H_
#define stepper_H_
#define St_PORTA0 0
#define St_PORTA1 1
#define St_PORTA2 2
#define St_PORTA3 3
#define St_PORTA4 4
#define St_PORTA5 5
#define St_PORTA6 6
#define St_PORTA7 7
#define St_PORTB0 10
#define St_PORTB1 11
#define St_PORTB2 12
#define St_PORTB3 13
#define St_PORTB4 14
#define St_PORTB5 15
#define St_PORTB6 16
#define St_PORTB7 17
#define St_PORTC0 20
#define St_PORTC1 21
#define St_PORTC2 22
#define St_PORTC3 23
#define St_PORTC4 24
#define St_PORTC5 25
#define St_PORTC6 26
#define St_PORTC7 27
#define St_PORTD0 30
#define St_PORTD1 31
#define St_PORTD2 32
#define St_PORTD3 33
#define St_PORTD4 34
#define St_PORTD5 35
#define St_PORTD6 36
#define St_PORTD7 37
#endif
#define cw 1
#define ccw 0
#ifndef ms1
#define ms1 St_PORTC0    //ms1 pin from the driver connect to portA0
#define ms2 St_PORTC1    //ms2 pin from the driver connect to portA1
#define ms3 St_PORTC2    //ms3 pin from the driver connect to portA2
#define StepA St_PORTC3  //step pin for first stepper from the driver connect to portA3
#define DIRA St_PORTC4   //direction pin for first stepper from the driver connect to portA4
#define StepB St_PORTA5  //step pin for 2nd stepper from the driver connect to portA5
#define DIRB St_PORTA6   //direction pin for 2nd stepper from the driver connect to portA6
#define StepC St_PORTA7  //step pin for 3rd stepper from the driver connect to portA7
#define DIRC St_PORTB0   //direction pin for 3rd stepper from the driver connect to portB0
#define StepD St_PORTB1  //step pin for 4th stepper from the driver connect to portB1
#define DIRD St_PORTB2   //direction pin for 4th stepper from the driver connect to portB2
#endif
// void pinChange(int a, int b)
// {
// 	if(b == 0)
// 	{
// 		if(a == St_PORTA0)
// 		PORTA &= ~(1<<PA0);
// 		else if(a == St_PORTA1)
// 		PORTA &= ~(1<<PA1);
// 		else if(a == St_PORTA2)
// 		PORTA &= ~(1<<PA2);
// 		else if(a == St_PORTA3)
// 		PORTA &= ~(1<<PA3);
// 		else if(a == St_PORTA4)
// 		PORTA &= ~(1<<PA4);
// 		else if(a == St_PORTA5)
// 		PORTA &= ~(1<<PA5);
// 		else if(a == St_PORTA6)
// 		PORTA &= ~(1<<PA6);
// 		else if(a == St_PORTA7)
// 		PORTA &= ~(1<<PA7);
// 		else if(a == St_PORTB0)
// 		PORTB &= ~(1<<PB0);
// 		else if(a == St_PORTB1)
// 		PORTB &= ~(1<<PB1);
// 		else if(a == St_PORTB2)
// 		PORTB &= ~(1<<PB2);
// 		else if(a == St_PORTB3)
// 		PORTB &= ~(1<<PB3);
// 		else if(a == St_PORTB4)
// 		PORTB &= ~(1<<PB4);
// 		else if(a == St_PORTB5)
// 		PORTB &= ~(1<<PB5);
// 		else if(a == St_PORTB6)
// 		PORTB &= ~(1<<PB6);
// 		else if(a == St_PORTB7)
// 		PORTB &= ~(1<<PB7);
// 		else if(a == St_PORTC0)
// 		PORTC &= ~(1<<PC0);
// 		else if(a == St_PORTC1)
// 		PORTC &= ~(1<<PC1);
// 		else if(a == St_PORTC2)
// 		PORTC &= ~(1<<PC2);
// 		else if(a == St_PORTC3)
// 		PORTC &= ~(1<<PC3);
// 		else if(a == St_PORTC4)
// 		PORTC &= ~(1<<PC4);
// 		else if(a == St_PORTC5)
// 		PORTC &= ~(1<<PC5);
// 		else if(a == St_PORTC6)
// 		PORTC &= ~(1<<PC6);
// 		else if(a == St_PORTC7)
// 		PORTC &= ~(1<<PC7);
// 		else if(a == St_PORTD0)
// 		PORTD &= ~(1<<PD0);
// 		else if(a == St_PORTD1)
// 		PORTD &= ~(1<<PD1);
// 		else if(a == St_PORTD2)
// 		PORTD &= ~(1<<PD2);
// 		else if(a == St_PORTD3)
// 		PORTD &= ~(1<<PD3);
// 		else if(a == St_PORTD4)
// 		PORTD &= ~(1<<PD4);
// 		else if(a == St_PORTD5)
// 		PORTD &= ~(1<<PD5);
// 		else if(a == St_PORTD6)
// 		PORTD &= ~(1<<PD6);
// 		else if(a == St_PORTD7)
// 		PORTD &= ~(1<<PD7);
// 	}
// 	else
// 	{
// 		if(a == St_PORTA0)
// 		PORTA |= (1<<PA0);
// 		else if(a == St_PORTA1)
// 		PORTA |= (1<<PA1);
// 		else if(a == St_PORTA2)
// 		PORTA |= (1<<PA2);
// 		else if(a == St_PORTA3)
// 		PORTA |= (1<<PA3);
// 		else if(a == St_PORTA4)
// 		PORTA |= (1<<PA4);
// 		else if(a == St_PORTA5)
// 		PORTA |= (1<<PA5);
// 		else if(a == St_PORTA6)
// 		PORTA |= (1<<PA6);
// 		else if(a == St_PORTA7)
// 		PORTA |= (1<<PA7);
// 		else if(a == St_PORTB0)
// 		PORTB |= (1<<PB0);
// 		else if(a == St_PORTB1)
// 		PORTB |= (1<<PB1);
// 		else if(a == St_PORTB2)
// 		PORTB |= (1<<PB2);
// 		else if(a == St_PORTB3)
// 		PORTB |= (1<<PB3);
// 		else if(a == St_PORTB4)
// 		PORTB |= (1<<PB4);
// 		else if(a == St_PORTB5)
// 		PORTB |= (1<<PB5);
// 		else if(a == St_PORTB6)
// 		PORTB |= (1<<PB6);
// 		else if(a == St_PORTB7)
// 		PORTB |= (1<<PB7);
// 		else if(a == St_PORTC0)
// 		PORTC |= (1<<PC0);
// 		else if(a == St_PORTC1)
// 		PORTC |= (1<<PC1);
// 		else if(a == St_PORTC2)
// 		PORTC |= (1<<PC2);
// 		else if(a == St_PORTC3)
// 		PORTC |= (1<<PC3);
// 		else if(a == St_PORTC4)
// 		PORTC |= (1<<PC4);
// 		else if(a == St_PORTC5)
// 		PORTC |= (1<<PC5);
// 		else if(a == St_PORTC6)
// 		PORTC |= (1<<PC6);
// 		else if(a == St_PORTC7)
// 		PORTC |= (1<<PC7);
// 		else if(a == St_PORTD0)
// 		PORTD |= (1<<PD0);
// 		else if(a == St_PORTD1)
// 		PORTD |= (1<<PD1);
// 		else if(a == St_PORTD2)
// 		PORTD |= (1<<PD2);
// 		else if(a == St_PORTD3)
// 		PORTD |= (1<<PD3);
// 		else if(a == St_PORTD4)
// 		PORTD |= (1<<PD4);
// 		else if(a == St_PORTD5)
// 		PORTD |= (1<<PD5);
// 		else if(a == St_PORTD6)
// 		PORTD |= (1<<PD6);
// 		else if(a == St_PORTD7)
// 		PORTD |= (1<<PD7);
// 	}
// }
// void Steper_pins(char a)
// {
// 	if(a & 1)
// 		pinChange(ms1,1);
// 	else
// 		pinChange(ms1,0);
// 		
// 	if(a & 2)
// 		pinChange(ms2,1);
// 	else
// 		pinChange(ms2,0);
// 	
// 	if(a & 4)
// 		pinChange(ms3,1);
// 	else
// 		pinChange(ms3,0);
// 	
// 	if(a & 8)
// 		pinChange(StepA,1);
// 	else
// 		pinChange(StepA,0);
// 	if(a & 16)
// 		pinChange(DIRA,1);
// 	else
// 		pinChange(DIRA,0);
// 	if(a & 32)
// 		pinChange(StepB,1);
// 	else
// 		pinChange(StepB,0);
// 	if(a & 64)
// 		pinChange(DIRB,1);
// 	else
// 		pinChange(DIRB,0);
// 	if(a & 128)
// 		pinChange(StepC,1);
// 	else
// 		pinChange(StepC,0);
// 	if(a & 256)
// 		pinChange(DIRC,1);
// 	else
// 		pinChange(DIRC,0);
// 	if(a & 512)
// 		pinChange(StepD,1);
// 	else
// 		pinChange(StepD,0);
// 	if(a & 1024)
// 		pinChange(DIRD,1);
// 	else
// 		pinChange(DIRD,0);
// 			
// }



