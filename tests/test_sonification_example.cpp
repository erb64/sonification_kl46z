#include "mbed.h"

// Serial pc(USBTX, USBRX);//PTA2, PTA1 (uart0)

PwmOut speaker(PTD2);

int main()
{
	int lowf = 2500,
		highf = 3000;

	int wait_ms = 100;

	float f1out,
		  wait_s;



	while(true)
	{
		// CAUTION

		for(int i = 0; i < 500; i++)
		{
			f1out = lowf + i; //calculates frequency out (sweeps from 2.5k to 3k Hz)
			speaker.period(1.0/f1out); //calculates period
			speaker.write(0.5); //half duty cycle gives a square wave

		}

		//WARNING

		for(int i = 1; i < 100; i++)
		{
			wait_s = 1.0/i; //determines the alternating frequency. 1-100hz as is.

			speaker.period(1.0/lowf);
			speaker.write(0.5);

			wait(wait_s); //waits in seconds

			speaker.period(1.0/highf);
			speaker.write(0.5);

			wait(wait_s);
		}


		// EMERGENCY
		speaker.period(1.0/highf);

		for(int i = 1; i < 100; i++)
		{
			wait_s = 1.0/i; //determines the alternating frequency. 1-100hz as is.

			speaker.write(0.5);

			wait(wait_s); //waits in seconds

			speaker.write(0);

			wait(wait_s);

		}


	}

}