#include <Firefly.h>

const int MAX_COLOR_VALUE = 400;
const int NUM_FIREFLIES = 2;

Firefly f[NUM_FIREFLIES] = {Firefly(9,10,11),Firefly(3,5,6)};

void setup()
{
    // nothing
}

void loop()
{
	// randomly pick a firefly to light up
	int firefly_idx = random(0,NUM_FIREFLIES);
	
	// blink!
	f[firefly_idx].firefly_blink();
	
	delay(random(1000,7000));
}


