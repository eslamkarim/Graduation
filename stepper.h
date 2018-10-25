/*
 * stepper.h
 *
 * Created: 25/10/2018 10:14:48 م
 *  Author: eng_s
 * This library controls the bipolar Stepper Motor with the A9488 controller 
 */ 


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
#define cw 1
#define anticw 0

#ifndef step
#define step St_PORTA0  //step pin from the driver connect to portA0
#define ms1 St_PORTA1   //ms1 pin from the driver connect to portA1
#define ms2 St_PORTA2   //ms2 pin from the driver connect to portA2
#define ms3 St_PORTA3   //ms3 pin from the driver connect to portA3
#define DIR St_PORTA4   //ms3 pin from the driver connect to portA4
#endif

#include<util/delay.h>

void pinChange(int a, int b)
{
	if(b == 0)
	{
		if(a == St_PORTA0)
		PORTA &= ~(1<<PA0);
		else if(a == St_PORTA1)
		PORTA &= ~(1<<PA1);
		else if(a == St_PORTA2)
		PORTA &= ~(1<<PA2);
		else if(a == St_PORTA3)
		PORTA &= ~(1<<PA3);
		else if(a == St_PORTA4)
		PORTA &= ~(1<<PA4);
		else if(a == St_PORTA5)
		PORTA &= ~(1<<PA5);
		else if(a == St_PORTA6)
		PORTA &= ~(1<<PA6);
		else if(a == St_PORTA7)
		PORTA &= ~(1<<PA7);
		else if(a == St_PORTB0)
		PORTB &= ~(1<<PB0);
		else if(a == St_PORTB1)
		PORTB &= ~(1<<PB1);
		else if(a == St_PORTB2)
		PORTB &= ~(1<<PB2);
		else if(a == St_PORTB3)
		PORTB &= ~(1<<PB3);
		else if(a == St_PORTB4)
		PORTB &= ~(1<<PB4);
		else if(a == St_PORTB5)
		PORTB &= ~(1<<PB5);
		else if(a == St_PORTB6)
		PORTB &= ~(1<<PB6);
		else if(a == St_PORTB7)
		PORTB &= ~(1<<PB7);
		else if(a == St_PORTC0)
		PORTC &= ~(1<<PC0);
		else if(a == St_PORTC1)
		PORTC &= ~(1<<PC1);
		else if(a == St_PORTC2)
		PORTC &= ~(1<<PC2);
		else if(a == St_PORTC3)
		PORTC &= ~(1<<PC3);
		else if(a == St_PORTC4)
		PORTC &= ~(1<<PC4);
		else if(a == St_PORTC5)
		PORTC &= ~(1<<PC5);
		else if(a == St_PORTC6)
		PORTC &= ~(1<<PC6);
		else if(a == St_PORTC7)
		PORTC &= ~(1<<PC7);
		else if(a == St_PORTD0)
		PORTD &= ~(1<<PD0);
		else if(a == St_PORTD1)
		PORTD &= ~(1<<PD1);
		else if(a == St_PORTD2)
		PORTD &= ~(1<<PD2);
		else if(a == St_PORTD3)
		PORTD &= ~(1<<PD3);
		else if(a == St_PORTD4)
		PORTD &= ~(1<<PD4);
		else if(a == St_PORTD5)
		PORTD &= ~(1<<PD5);
		else if(a == St_PORTD6)
		PORTD &= ~(1<<PD6);
		else if(a == St_PORTD7)
		PORTD &= ~(1<<PD7);
	}
	else
	{
		if(a == St_PORTA0)
		PORTA |= (1<<PA0);
		else if(a == St_PORTA1)
		PORTA |= (1<<PA1);
		else if(a == St_PORTA2)
		PORTA |= (1<<PA2);
		else if(a == St_PORTA3)
		PORTA |= (1<<PA3);
		else if(a == St_PORTA4)
		PORTA |= (1<<PA4);
		else if(a == St_PORTA5)
		PORTA |= (1<<PA5);
		else if(a == St_PORTA6)
		PORTA |= (1<<PA6);
		else if(a == St_PORTA7)
		PORTA |= (1<<PA7);
		else if(a == St_PORTB0)
		PORTB |= (1<<PB0);
		else if(a == St_PORTB1)
		PORTB |= (1<<PB1);
		else if(a == St_PORTB2)
		PORTB |= (1<<PB2);
		else if(a == St_PORTB3)
		PORTB |= (1<<PB3);
		else if(a == St_PORTB4)
		PORTB |= (1<<PB4);
		else if(a == St_PORTB5)
		PORTB |= (1<<PB5);
		else if(a == St_PORTB6)
		PORTB |= (1<<PB6);
		else if(a == St_PORTB7)
		PORTB |= (1<<PB7);
		else if(a == St_PORTC0)
		PORTC |= (1<<PC0);
		else if(a == St_PORTC1)
		PORTC |= (1<<PC1);
		else if(a == St_PORTC2)
		PORTC |= (1<<PC2);
		else if(a == St_PORTC3)
		PORTC |= (1<<PC3);
		else if(a == St_PORTC4)
		PORTC |= (1<<PC4);
		else if(a == St_PORTC5)
		PORTC |= (1<<PC5);
		else if(a == St_PORTC6)
		PORTC |= (1<<PC6);
		else if(a == St_PORTC7)
		PORTC |= (1<<PC7);
		else if(a == St_PORTD0)
		PORTD |= (1<<PD0);
		else if(a == St_PORTD1)
		PORTD |= (1<<PD1);
		else if(a == St_PORTD2)
		PORTD |= (1<<PD2);
		else if(a == St_PORTD3)
		PORTD |= (1<<PD3);
		else if(a == St_PORTD4)
		PORTD |= (1<<PD4);
		else if(a == St_PORTD5)
		PORTD |= (1<<PD5);
		else if(a == St_PORTD6)
		PORTD |= (1<<PD6);
		else if(a == St_PORTD7)
		PORTD |= (1<<PD7);
	}
}
void Steper_pins(char a)
{
	if(a & 1)
	pinChange(step,1);
	else
	pinChange(step,0);
	
	if(a & 2)
	pinChange(ms1,1);
	else
	pinChange(ms1,0);
	
	if(a & 4)
	pinChange(ms2,1);
	else
	pinChange(ms2,0);
	
	if(a & 8)
	pinChange(ms3,1);
	else
	pinChange(ms3,0);
	if(a & 16)
	pinChange(D4,1);
	else
	pinChange(D4,0);
}
void steper_1step(){ // to make a full 1 step with 2 phase 
	pinChange(ms1,0);        // ms1 = 0,ms2 = 0,ms3 = 0 from a9488 data sheet
	pinChange(ms2,0);
	pinChange(ms3,0);
}
void steper_Hstep(){// to make a half 1 step with 1-2 phase ms1 = 1,ms2 = 0,ms3 = 0 from a9488 data sheet
	pinChange(ms1,1);
	pinChange(ms2,0);
	pinChange(ms3,0);
}
void steper_Qstep(){// to make a Quarter 1 step with w1-2 phase ms1 = 0,ms2 = 1,ms3 = 0 from a9488 data sheet
	pinChange(ms1,0);
	pinChange(ms2,1);
	pinChange(ms3,0);
}
void steper_Estep(){// to make a Eighth 1 step with 2w1-2 phase ms1 = 1,ms2 = 1,ms3 = 0 from a9488 data sheet
	pinChange(ms1,1);
	pinChange(ms2,1);
	pinChange(ms3,0);
}
void steper_Sstep(){// to make a Sixteenth 1 step with 4w1-2 phase ms1 = 1,ms2 = 1,ms3 = 0 from a9488 data sheet
	pinChange(ms1,1);
	pinChange(ms2,1);
	pinChange(ms3,1);
}
void stepper_rev(bool clockw,int steps, int sp, int no){ // (the direction of rotate,types of steps (1,2,6,8,16),speed of rotate,speed of motor in rpm , nombur of steps)
	if (clockw)
	{
		pinChange(DIR,1);	
	} 
	else
	{
		pinChange(DIR,0);	
	}
	switch steps{
		case 1:steper_1step();break;
		case 2:steper_Hstep();break;
		case 6:steper_Qstep();break;
		case 8:steper_Estep();break;
		case 16:steper_Sstep();break;
	}
	while (no != 0)
	{
		pinChange(step,1);
		_delay_ms(int(1/(no/60))); //1Hz = 60 rpm & t = 1/f
		pinChange(step,0);
		_delay_ms(int(1/(no/60)));
		no -= 1;
	}
}