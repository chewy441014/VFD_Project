#include <pigpio.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>

/*
	This is an example of how to write a single letter to the display, using:
		gpioInitialise	- initialise the gpio library
		gpioSetMode 	- set the pin type as output
		gpioDelay 		- set the delay in micro-seconds
		gpioWrite 		- output a bit to a pin
*/

using namespace std

int main () {
	
	int t = 0;
	uint32_t t_d = 0;
	t = gpioInitialise(); // REQUIRED before using the other gpio library functions
	
	/*
		Pinout is as follows: 
		5		D0
		6		D1
		16		D2
		17		D3
		22		D4
		23		D5
		24 		D6
		25		D7
		26		WR
		27		CS
	*/
	
	gpioSetMode(17,PI_OUTPUT);
	gpioSetMode(27,PI_OUTPUT);
	gpioSetMode(22,PI_OUTPUT);
	gpioSetMode(23,PI_OUTPUT);
	gpioSetMode(24,PI_OUTPUT);
	gpioSetMode(25,PI_OUTPUT);
	gpioSetMode(5,PI_OUTPUT);
	gpioSetMode(6,PI_OUTPUT);
	gpioSetMode(16,PI_OUTPUT);
	gpioSetMode(26,PI_OUTPUT);
	
	// the order for gpioSetMode does NOT matter
	
	if (t < 0) // test if the gpio library initialised successfully
	{
		printf("gpio initialisation failed\n");
		printf("%d\n",t);
	}
	else
	{
		printf("gpio initialisation success\n");
		printf("%d\n",t);
	}
	
	/*
		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		The order of writing to the pins is important. All other pins should be written before WR.
		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	*/
	
	gpioWrite(5,1); // D0 = 1
	gpioWrite(6,0); // D1 = 0
	gpioWrite(16,0); // D2 = 0
	gpioWrite(17,0); // D3 = 0
	gpioWrite(22,0); // D4 = 0
	gpioWrite(23,0); // D5 = 0
	gpioWrite(24,1); // D6 = 1
	gpioWrite(25,0); // D7 = 0
	gpioWrite(27,1); // CS = 1
	gpioWrite(26,1); // WR = 1
	
	t_d = gpioDelay(1); // REQUIRED so that we do not have to monitor the BUSY output from the VFD
	
	gpioWrite(26,0); // WR = 0. Stops the VFD from reading the digital pins any further
	
	t_d = gpioDelay(1); // REQUIRED so that the VFD has time to stop reading from the digital pins
	
	/*
		The below is not strictly required, but it's not a bad idea. Resets all pins back to zero. As such the order does not matter. Also WR has already been written to 0 so is not included in the below. 
	*/
	
	gpioWrite(5,0); // D0 = 0
	gpioWrite(6,0); // D1 = 0
	gpioWrite(16,0); // D2 = 0
	gpioWrite(17,0); // D3 = 0
	gpioWrite(22,0); // D4 = 0
	gpioWrite(23,0); // D5 = 0
	gpioWrite(24,0); // D6 = 0
	gpioWrite(25,0); // D7 = 0
	gpioWrite(27,0); // CS = 0
	
	gpioTerminate(); //do this at the end of a block. 
	
}
