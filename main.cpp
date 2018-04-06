//#include "studio.h"
#include <stdio.h>
#include "stdint.h"
#include "mbed.h"
#include "Freedom_headers.h"

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

InterruptIn snooze(PTD3);
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

AnalogIn sensor1(PTB0);
AnalogIn sensor2(PTB0);
AnalogIn sensor3(PTB0);
AnalogIn sensor4(PTB0);

//buffer ranges, necessary for setting up priority. names of sensors may

//index refers to number of sensor [s1 value, s2 value,....]
//highest priority is 4 -- lowest is 1
const uint8_t SENSOR_PRIORITY[] = {4,3,2,1};

//buffer zones for sensor 1
// initialized as uint16_t because the normalized analog in read_u16 returns 
// a normalized 16bit integer. I did it this way over floats to save space 
// and increase calculation speed
// [normal [0]|[1] advisory [2]|[3] caution [4]|[5] warning [6]|[7] emergency ]
const uint16_t BUFFER_ZONES[4][8] = {{11800,13433,25234,26867,38668,40301,52102,53735},
                                     {11800,13433,25234,26867,38668,40301,52102,53735}, 
                                     {11800,13433,25234,26867,38668,40301,52102,53735},
                                     {11800,13433,25234,26867,38668,40301,52102,53735}};

const uint8_t NORMAL = 1,
              ADVISORY = 2,
              CAUTION = 3,
              WARNING = 4,
              EMERGENCY = 5;

char LEVELS[5][10] = {"NORMAL   ", "ADVISORY ", "CAUTION  ", "WARNING  ", "EMERGENCY"};

int temperature_sensor = 0; //replace with index of temperature sensor

// this algorithm can be optimized if we begin the comparison based on the previous zone
// can also be optimized by passing variables by reference
uint8_t determineSeverityZone(uint8_t sensor_index, uint16_t raw_reading, uint8_t previous_zone)
{
    //[Emergency|Warning|Caution|Advisory|Normal|Advisory|Caution|Warning|Emergency]
 
    if (sensor_index == temperature_sensor)
    {
        if(raw_reading < BUFFER_ZONES[temperature_sensor][0] || raw_reading > BUFFER_ZONES[temperature_sensor][7])
            return EMERGENCY;
        else if (raw_reading < BUFFER_ZONES[temperature_sensor][1] || raw_reading > BUFFER_ZONES[temperature_sensor][6])
            return WARNING;
        else if (raw_reading < BUFFER_ZONES[temperature_sensor][2] || raw_reading > BUFFER_ZONES[temperature_sensor][5])
            return CAUTION;
        else if (raw_reading < BUFFER_ZONES[temperature_sensor][3] || raw_reading > BUFFER_ZONES[temperature_sensor][4])
            return ADVISORY;
        else
            return NORMAL;
    }


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
InterruptIn volume1(PTC9);
InterruptIn volume2(PTC8);
InterruptIn reset(PTC7); //needs to be changed

DigitalOut slider_reset(PTD3); //connects to positive terminal of slider reset

void reset_sliders()
{
    slider_reset = 1;

    wait(2);

    slider_reset = 0;
}

//setup in main
//calls a function to call a function bc pattycake said so

//take code from rotary test

/********************************************************************/

//something about amplifiers -_______-
/********************************************************************/
PwmOut speaker(PTD2); 

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

float determineOutputFrequency(uint8_t highest_severity_index, uint8_t zone, 
                               uint16_t raw_reading)
{  
    switch(zone)
    {
        case 1:
            pc.printf("normal zone, shutting off output\n\r");
            speaker.write(0);
            flipper.detach();
            break;
        case 2:
            pc.printf("advisory zone, shutting off output\n\r");
            //trigger display message
            speaker.write(0);
            flipper.detach();
            break;
        case 3: //caution
            pc.printf("in caution output calculation\n\r");
            flipper.detach();
            //do math to determine f_out
            f_low = SENSOR_FREQUENCY_RANGE[highest_severity_index][0] + 
                    (f_range * (raw_reading - BUFFER_ZONES[highest_severity_index][3])
                    / (BUFFER_ZONES[highest_severity_index][4] - 
                    BUFFER_ZONES[highest_severity_index][3])); 
            pc.printf("f_out calculated as: %f for sensor: %i\n\r", f_low, highest_severity_index);
            speaker.period(1.0/f_low); //calculates period
            speaker.write(0.5); //half duty cycle gives a square wave
            break;
        case 4: //warning
            pc.printf("in warning output calculation\n\r");
            //do math to determine alternating frequency
            f_alt = 5 + (30 * (raw_reading - BUFFER_ZONES[highest_severity_index][5])
                    / (BUFFER_ZONES[highest_severity_index][6] - 
                    BUFFER_ZONES[highest_severity_index][5]));
            pc.printf("f_alt calculated as: %f\n\r", f_alt);
            f_low = SENSOR_FREQUENCY_RANGE[highest_severity_index][0];
            pc.printf("f_low calculated as: %f\n\r", f_low);
            f_high = SENSOR_FREQUENCY_RANGE[highest_severity_index][1];
            pc.printf("f_high calculated as: %f\n\r", f_high);
            flipper.attach(&flip, 1/f_alt);

            break;
        case 5:
            pc.printf("in emergency output calculation\n\r");
            //do math to determine alternating frequency
            f_alt = 5 + (30 * (raw_reading - BUFFER_ZONES[highest_severity_index][7])
                    / (65535 - BUFFER_ZONES[highest_severity_index][7]));
            pc.printf("f_alt calculated as: %f\n\r", f_alt);
            f_low = 3.4E-38; //because you cannot divide by zero
            pc.printf("f_low calculated as: %f\n\r", f_low);
            f_high = SENSOR_FREQUENCY_RANGE[highest_severity_index][1];
            pc.printf("f_high calculated as: %f\n\r", f_high);
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
    char stringbuffer[5];
    //for snooze stuff
    int time_snoozed;
    slider_reset = 0;

    //reset and volume stuff
    reset.mode(PullDown);
    reset.rise(&reset_sliders);
    
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
        pc.printf("sensor 0 read as %i\n\r", sensor_levels_raw[0]);
        sensor_levels_raw[1] = sensor2.read_u16(); //reads as a 16 bit normalized unsigned integer (for 0V - 3.3V)
        pc.printf("sensor 1 read as %i\n\r", sensor_levels_raw[1]);
        sensor_levels_raw[2] = sensor3.read_u16();
        pc.printf("sensor 2 read as %i\n\r", sensor_levels_raw[2]);
        sensor_levels_raw[3] = sensor4.read_u16();
        pc.printf("sensor 3 read as %i\n\r", sensor_levels_raw[3]);
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

        character_lcd_cursor(0,0);
        character_lcd_puts("Active Sensor: ");
        sprintf(stringbuffer, "%i", highest_severity_index + 1); //will need to convert this to label
        // character_lcd_putc(highest_severity_index + 1);
        character_lcd_puts(stringbuffer);
        character_lcd_cursor(1,0);
        character_lcd_puts("Severity: ");
        character_lcd_puts(LEVELS[sensor_levels_zone[highest_severity_index] - 1]);
        character_lcd_cursor(2,0);
        character_lcd_puts("Volume: "); //replace 1 with volume variable
        character_lcd_putc('1');
        character_lcd_cursor(3,0);
        character_lcd_puts("ADVISORY: ");
        for(int i = 0; i < NUM_SENSORS; i++)
        {
            if (sensor_levels_zone[i] == 2){
                sprintf(stringbuffer,"%i ", i + 1);
                character_lcd_puts(stringbuffer);
            }
            else
                character_lcd_puts("  ");

        }

    }

}
