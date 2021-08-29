/*
 * Metronome2
 *
 * Based on the basic Arduino example, Blink:
 *   http://www.arduino.cc/en/Tutorial/Blink
 * Operates as a visual metronome.
 */
 
// Constants
const int LED_PIN = 13;					// LED connected to digital pin 13
const int POT_PIN = 0;					// Pot connected to analog pin 0
const int POT_THRESHOLD = 7;			// Threshold amount to guard against false values


void setup()							// Run once, when the sketch starts
{
	pinMode(LED_PIN, OUTPUT);			// Sets the digital pin as output
}

void loop()								// Run over and over again
{
	int nCurrentPotValue = analogRead(POT_PIN);
	int nTempo = map(nCurrentPotValue, 0, 1023, 50, 255);		// Map the value to 50-255

	// Delay in milliseconds = 1 minute    60 seconds   1000 milliseconds
	//                         --------- * ---------- * -----------------
	//                         (X) beats   minute       second

	int nDelay = (int)((60.0 * 1000.0) / (float)nTempo);
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
