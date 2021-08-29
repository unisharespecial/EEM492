/*
 * Metronome2
 *
 * Based on the basic Arduino example, Blink:
 *   http://www.arduino.cc/en/Tutorial/Blink
 * Operates as a visual metronome.
 */
 
// Constants
#include "WProgram.h"
void setup();
void loop();
void PlayNote(int nDuration);
const int LED_PIN = 13;					// LED connected to digital pin 13
const int POT_PIN = 0;					// Pot connected to analog pin 0
const int POT_THRESHOLD = 3;			// Threshold amount to guard against false values


void setup()							// Run once, when the sketch starts
{
	pinMode(LED_PIN, OUTPUT);			// Sets the LED as output
	pinMode(POT_PIN, INPUT);			// Sets the potentiometer as input
}

void loop()								// Run over and over again
{
	static int s_nLastPotValue = 0;
	static int s_nTempo = 0;

	int nCurrentPotValue = analogRead(POT_PIN);						// Has a range of 0 - 1023
	if(abs(nCurrentPotValue - s_nLastPotValue) >= POT_THRESHOLD)
	{
		s_nLastPotValue = nCurrentPotValue;
		int nTempo = map(nCurrentPotValue, 0, 1023, 50, 255);		// Map the value to 50-255
		if(nTempo != s_nTempo)
		{
			s_nTempo = nTempo;
		}
	}

	// Delay in milliseconds = 1 minute    60 seconds   1000 milliseconds
	//                         --------- * ---------- * -----------------
	//                         (X) beats   minute       second
	int nDelay = (int)((60.0 * 1000.0) / (float)s_nTempo);
	PlayNote(nDelay);
}

void PlayNote(int nDuration)
{
	nDuration = (nDuration / 2);
	digitalWrite(LED_PIN, HIGH);		// Set the LED on
	delay(nDuration);					// Wait for half the (original) duration
	digitalWrite(LED_PIN, LOW);			// Set the LED off
	delay(nDuration);					// Wait for half the (original) duration
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

