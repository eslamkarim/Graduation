/*
 * sensor.h
 *
 * Created: 10/30/2018 12:10:59 AM
 *  Author: norha
 */ 


#ifndef SENSOR_H_
#define SENSOR_H_
#define P 10/1000         //volt per temperature
#define NOS_VR 1024/5    //number of steps per v ref
#include <avr/io.h>

void ADC_INIT ();
uint16_t ADC_READ ();


#endif /* SENSOR_H_ */