#include "mbed.h"

//Sensor Inputs and buffer ranges
/********************************************************************/
const uint8_t NUM_SENSORS = 4;

/*
AnalogIn sensor1(PTB1);
AnalogIn sensor2(PTB1);
AnalogIn sensor3(PTB1);
AnalogIn sensor4(PTB1);
*/

//buffer ranges, necessary for setting up priority. names of sensors may

//index refers to number of sensor [s1 value, s2 value,....]
//highest priority is 4 -- lowest is 1
const uint8_t SENSOR_PRIORITY[] = {1, 2, 3, 4};

//buffer zones for sensor 1
// initialized as uint16_t because the normalized analog in read_u16 returns 
// a normalized 16bit integer. I did it this way over floats to save space 
// and increase calculation speed
const uint16_t BUFFER_ZONES[4][8] = {{11800,13433,25234,26867,38668,40301,52102,53735},
                                     {11800,13433,25234,26867,38668,40301,52102,53735}, 
                                     {11800,13433,25234,26867,38668,40301,52102,53735},
                                     {11800,13433,25234,26867,38668,40301,52102,53735}};


// this algorithm can be optimized if we begin the comparison based on the previous zone
// can also be optimized by passing variables by reference
uint8_t determineSeverityZone(uint8_t sensor_index, uint16_t raw_reading, uint8_t previous_zone)
{
    if (raw_reading < BUFFER_ZONES[sensor_index][0])
        return 1;
    else if (raw_reading < BUFFER_ZONES[sensor_index][1])
        return previous_zone; // this returns the previous zone. here i'm assuming that 
                              // previous_zone was either of the neighboring zones, but
                              // in future iterations, it might be better to start the 
                              // determination based on what the previous zone was
    else if (raw_reading < BUFFER_ZONES[sensor_index][2])
        return 2;
    else if (raw_reading < BUFFER_ZONES[sensor_index][3])
        return previous_zone;
    else if (raw_reading < BUFFER_ZONES[sensor_index][4])
        return 3;
    else if (raw_reading < BUFFER_ZONES[sensor_index][5])
        return previous_zone;
    else if (raw_reading < BUFFER_ZONES[sensor_index][6])
        return 4;
    else if (raw_reading < BUFFER_ZONES[sensor_index][7])
        return previous_zone;
    else 
        return 5;
}
/********************************************************************/

    bool multiple_in_zone;
    uint8_t count_in_high_zone;
    uint8_t highest_severity_index;
    uint16_t sensor_levels_raw[NUM_SENSORS];
    uint8_t sensor_levels_zone[NUM_SENSORS] = {1, 1, 1, 1}; //all sensors default to normal region

int priorityAlgorithm()
{
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

    return 1;
}

Serial pc(USBTX, USBRX);

int main()
{  
    char key;
    /* FIRST TEST - ENSURE IT PICKS THE RIGHT SENSOR */
    /* FIRST - JUST SENSOR 1 IN CAUTION */
    sensor_levels_raw[0] = 30000;
    sensor_levels_raw[1] = 0;
    sensor_levels_raw[2] = 0;
    sensor_levels_raw[3] = 0;
    
    priorityAlgorithm();
    
    pc.printf("TEST 1 - FIRST SENSOR IN CAUTION RANGE (3), all others normal(1)");
    pc.printf("Actual values:\n\r\tS1 - %i\n\tS2 - %i\n\r\tS3 - %i\n\tS4 %i\n\r", 
              sensor_levels_zone[0],sensor_levels_zone[1],sensor_levels_zone[2],
              sensor_levels_zone[3]);
    if (sensor_levels_zone[0] == 3 && sensor_levels_zone[1] == 1 && 
    	sensor_levels_zone[2] == 1 && sensor_levels_zone[3] == 1)
    {
    	pc.printf("sensors at correct level");
    	    if(multiple_in_zone == false && highest_severity_index == 0)
    	    	pc.printf("TEST 1 PASSED");
    }
   	else
   		pc.printf("TEST 1 FAILED");

    
    /* SECOND TEST - ENSURE IT PICKS THE RIGHT SENSOR */
    /* SECOND - JUST SENSOR 1 IN CAUTION */
    sensor_levels_raw[0] = 0;
    sensor_levels_raw[1] = 45000;
    sensor_levels_raw[2] = 0;
    sensor_levels_raw[3] = 0;
    
    priorityAlgorithm();
    
    pc.printf("TEST 2 - SECOND SENSOR IN WARNING RANGE (4), all others normal(1)");
    pc.printf("Actual values:\n\r\tS1 - %i\n\tS2 - %i\n\r\tS3 - %i\n\tS4 %i\n\r", 
              sensor_levels_zone[0],sensor_levels_zone[1],sensor_levels_zone[2],
              sensor_levels_zone[3]);
    if (sensor_levels_zone[0] == 1 && sensor_levels_zone[1] == 4 && 
    	sensor_levels_zone[2] == 1 && sensor_levels_zone[3] == 1)
    {
    	pc.printf("sensors at correct level");
    	    if(multiple_in_zone == false && highest_severity_index == 1)
    	    	pc.printf("TEST 2 PASSED");
    }
   	else
   		pc.printf("TEST 2 FAILED");


       

    
}//endofmain