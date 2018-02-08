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
const uint8_t NUM_SENSORS = 4;

AnalogIn sensor1(PTB1);
AnalogIn sensor2(PTB1);
AnalogIn sensor3(PTB1);
AnalogIn sensor4(PTB1);

//buffer ranges, necessary for setting up priority. names of sensors may

//index refers to number of sensor [s1 value, s2 value,....]
//highest priority is 4 -- lowest is 1
const uint8_t SENSOR_PRIORITY[] = {1, 2, 3, 4};

//buffer zones for sensor 1
// initialized as uint16_t because the normalized analog in read_u16 returns 
// a normalized 16bit integer. I did it this way over floats to save space 
// and increase calculation speed
const uint16_t S1LB1 = 0, //value indicates the low end for the first buffer
			   S1UB1 = 0, 
			   S1LB2 = 0,
		       S1UB2 = 0, 
			   S1LB3 = 0, 
			   S1UB3 = 0, 
			   S1LB4 = 0, 
			   S1UB4 = 0; 

//buffer zones for sensor 2
const uint16_t S2LB1 = 0, //value indicates the low end for the first buffer
				S2UB1 = 0, 
				S2LB2 = 0,
				S2UB2 = 0, 
				S2LB3 = 0, 
				S2UB3 = 0, 
				S2LB4 = 0, 
				S2UB4 = 0; 

//buffer zones for sensor 3
const uint16_t S3LB1 = 0, //value indicates the low end for the first buffer
				S3UB1 = 0, 
				S3LB2 = 0,
				S3UB2 = 0, 
				S3LB3 = 0, 
				S3UB3 = 0, 
				S3LB4 = 0, 
				S3UB4 = 0; 

//buffer zones for sensor 4
const uint16_t S4LB1 = 0,//value indicates the low end for the first buffer
				S4UB1 = 0,
				S4LB2 = 0,
				S4UB2 = 0,
				S4LB3 = 0, 
				S4UB3 = 0, 
				S4LB4 = 0, 
				S4UB4 = 0; 


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

	uint8_t highest_priority_index;
	uint16_t sensor_levels_raw[NUM_SENSORS];
	uint8_t sensor_levels_zone[NUM_SENSORS] = {1, 1, 1, 1}; //all sensors default to normal region

	character_lcd_initialize(); //initializes the display
	//other peripheral initializations

	//snooze initialization
	snooze.mode(PullDown);//can talk about PullUp mode, i have no preference
	snooze.rise(&setup);//starts a timer on the rising edge

	while(1)
	{
		//pole sensors 
		sensor_levels[0] = sensor1.read_u16(); //may change these s1, s2, to some array
		sensor_levels[1] = sensor2.read_u16(); //reads as a 16 bit normalized unsigned integer (for 0V - 3.3V)
		sensor_levels[2] = sensor3.read_u16();
		sensor_levels[3] = sensor4.read_u16();
		/* mbed documentation for AnalogIn's read_u16() function
		Read the input voltage, represented as an unsigned short in the range [0x0, 0xFFFF]

		Returns
		16-bit unsigned short representing the current input voltage, normalised to a 16-bit value
		*/

		//DETERMINE ZONES OF SEVERITY

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