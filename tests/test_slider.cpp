#include "mbed.h"
#include <stdio.h>

AnalogIn slider(PTB0);
DigitalOut slider_reset(PTD3);
Serial pc(USBTX, USBRX);

#define USE_CHARACTER_LCD TRUE

/********************************************************************/
#ifdef USE_CHARACTER_LCD
// will change depending on connections

/*
pins defined in char_lcd_4x20.h
rs - PTE19
rw - PTE18
e  - PTE17
--using 4bit mode
db4 - PTE16
db5 - PTE6
db6 - PTE3
db7 - PTE2
*/
#define LCD_REFERENCE_VOLTAGE PTE30
AnalogOut aout(LCD_REFERENCE_VOLTAGE);

#include "char_lcd_4x20.h"
#endif

int main()
{
    float voltage;
    char buffer[50]; 
    character_lcd_initialize();
    while(1)
    {
        voltage = slider.read()*3.3;
        sprintf(buffer,"%f", voltage);
        pc.printf("voltage: %f\tas uint16_t: %i\n\r", voltage, slider.read_u16());

        character_lcd_cursor(0,0);
        character_lcd_puts("Active Sensor: ");
        character_lcd_putc('1');
        character_lcd_cursor(1,0);
        character_lcd_puts("Severity: ");
        character_lcd_puts("test mode");
        character_lcd_cursor(2,0);
        character_lcd_puts("Voltage: "); //replace 1 with volume variable
        character_lcd_puts(buffer);
        character_lcd_cursor(3,0);
        character_lcd_puts("ADVISORY ---");
        wait(1);
    }
}