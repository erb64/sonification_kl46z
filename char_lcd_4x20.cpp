#ifndef CHARACTER_LCD_H
#define CHARACTER_LCD_H

#include "stdint.h"

/* This file contains functions for controlling a standard character LCD. */
/* This is assumed to use a HD44780 chipset or equivalent. */

/* Default is to not use RW pin and write-only the LCD */
#ifndef CHARACTER_LCD_USE_RW
/* #define CHARACTER_LCD_USE_RW */
#endif

#ifdef CHARACTER_LCD_USE_RW 
#ifndef CHARACTER_LCD_RW
#define CHARACTER_LCD_RW PTE18
#endif
#endif

#ifndef CHARACTER_LCD_RS
#define CHARACTER_LCD_RS PTE17
#endif
#ifndef CHARACTER_LCD_E
#define CHARACTER_LCD_E PTE19
#endif

/* Default is to use 4-bit data bus */
#ifndef CHARACTER_LCD_BUS_8BITS
/* #define CHARACTER_LCD_BUS_8BITS */
#endif

/*
#ifndef CHARACTER_LCD_BUS_WIDTH
#define CHARACTER_LCD_BUS_WIDTH 4
#endif

#if ((CHARACTER_LCD_BUS_WIDTH != 4) && (CHARACTER_LCD_BUS_WIDTH != 8))
#undef CHARACTER_LCD_BUS_WIDTH
#define CHARACTER_LCD_BUS_WIDTH 4
#endif
*/

#ifdef CHARACTER_LCD_BUS_8BITS
#ifndef CHARACTER_LCD_DB0
#define CHARACTER_LCD_DB0 PTE20
#endif
#ifndef CHARACTER_LCD_DB1
#define CHARACTER_LCD_DB1 PTE21
#endif
#ifndef CHARACTER_LCD_DB2
#define CHARACTER_LCD_DB2 PTE22
#endif
#ifndef CHARACTER_LCD_DB3
#define CHARACTER_LCD_DB3 PTE23
#endif
#endif

#ifndef CHARACTER_LCD_DB4
#define CHARACTER_LCD_DB4 PTE16
#endif
#ifndef CHARACTER_LCD_DB5
#define CHARACTER_LCD_DB5 PTE6
#endif
#ifndef CHARACTER_LCD_DB6
#define CHARACTER_LCD_DB6 PTE3
#endif
#ifndef CHARACTER_LCD_DB7
#define CHARACTER_LCD_DB7 PTE2
#endif

#ifndef character_lcd_rs
DigitalOut character_lcd_rs(CHARACTER_LCD_RS);
#endif

#ifndef character_lcd_e
DigitalOut character_lcd_e(CHARACTER_LCD_E);
#endif

#ifdef CHARACTER_LCD_USE_RW 
DigitalOut character_lcd_rw(CHARACTER_LCD_RW);
#endif

#ifndef character_lcd_data
#ifndef CHARACTER_LCD_USE_RW 
#ifndef CHARACTER_LCD_BUS_8BITS
BusOut character_lcd_data(CHARACTER_LCD_DB4, CHARACTER_LCD_DB5, CHARACTER_LCD_DB6, CHARACTER_LCD_DB7);
#endif
#ifdef CHARACTER_LCD_BUS_8BITS
BusOut character_lcd_data(CHARACTER_LCD_DB0, CHARACTER_LCD_DB1, CHARACTER_LCD_DB2, CHARACTER_LCD_DB3, CHARACTER_LCD_DB4, CHARACTER_LCD_DB5, CHARACTER_LCD_DB6, CHARACTER_LCD_DB7);
#endif
#endif
#ifdef CHARACTER_LCD_USE_RW  
#ifndef CHARACTER_LCD_BUS_8BITS
BusInOut character_lcd_data(CHARACTER_LCD_DB4, CHARACTER_LCD_DB5, CHARACTER_LCD_DB6, CHARACTER_LCD_DB7);
#endif
#ifdef CHARACTER_LCD_BUS_8BITS
BusInOut character_lcd_data(CHARACTER_LCD_DB0, CHARACTER_LCD_DB1, CHARACTER_LCD_DB2, CHARACTER_LCD_DB3, CHARACTER_LCD_DB4, CHARACTER_LCD_DB5, CHARACTER_LCD_DB6, CHARACTER_LCD_DB7);
#endif
#endif
#endif


#define CHARACTER_LCD_ADDRESS_PREFIX 0x80

#ifndef CHARACTER_LCD_ROWS
#define CHARACTER_LCD_ROWS 4
#endif

#ifndef CHARACTER_LCD_COLUMNS
#define CHARACTER_LCD_COLUMNS 20
#endif

#ifndef CHARACTER_LCD_ROW0_START
#define CHARACTER_LCD_ROW0_START 0x00
#endif

#ifndef CHARACTER_LCD_ROW1_START
#define CHARACTER_LCD_ROW1_START 0x40
#endif

#ifndef CHARACTER_LCD_ROW2_START
#define CHARACTER_LCD_ROW2_START CHARACTER_LCD_ROW0_START+CHARACTER_LCD_COLUMNS
#endif

#ifndef CHARACTER_LCD_ROW3_START
#define CHARACTER_LCD_ROW3_START CHARACTER_LCD_ROW1_START+CHARACTER_LCD_COLUMNS
#endif

#ifndef RS_COMMAND
#define RS_COMMAND 0
#endif

#ifndef RS_DATA
#define RS_DATA 1
#endif

#ifndef character_lcd_row_offsets
uint8_t character_lcd_row_offsets[4]={CHARACTER_LCD_ROW0_START,CHARACTER_LCD_ROW1_START,CHARACTER_LCD_ROW2_START,CHARACTER_LCD_ROW3_START};
#endif

#ifndef CHARACTER_LCD_STANDARD_DELAY
#define CHARACTER_LCD_STANDARD_DELAY 100E-6 //may change this. display is physically capable of updating faster.
#endif

#ifndef CHARACTER_LCD_EXTENDED_DELAY
#define CHARACTER_LCD_EXTENDED_DELAY 2E-3
#endif

#ifndef CHARACTER_LCD_PULSE_DELAY
#define CHARACTER_LCD_PULSE_DELAY 5E-6 //need to test
#endif

void character_lcd_pulse_e(void)
{
    character_lcd_e=0;
    wait(CHARACTER_LCD_PULSE_DELAY);
    character_lcd_e=1;
    wait(CHARACTER_LCD_PULSE_DELAY);
    character_lcd_e=0;
    wait(CHARACTER_LCD_PULSE_DELAY); 
}

int character_lcd_write_nybble(uint8_t lcd_data, uint8_t lcd_select)
{
    character_lcd_e=0;
#ifdef CHARACTER_LCD_USE_RW 
    character_lcd_rw=0;
    character_lcd_data.output();
#endif    
    if((lcd_select < RS_COMMAND) || (lcd_select > RS_DATA))
    {
        return(-1);
    }
    character_lcd_rs=lcd_select;
#ifndef CHARACTER_LCD_BUS_8BITS
    character_lcd_data=(lcd_data&0x0F);   /*nybble into 4 bits*/
#endif   
#ifdef CHARACTER_LCD_BUS_8BITS
    character_lcd_data=(lcd_data<<4);   /*nybble on upper 4 bits of 8*/
#endif   
    character_lcd_pulse_e();
    wait(CHARACTER_LCD_STANDARD_DELAY);
    return(lcd_data);
    
} /* end of character_lcd_write_nybble() */

int character_lcd_write_byte(uint8_t lcd_data, uint8_t lcd_select)
{
    int temp;
    character_lcd_e=0;
#ifdef CHARACTER_LCD_USE_RW 
    character_lcd_rw=0;
    character_lcd_data.output();
#endif    
    if((lcd_select < RS_COMMAND) || (lcd_select > RS_DATA))
    {
        return(-1);
    }
    character_lcd_rs=lcd_select;
#ifndef CHARACTER_LCD_BUS_8BITS
    temp=character_lcd_write_nybble(lcd_data>>4, lcd_select);   /*upper nybble*/
    if(temp < 0) {return(temp); }
    temp=character_lcd_write_nybble(lcd_data&0x0F, lcd_select);   /*lower nybble*/
    if(temp < 0) {return(temp); }
 #endif   
#ifdef CHARACTER_LCD_BUS_8BITS
    character_lcd_data=(lcd_data);   /*all 8 bits of bus simultaneously*/
#endif
 
    if((lcd_select == RS_COMMAND) && (lcd_data <= 0x03)) 
    {   wait(CHARACTER_LCD_EXTENDED_DELAY); }
    return(lcd_data);
    
} /* end of character_lcd_write_byte() */

void character_lcd_initialize(void)
{
    wait(20E-3);
    character_lcd_write_nybble(0x03,RS_COMMAND);        /* reset signal, must be repeated 3 times with delays */
    wait(20E-3);
    character_lcd_write_nybble(0x03,RS_COMMAND);        /* reset signal, must be repeated 3 times with delays */
    wait(20E-3);
    character_lcd_write_nybble(0x03,RS_COMMAND);        /* reset signal, must be repeated 3 times with delays */

#ifndef CHARACTER_LCD_BUS_8BITS
    character_lcd_write_nybble(0x02,RS_COMMAND);        /* select 4-bit mode */
    character_lcd_write_byte(0x28,RS_COMMAND);          /*use both/all lines, use standard size characters (5x7 dots) */
#endif
#ifdef CHARACTER_LCD_BUS_8BITS
    character_lcd_write_byte(0x38,RS_COMMAND);          /* select 8-bit mode, use both/all lines, use standard size characters (5x7 dots) */
#endif 
   
    character_lcd_write_byte(0x0F,RS_COMMAND);          /* turn display on, turn cursor on, cursor blinks */
    character_lcd_write_byte(0x10,RS_COMMAND);          /* cursor moves after write, characters shift to left */
    character_lcd_write_byte(0x01,RS_COMMAND);          /* clear LCD and move cursor to row 0, column 0 */

}

int character_lcd_set_data_address(uint8_t lcd_address)
{
    return( character_lcd_write_byte((lcd_address|CHARACTER_LCD_ADDRESS_PREFIX),RS_COMMAND) );
}

int character_lcd_set_CG_address(uint8_t lcd_address)
{
    return( character_lcd_write_byte((0x40+(lcd_address&0x3F)),RS_COMMAND) );
}

int character_lcd_cursor(uint8_t row, uint8_t column)
{
    if((row >= CHARACTER_LCD_ROWS) || (column >= CHARACTER_LCD_COLUMNS))
    {
        return(-1);
    }    
    return( character_lcd_set_data_address(character_lcd_row_offsets[row]+column) );
}

int character_lcd_putc(char lcd_data)
{
    return( character_lcd_write_byte((uint8_t) lcd_data, RS_DATA) );
}

int character_lcd_puts(char *str)
{
    int i, temp;
    for(i=0; str[i]; i++)
    {
        temp=character_lcd_write_byte((uint8_t) str[i], RS_DATA);
        if(temp<0){ return(temp); }
    }
    return(0);
}

#ifdef CHARACTER_LCD_USE_RW  
int character_lcd_read_nybble(uint8_t *lcd_data, uint8_t lcd_select)
{
    character_lcd_e=0;
    character_lcd_rw=1;
    character_lcd_data.input();
    
    if((lcd_select < RS_COMMAND) || (lcd_select > RS_DATA))
    {
        return(-1);
    }
    character_lcd_rs=lcd_select;
    character_lcd_pulse_e();
    wait(CHARACTER_LCD_STANDARD_DELAY);
#ifndef CHARACTER_LCD_BUS_8BITS
    *lcd_data=character_lcd_data;   /*nybble into 4 bits*/
#endif   
#ifdef CHARACTER_LCD_BUS_8BITS
    *lcd_data=character_lcd_data>>4;   /*nybble on upper 4 bits of 8*/
#endif   
    return(*lcd_data);
    
} /* end of character_lcd_read_nybble() */
#endif

#ifdef CHARACTER_LCD_USE_RW 
int character_lcd_read_byte(uint8_t *lcd_data, uint8_t lcd_select)
{
    int temp;
    char temp1, temp2;
    character_lcd_e=0;
    character_lcd_rw=1;
    character_lcd_data.input();
     
    if((lcd_select < RS_COMMAND) || (lcd_select > RS_DATA))
    {
        return(-1);
    }
    character_lcd_rs=lcd_select;
    character_lcd_pulse_e();
    wait(CHARACTER_LCD_STANDARD_DELAY);

#ifndef CHARACTER_LCD_BUS_8BITS
    temp=character_lcd_read_nybble(*temp1, lcd_select);   /*upper nybble*/
    if(temp < 0) {return(temp); }
    temp=character_lcd_read_nybble(*temp2, lcd_select);   /*lower nybble*/
    if(temp < 0) {return(temp); }
    *lcd_data=(temp1<<4)+temp2;
 #endif   
#ifdef CHARACTER_LCD_BUS_8BITS
    *lcd_data=character_lcd_data;   /*all 8 bits of bus simultaneously*/
#endif
 
    return(*lcd_data);   
} /* end of character_lcd_read_byte() */
#endif 

#endif /* #ifndef CHARACTER_LCD_H */