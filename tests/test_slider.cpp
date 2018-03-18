#include "mbed.h"

AnalogIn slider(PTB0);
DigitalOut slider_reset(PTD3);
Serial pc(USBTX, USBRX);

int main()
{
	while(1)
	{
		pc.printf("voltage: %f\tas uint16_t: %i\n\r", slider.read()*3.3, slider.read_u16());

		wait(1);
	}
}