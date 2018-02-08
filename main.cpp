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

//Snooze functionality
/********************************************************************/
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
/********************************************************************/

//Sensor Inputs and buffer ranges
/********************************************************************/
AnalogIn sensor0(PTB1);
AnalogIn sensor1(PTB1);
AnalogIn sensor2(PTB1);
AnalogIn sensor3(PTB1);

//buffer ranges, necessary for setting up priority. names of sensors may

//index refers to number of sensor
//highest priority is 4 -- lowest is 1
const short int SENSOR_PRIORITY[] = {1, 2, 3, 4};

//buffer zones for sensor 0
const short int S0LB1 = 0,//value indicates the low end for the first buffer
				S0UB1 = 0,
				S0LB2 = 0,
				S0UB2 = 0,
				S0LB3 = 0, 
				S0UB3 = 0, 
				S0LB4 = 0, 
				S0UB4 = 0; 

//buffer zones for sensor 1
const short int S1LB1 = 0, //value indicates the low end for the first buffer
				S1UB1 = 0, 
				S1LB2 = 0,
				S1UB2 = 0, 
				S1LB3 = 0, 
				S1UB3 = 0, 
				S1LB4 = 0, 
				S1UB4 = 0; 

//buffer zones for sensor 2
const short int S2LB1 = 0, //value indicates the low end for the first buffer
				S2UB1 = 0, 
				S2LB2 = 0,
				S2UB2 = 0, 
				S2LB3 = 0, 
				S2UB3 = 0, 
				S2LB4 = 0, 
				S2UB4 = 0; 

//buffer zones for sensor 3
const short int S3LB1 = 0, //value indicates the low end for the first buffer
				S3UB1 = 0, 
				S3LB2 = 0,
				S3UB2 = 0, 
				S3LB3 = 0, 
				S3UB3 = 0, 
				S3LB4 = 0, 
				S3UB4 = 0; 


/********************************************************************/

//Volume input
/********************************************************************/
InterruptIn volume(PTB1);

//setup in main
//calls a function to call a function bc pattycake said so

/********************************************************************/

//something about amplifiers -_______-
/********************************************************************/
PwmOut speaker(PTE1); 


/*
dont forget to write the duty cycle AFTER the period like:
float duty_cycle; //value between 0 and 1


duty_cycle = <based on priority/level>
speaker.period(<determined by algorithm>); //accepts float values in seconds (1.0/frequency)
speaker.write(duty_cycle);
/********************************************************************/


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
		s1 = sensor1.read(); //may change these s1, s2, to some array
		s2 = sensor2.read(); //reads as a float between 0.0 and 1.0 (for 0V - 3.3V)
		s3 = sensor3.read();
		s4 = sensor4.read();

		//check if snooze is activated
		if(snooze_on)
		{
			//also available: t_snooze.read_ms();
			time_passed = t_snooze.read_us(); //reads the timer

			if( time_passed > SNOOZE_DURATION_US )
				snooze_on = FALSE; //turns snooze off if set duration has passed
		}

		//determine which signal has highest priority

		//calculate signal to output

		//output sound/display


	}

}