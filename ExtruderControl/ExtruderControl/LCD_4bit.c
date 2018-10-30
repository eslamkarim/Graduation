/*
 * LCD_4bit.c
 *
 * Created: 10/26/2018 5:12:00 PM
 *  Author: norha
 */ 

#include "LCD_4bit.h"
#include "Gpio.h"
#include "stdint.h"
#include <util/delay.h>
#include <avr/io.h>

void Lcd_Enable()
{
	pin_write (RS_RW_E_port, E_bin ,1 );
	_delay_us (1);
	pin_write (RS_RW_E_port, E_bin ,0 );
	_delay_us (1);
}

void Lcd_Init()
{  
    t = Casting (Data_port+2);
	port_direction (Data_port, output );
	port_direction (RS_RW_E_port, output );
	port_write (Data_port, 0x00 );
	//port_write (RS_RW_E_port, 0x00 );
	
	_delay_ms(20);
	t &= 0x0f;
	Write_Command(0x30);
	Lcd_Enable();
	
	_delay_ms(6);
	t &= 0x0f;
	Write_Command(0x30);
	Lcd_Enable();
	
	_delay_us(150);
	t &= 0x0f;
	Write_Command(0x30);
	Lcd_Enable();
	
	t &= 0x0f;
	Write_Command(0x20);
	Lcd_Enable();
	
	
	Write_Command(0x20);
	Write_Command(0x20);
	_delay_ms(2);
	Write_Command(0x01);
	_delay_ms(2);
	Write_Command(0x02);
	_delay_ms(2);
	Write_Command(0x06);
	_delay_ms(2);
	Write_Command(0x0c);
	_delay_ms(2);
	Write_Command(0x14);
	_delay_ms(2);
	Write_Command(0x80);
	_delay_ms(2);
	
	
}



void Write_Command(char Command)
{   
    
	pin_write (RS_RW_E_port, RS_bin ,1 );
	pin_write (RS_RW_E_port, RW_bin ,0 );
	t = Casting (Data_port+2); 
	t &= 0x0f;
	t |= (Command & 0xf0);
	Lcd_Enable();
	t &= 0x0f;
	t |= ( (Command << 4) & 0xf0);
	Lcd_Enable();
}

void Write_Data(char Data)
{ 
	pin_write (RS_RW_E_port, RS_bin ,1 );
	pin_write (RS_RW_E_port,RW_bin ,0 );
	
	t = Casting (Data_port+2); 
	t &= 0x0f;
	t |= (Data & 0xf0);
	Lcd_Enable();
	t &= 0x0f;
	t |= ( (Data << 4) & 0xf0);
	
	Lcd_Enable();
	
}

void Write_String(char* s)
{
	while (*s)
	{
	Write_Data(*s++);
	_delay_ms(3);
	}
	
}

void Set_Cursor(char row, char cloumn)
{
	Write_Command(0x80 | ((row * 0x40) + cloumn) );
	Lcd_Enable();
}
	
void Lcd_Chracter(char row, char cloumn, char Data)
{
	Set_Cursor( row, cloumn);
	Write_Data(Data);
}
void Lcd_String(char row, char cloumn, char *Data)
{
	Set_Cursor( row, cloumn);
	Write_String(Data);
}

void Write_Number(char row, char cloumn, char Number)
{
	Set_Cursor(row,cloumn);
	if (Number < 10)
	Write_Data(Number + 0x30);
	if (Number >= 10);
	Write_Data((Number / 10) + 0x30);
	Write_Data((Number % 10) + 0x30);
}
