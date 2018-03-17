//#include "studio.h"
#include "stdint.h"
#include "mbed.h"
#include "Freedom_headers.h"

#define USE_CHARACTER_LCD TRUE

/********************************************************************/
#ifdef USE_CHARACTER_LCD
// will change depending on connections

/*
pins defined in char_lcd_4x20.h
rw - PTE18
rs - PTE17
e  - PTE19
--using 4bit mode
db4 - PTE16
db5 - PTE6
db6 - PTE3
db7 - PTE2
*/
#define LCD_REFERENCE_VOLTAGE PTE30
AnalogOut aout(LCD_REFERENCE_VOLTAGE);

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

/********************************************************************/
Serial pc(USBTX, USBRX);
/********************************************************************/

//Snooze functionality
/********************************************************************/
bool snooze_on = false;
const int SNOOZE_DURATION_MIN = 1, //preset by user
          SNOOZE_DURATION_US = SNOOZE_DURATION_MIN * 60000000; //60 million microseconds in each minute

InterruptIn snooze(PTA6); //CHANGE PORT NAME;
Timer t_snooze; 

void setup_t_snooze()
{
    snooze_on = true;
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
const uint16_t BUFFER_ZONES[4][8] = {{0,0,0,0,0,0,0,0},
                                     {0,0,0,0,0,0,0,0}, 
                                     {0,0,0,0,0,0,0,0},
                                     {0,0,0,0,0,0,0,0}};

const uint8_t NORMAL = 1,
              ADVISORY = 2,
              CAUTION = 3,
              WARNING = 4,
              EMERGENCY = 5;
/*
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
*/
// this algorithm can be optimized if we begin the comparison based on the previous zone
// can also be optimized by passing variables by reference
uint8_t determineSeverityZone(uint8_t sensor_index, uint16_t raw_reading, uint8_t previous_zone)
{
    //[Emergency|Warning|Caution|Advisory|Normal|Advisory|Caution|Warning|Emergency]
 
 /*   if (sensor_index == temperature_sensor)
    {
        if(raw_reading < <lowemergencybuffer> || raw_reading > <highemergencybuffer>)
            return EMERGENCY;
        else if (raw_reading < <lowwarningbuffer> || raw_reading > <highwarningbuffer>)
            return WARNING;
        else if (raw_reading < <lowcautionbuffer> || raw_reading > <highcautionbuffer>)
            return CAUTION;
        else if (raw_reading < <lowadvisorybuffer> || raw_reading > <highadvisorybuffer>)
            return ADVISORY;
        else
            return NORMAL;
    }
    */

    if (raw_reading < BUFFER_ZONES[sensor_index][0])
        return NORMAL;
    else if (raw_reading < BUFFER_ZONES[sensor_index][1])
        return previous_zone; // this returns the previous zone. here i'm assuming that 
                              // previous_zone was either of the neighboring zones, but
                              // in future iterations, it might be better to start the 
                              // determination based on what the previous zone was
    else if (raw_reading < BUFFER_ZONES[sensor_index][2])
        return ADVISORY;
    else if (raw_reading < BUFFER_ZONES[sensor_index][3])
        return previous_zone;
    else if (raw_reading < BUFFER_ZONES[sensor_index][4])
        return CAUTION;
    else if (raw_reading < BUFFER_ZONES[sensor_index][5])
        return previous_zone;
    else if (raw_reading < BUFFER_ZONES[sensor_index][6])
        return WARNING;
    else if (raw_reading < BUFFER_ZONES[sensor_index][7])
        return previous_zone;
    else 
        return EMERGENCY;
}
/********************************************************************/

//Volume input
/********************************************************************/
InterruptIn volume(PTB1);

//setup in main
//calls a function to call a function bc pattycake said so

//take code from rotary test

/********************************************************************/

//something about amplifiers -_______-
/********************************************************************/
PwmOut speaker(PTE1); 

Ticker flipper;
float f_alt, //frequency with which tones alternate or turn off and on (warning and emergency)
      f_low,
      f_high;
bool isFlip = true;

const int SENSOR_FREQUENCY_RANGE[NUM_SENSORS][NUM_SENSORS * 2] = {{500,1000}, 
                                                                   {1200,1700},
                                                                   {1850,2250},
                                                                   {2500,3000}};

int f_range = 500;

int temperature_sensor = 0; //replace with index of temperature sensor

void flip(){
    if(isFlip)
    {
        isFlip = !isFlip;
        speaker.period(1/f_low);
        speaker.write(0.5);
    }
    else
    {
        isFlip = !isFlip;
        speaker.period(1/f_high);
        speaker.write(0.5);
    }
}

float determineOutputFrequency(uint8_t highest_severity_index, uint8_t zone, uint16_t raw_reading)
{  
    switch(zone)
    {
        case 1:
            pc.printf("ERROR - NORMAL ZONE SHOULD NOT TRIGGER OUTPUT CALC");
            flipper.detach();
            break;
        case 2:
            pc.printf("ERROR - ADVISORY ZONE SHOULD NOT TRIGGER OUTPUT CALC");
            //trigger display message
            flipper.detach();
            break;
        case 3: //caution
            pc.printf("in caution output calculation");
            flipper.detach();
            //do math to determine f_out
            break;
        case 4: //warning
            pc.printf("in warning output calculation");
            //do math to determine alternating frequency
            //f_alt = ???
            f_low = SENSOR_FREQUENCY_RANGE[highest_severity_index][0];
            f_high = SENSOR_FREQUENCY_RANGE[highest_severity_index][1];
            flipper.attach(&flip, 1/f_alt);

            break;
        case 5:
            pc.printf("in emergency output calculation");
            //do math to determine alternating frequency
            //f_alt = ???
            f_low = -3.4E38; //because you cannot divide by zero
            f_high = SENSOR_FREQUENCY_RANGE[highest_severity_index][1];
            flipper.attach(&flip, 1/f_alt);
            break;
        default:
            pc.printf("something is very wrong with zone");
    }

}



/*
dont forget to write the duty cycle AFTER the period like:
float duty_cycle; //value between 0 and 1


duty_cycle = <based on priority/level>
speaker.period(<determined by algorithm>); //accepts float values in seconds (1.0/frequency)
speaker.write(duty_cycle);
/********************************************************************/



int main()
{
    //for priority algorithm
    bool multiple_in_zone;
    uint8_t count_in_high_zone;
    uint8_t highest_severity_index;
    uint16_t sensor_levels_raw[NUM_SENSORS];
    uint8_t sensor_levels_zone[NUM_SENSORS] = {1, 1, 1, 1}; //all sensors default to normal region

    //for snooze stuff
    int time_snoozed;
    
    pc.baud(115200);
    
    //for lcd
    aout.write(0.5/3.3f);
    character_lcd_initialize(); //initializes the display
    //other peripheral initializations

    //snooze initialization
    snooze.mode(PullDown);//can talk about PullUp mode, i have no preference
    snooze.rise(&setup_t_snooze);//starts a timer on the rising edge

    while(1)
    {
        //pole sensors 
        sensor_levels_raw[0] = sensor1.read_u16(); //may change these s1, s2, to some array
        sensor_levels_raw[1] = sensor2.read_u16(); //reads as a 16 bit normalized unsigned integer (for 0V - 3.3V)
        sensor_levels_raw[2] = sensor3.read_u16();
        sensor_levels_raw[3] = sensor4.read_u16();
        /* mbed documentation for AnalogIn's read_u16() function
        Read the input voltage, represented as an unsigned short in the range [0x0, 0xFFFF]

        Returns
        16-bit unsigned short representing the current input voltage, normalised to a 16-bit value
        */

        // DETERMINE ZONES OF SEVERITY
        for (int sensor_index = 0; sensor_index < NUM_SENSORS; sensor_index++) 
            sensor_levels_zone[sensor_index] = determineSeverityZone(sensor_index, sensor_levels_raw[sensor_index], 
                                                        sensor_levels_zone[sensor_index]);
        
        // GET HIGHEST SEVERITY AND PRIORITY INDEX, check for multiples in highest index, count in highest
        count_in_high_zone = 0;
        highest_severity_index = 0;
        multiple_in_zone = false;

        for (int sensor_index = 1; sensor_index < NUM_SENSORS; sensor_index++)
            if(sensor_levels_zone[sensor_index] > sensor_levels_zone[highest_severity_index])
            {
                count_in_high_zone = 1;
                highest_severity_index = sensor_index;
                multiple_in_zone = false;
            }
            else if(sensor_levels_zone[sensor_index] == sensor_levels_zone[highest_severity_index])
            {
                count_in_high_zone++;
                multiple_in_zone = true;
                // highest_severity_index determined now by priority
                if(SENSOR_PRIORITY[sensor_index] > SENSOR_PRIORITY[highest_severity_index])
                    highest_severity_index = sensor_index; //will save the most severe signal with highest priority only
            }

        //check if snooze is activated
        if(snooze_on)
        {
            //also available: t_snooze.read_ms();
            time_snoozed = t_snooze.read_us(); //reads the timer

            if( time_snoozed > SNOOZE_DURATION_US )
                snooze_on = false; //turns snooze off if set duration has passed
        }
        else
        {
            determineOutputFrequency(highest_severity_index,sensor_levels_zone[highest_severity_index],
                                 sensor_levels_raw[highest_severity_index]);
        }
        

        

        //output sound/display

    }

}
