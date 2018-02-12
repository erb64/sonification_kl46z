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

Serial pc (USBTX, USBRX); //tx, rx

int main()
{
	string test_string_1 = "first test string", //17 chars
	       test_string_2 = "the quick brown fox jumps over the lazy dog",
	       test_string_3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
	       test_string_4 = "1234567890",
	       test_string_5 = "~!@#$%^&*()_+=-`[]|}{:';<>\\"
	char choice;

	float wait_seconds = 10.0;

	character_lcd_initialize();

	pc.printf("The first line of the LCD should display: %s\nPress any key to continue", test_string_1);
	character_lcd_puts(&test_string_1);
    pc.scanf("%c", &choice);
	wait(wait_seconds);

	pc.printf("The first line of the LCD should display: %s", test_string_2);
	character_lcd_puts(&test_string_2);
	wait(wait_seconds);

	pc.printf("The first line of the LCD should display: %s", test_string_3);
	character_lcd_puts(&test_string_3);
	wait(wait_seconds);

	pc.printf("The first line of the LCD should display: %s", test_string_4);
	character_lcd_puts(&test_string_4);
	wait(wait_seconds);

	pc.printf("The first line of the LCD should display: %s", test_string_5);
	character_lcd_puts(&test_string_5);
	wait(wait_seconds);


}