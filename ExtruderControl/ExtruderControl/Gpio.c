
/*
 * Gpio.c
 *
 * Created: 02/06/2018 04:28:17 م
 *  Author: norhan tarek
 */ 

//#include "src/asf.h"
#include "Gpio.h"
#include "stdint.h"

char Casting (int reg)
{
	return ( (*(volatile char*) reg));
}

void pin_direction (char base, char bin, char state )
{
	if (state == output)
	{
		set_bin ( (base+1) , bin);
	}
	else
	{
		reset_bin( (base+1) , bin);
	}

}


char pin_Read(char base,char bin)
{
	char t ;
	t = Casting (base)  && (1<<bin);   
	return t;
}

void pin_write (char base, char bin ,char p )
{
	if (p ==0)
	set_bin ( (base+2) , bin);
	else
	reset_bin ( (base+2) , bin);
}

void port_direction (char base, char state )
{
	if (state == output)
	{
		( (*(volatile char*) (base+1)) = 0xff);
	}
	
	else if (state == input)
	{
		( (*(volatile char*) (base+1)) = 0x00);
	}
}
char port_Read(char base)
{
	char t ;
	t = Casting(base) ;
	return t;
}

void port_write (char base, char p )
{
	(*(volatile char*) (base+2)) = p ;
}


