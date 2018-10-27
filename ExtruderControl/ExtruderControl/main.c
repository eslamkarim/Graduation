/*
 * ExtruderControl.c
 *
 * Created: 10/24/2018 7:35:17 PM
 * Author : PRISCA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "stepper.h"
#include "lcd.h"
#define ms1 St_PORTC0
#define ms2 St_PORTC1
#define ms3 St_PORTC2
#define DIRA St_PORTC3
#define StepA St_PORTC4
#define D4 eS_PORTB0
#define D5 eS_PORTB1
#define D6 eS_PORTB2
#define D7 eS_PORTB3
#define RS eS_PORTB4
#define EN eS_PORTB5
int main(void)
{
	DDRC = 0xFF;
	DDRB = 0xFF;
	StepperInit(16,1000);
	Lcd4_Init();
	
    while (1) 
    {
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("the stepper is rotate with speed 1000 rpm") ;
		Stepper_A_rev(cw,50);
    }
}



