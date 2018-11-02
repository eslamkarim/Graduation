#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main(void)
{
    lcd_init(LCD_DISP_ON_CURSOR); /* initialize lcd, display and cursor */


    while(1)                      /* Stay awake */
    {
        lcd_clrscr();             /* clear screen */
        lcd_home();               /* cursor to 0,0 */
        lcd_puts("Hello");        /* Print "Hello" */
        lcd_gotoxy(0,1);          /* move cursor to 2nd row 1st column */
        lcd_puts("Prisca!");      /* Print "Prisca!" */
        _delay_ms(100);           /* wait 100ms */
    }
}
