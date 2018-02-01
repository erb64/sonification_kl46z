#include "studio.h"
#include "stdint.h"
#include "mbed.h"
#include "Freedom_headers.h"

#define USE_CHARACTER_LCD TRUE

/********************************************************************/
#ifdef USE_CHARACTER_LCD
// will change depending on connections

#define CHARACTER_LCD_RS PTE17
#define CHARACTER_LCD_E PTE19
#define CHARACTER_LCD_DB4 PTE16
#define CHARACTER_LCD_DB5 PTE6
#define CHARACTER_LCD_DB6 PTE3
#define CHARACTER_LCD_DB7 PTE2
#define CHARACTER_LCD_ROWS 4
#define CHARACTER_LCD_COLUMNS 20

#include "char_lcd_4x20.h"
/* available functions */
/*
void character_lcd_initialize(void)
int character_lcd_set_data_address(uint8_t lcd_address)
int character_lcd_cursor(uint8_t row, uint8_t column)
int character_lcd_set_CG_address(uint8_t lcd_address)
void character_lcd_pulse_e(void)
int character_lcd_write_nybble(uint8_t lcd_data, uint8_t lcd_select)
int character_lcd_write_byte(uint8_t lcd_data, uint8_t lcd_select)
int character_lcd_putc(char lcd_data)
int character_lcd_puts(char *str)
//int character_lcd_read_nybble(uint8_t *lcd_data, uint8_t lcd_select)
//int character_lcd_read_byte(uint8_t *lcd_data, uint8_t lcd_select)
*/
#endif /* #ifdef USE_CHARACTER_LCD */
/********************************************************************/

//INSERT GLOBAL DEFS HERE, AND OTHER INCLUDES

Boolean snooze_on = FALSE;
const int SNOOZE_DURATION_MIN = 1, //preset by user
		  SNOOZE_DURATION_US = SNOOZE_DURATION_MIN * 60000000; //60 million microseconds in each minute

InterruptIn snooze(PTA6); //CHANGE PORT NAME;
Timer t_snooze(PTA7); //CHANGE PORT NAME;

void setup_t_snooze()
{
	snooze_on = TRUE;
	t_snooze.reset();
	t_snooze.start();
}

int main()
{
	character_lcd_initialize(); //initializes the display
	//other peripheral initializations

	//snooze initialization
	snooze.mode(PullDown);//can talk about PullUp mode, i have no preference
	snooze.rise(&setup);//starts a timer on the rising edge

	while(1)
	{
		//pole sensors

		//check if snooze is activated

		//determine which signal has highest priority

		//calculate signal to output

		//output sound/display

		//check volume



	}

}