
/*
 * Gpio.h
 *
 * Created: 02/06/2018 04:28:42 م
 *  Author: norhan tarek
 */ 

#ifndef GPIO_H_
#define GPIO_H_

#define A  0x39
#define B  0x36
#define C  0x33
#define D  0x30
#define H  0xff


#define output 0
#define input 1

#define set_bin(reg,bit)   ( (*(volatile char*) reg) |= (1<<bit))
#define reset_bin(reg,bit)  ( (*(volatile char*) reg) &=~ (1<<bit))


char Casting (int reg);
void pin_direction (char base, char bin, char state );
char pin_Read(char base,char bin);
void pin_write (char base, char bin ,char p );
void port_direction (char base, char state ); 
char port_Read(char base);
void port_write (char base, char p );

#endif


