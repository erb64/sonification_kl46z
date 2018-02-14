#include "mbed.h"

Serial pc(USBTX, USBRX);

#define MISO PTA17 //defined MISO but not used
#define MOSI PTA16 //chip pin 3
#define SCK PTA15 // chip pin 2
//#define RCLK PTD4 // no latch any 
#define MODE 0 // 0 - rest at zero and lead rising edge. other modes(0,1,2,3)
#define BITS 8 //pits per clock cycle
#define FREQUENCY 100000 // 10 us per clock can go to 1000000

SPI ProgPot (MOSI, MISO, SCK); //refrence from board out, in, clock

DigitalOut CS(PTB9);

void chipwrite(uint8_t value){//value cast to byte unsigned
    CS = 1;
    CS = 0;//bring in new values
    ProgPot.write(0x11);//command bits, telling chip to set pot 00010001b
    ProgPot.write(value);// where to set FFh=255d=11111111b
    CS = 1;//clock in new values

    }

int main(){
    pc.baud(115200);
    
    ProgPot.format(BITS, MODE);
    ProgPot.frequency(FREQUENCY);
    
    //int i = 0;
    //pc.printf("Hello World!\n");

    for(uint8_t level = 255; level > 0; level--){//take down
        chipwrite(level);
        pc.printf("level %i \n", level);
    }
    
    pc.printf("waiting");
    wait(5);
    
    for(uint8_t level = 0; level < 255; level++){//take up
        chipwrite(level);
        pc.printf("level %i \n", level);
    }
    /*while (true) {
        
        wait(0.5f); // wait a small period of time
        pc.printf("%d \n", i); // print the value of variable i
        i++; // increment the variable
        myled = !myled; // toggle a led
    }*/
}
