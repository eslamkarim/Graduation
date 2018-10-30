/*
 * LCD_4it.h
 *
 * Created: 10/26/2018 5:12:40 PM
 *  Author: norha
 */ 


#ifndef LCD_4BIT_H_
#define LCD_4BIT_H_

#define Data_port D
#define RS_RW_E_port C
#define RS_bin 0
#define RW_bin 1
#define E_bin  2
char t; 


void Lcd_Enable();
void Lcd_Init();
void Write_Command(char Command);
void Write_Data(char Data);
void Write_String(char *S);
void Set_Cursor(char row, char cloumn);
void Lcd_Chracter(char row, char cloumn, char Data);void Lcd_Out(char row, char cloumn, char *Data);
void Lcd_String(char row, char cloumn, char *Data);
void Write_Number(char row, char cloumn, char Number);




#endif /* LCD_4IT_H_ */