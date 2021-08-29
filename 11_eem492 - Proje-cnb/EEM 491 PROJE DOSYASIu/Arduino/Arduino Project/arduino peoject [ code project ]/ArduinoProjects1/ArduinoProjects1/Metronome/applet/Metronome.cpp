/*
 * Metronome
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
const int TEMPO = 120;					// Beats per minute
// Delay in milliseconds = 1 minute    60 seconds   1000 milliseconds
//                         --------- * ---------- * -----------------
//                         (X) beats   minute       second
const int DELAY = (int)((60.0 * 1000.0) / (float)TEMPO);


void setup()							// Run once, when the sketch starts
{
	pinMode(LED_PIN, OUTPUT);			// Sets the digital pin as output
}

void loop()								// Run over and over again
{
	PlayNote(DELAY);
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

