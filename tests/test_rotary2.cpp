#include "mbed.h"

DigitalOut myled(LED_GREEN);
Serial pc(USBTX, USBRX);

InterruptIn press(PTD3);//PT D or C ports allow interrupts else not
InterruptIn CW(PTC8);//cw  pin A
InterruptIn CCW(PTC9);//ccw Pin B

DigitalIn cwcheck(PTC8);//cw       // maybe put volatile in front of these two
DigitalIn ccwcheck(PTC9);//ccw

void buttonpress() 
{
    pc.printf("button press");
}

void CWturn()
{
    while(cwcheck){//while high
        if(ccwcheck){//while high
            pc.printf("CW turn\n");
            break;  
        }  
    }   
    wait(.05); 
}

void CCWturn()
{
    while(ccwcheck){//while high
        if(cwcheck){//while high
            pc.printf("CCW turn\n");
            break;  
        }  
    }   
    wait(.05);
}
    

int main()
{
    press.mode(PullUp);
    press.fall(&buttonpress);
    
    CW.mode(PullDown);
    CW.rise(&CWturn);
    
    CCW.mode(PullDown);
    CCW.rise(&CCWturn);
    
    pc.baud(115200);
    
    int i = 0;
    pc.printf("Hello World!\n");

    while (true) {
        wait(0.5f); // wait a small period of time
        pc.printf("%d \n", i); // print the value of variable i
        i++; // increment the variable
        myled = !myled; // toggle a led
    }
}
