/*
 * stepper.h
 *
 * Created: 25/10/2018 10:14:48 ã
 *  Author: eng_s
 * This library controls the bipolar Stepper Motor with the A9488 driver
 * with 4 stepper A,B,C,D
 * the step pin is control the speed of rotation by the rate of change
 * in it with msx pins.
 * and the DIR pin is control the direction of rotation cw or ccw
 */
#include "stepper.h"
#include<util/delay.h>
#include <avr/io.h>
#include <stdbool.h>
int speed = 0;
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
//library interface description
int StepperInit(int steps,uint8_t sp)  //types of steps (1,2,6,8,16),speed of rotation in rpm
{
	switch (steps){
		case 1:steper_1step();break;
		case 2:steper_Hstep();break;
		case 6:steper_Qstep();break;
		case 8:steper_Estep();break;
		case 16:steper_Sstep();break;
	}
	speed = sp;
}
int setspeed(int sp){
	sp=(1/(sp/60))*1000;//1Hz = 60 rpm & t = 1/f &1s = 1000ms
	while(sp > 0){
		_delay_us(1);
		sp-=1;
	}
}
void Stepper_A_rev(bool clockw,uint8_t NuOfSteps){//rotate clockwise or ccw , number of steps for stepperA
	if (clockw)
	{
		pinChange(DIRA,1);
	}
	else
	{
		pinChange(DIRA,0);
	}
	
	while (NuOfSteps != 0)
	{
		pinChange(StepA,1);
		setspeed(speed); 
		pinChange(StepA,0);
		setspeed(speed);
		NuOfSteps -= 1;
	}
}
void Stepper_B_rev(bool clockw,uint8_t NuOfSteps){//rotate clockwise or ccw , number of steps for stepperB
	if (clockw)
	{
		pinChange(DIRB,1);
	}
	else
	{
		pinChange(DIRB,0);
	}
	
	while (NuOfSteps != 0)
	{
		pinChange(StepB,1);
		setspeed(speed); //1Hz = 60 rpm & t = 1/f &1s = 1000ms
		pinChange(StepB,0);
		setspeed(speed);
		NuOfSteps -= 1;
	}
}
void Stepper_C_rev(bool clockw,uint8_t NuOfSteps){//rotate clockwise or ccw , number of steps for stepperC
	if (clockw)
	{
		pinChange(DIRC,1);
	}
	else
	{
		pinChange(DIRC,0);
	}
	
	while (NuOfSteps != 0)
	{
		pinChange(StepC,1);
		setspeed(speed); //1Hz = 60 rpm & t = 1/f &1s = 1000ms
		pinChange(StepC,0);
		setspeed(speed);
		NuOfSteps -= 1;
	}
}
void Stepper_D_rev(bool clockw,uint8_t NuOfSteps){//rotate clockwise or ccw , number of steps for stepperC
	if (clockw)
	{
		pinChange(DIRD,1);
	}
	else
	{
		pinChange(DIRD,0);
	}
	
	while (NuOfSteps != 0)
	{
		pinChange(StepD,1);
		setspeed(speed); //1Hz = 60 rpm & t = 1/f &1s = 1000ms
		pinChange(StepD,0);
		setspeed(speed);
		NuOfSteps -= 1;
	}
}