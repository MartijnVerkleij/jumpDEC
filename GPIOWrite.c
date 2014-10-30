#include <wiringPi.h>
#include <stdio.h>

int i = 0;
int j = 0;

void mom() {
	
	digitalWrite(6,(j & (1<<i))>>i);
	--i;
	puts("bla");
}

int main(int argc, char **argv) {
	puts("bla");
	wiringPiSetup();
	pinMode(6,OUTPUT);
	//pinMode(7,OUTPUT);
	pinMode(7,GPIO_CLOCK);
	gpioClockSet(7,500);
	i = 8*sizeof(int);
	j = -24456;
	wiringPiISR(7, INT_EDGE_RISING, &mom);
	while (i != 0) {}
	digitalWrite(6,0);
}

