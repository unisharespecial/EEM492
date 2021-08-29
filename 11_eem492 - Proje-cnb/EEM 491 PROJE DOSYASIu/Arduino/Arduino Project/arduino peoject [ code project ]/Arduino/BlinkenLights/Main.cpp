#include "WProgram.h"

//The on board test LED is connected to pin number 13
const int ledPin = 13;
const int interval = 1000; //Milliseconds

int main()
{
	//Initialize the Arduino library
	init();

	//Initialize the serial port
	Serial.begin(9600);

	//Configure ledPin as an output
	pinMode(ledPin, OUTPUT);

	//Announce the start of program to whoever
	//is listening on the Serial port
	Serial.println("Ready.");

	while(true)
	{
		digitalWrite(ledPin, HIGH);
		delay(interval/2);
		digitalWrite(ledPin, LOW);
		delay(interval/2);
	}

	//Unreachable code but it's required by
	//the compiler
	return 0;
}
