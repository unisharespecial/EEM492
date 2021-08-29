/*
 * YYZ
 *
 * Based on the basic Arduino example, Blink: http://www.arduino.cc/en/Tutorial/Blink
 * Plays the opening rhythm to YYZ by Rush.
 */

const int LED_PIN = 13;                 // LED connected to digital pin 13
const int TEMPO = 100;                  // Beats per minute (the original song is played at 104 BPM but that's a little too fast
                                        // to watch so it has been slowed down to 100 BPM)

                                        // Delay in milliseconds = 1 minute    60 seconds   1000 milliseconds
                                        //                         --------- * ---------- * -----------------
                                        //                         (X) beats   minute       second
const int QUARTER_NOTE    = (int)((60.0 * 1000.0) / (float)TEMPO);
const int EIGHTH_NOTE     = QUARTER_NOTE / 2;
const int SIXTEENTH_NOTE  = EIGHTH_NOTE / 2;


void setup()                            // Run once, when the sketch starts
{
    pinMode(LED_PIN, OUTPUT);           // Sets the digital pin as output
}

void loop()                             // Run over and over again
{
    // Rush: YYZ (-.--|-.--|--..)
    PlayNote(EIGHTH_NOTE);
    PlayNote(SIXTEENTH_NOTE);
    PlayNote(EIGHTH_NOTE);
    PlayNote(EIGHTH_NOTE);
    // ----
    PlayNote(EIGHTH_NOTE);
    PlayNote(SIXTEENTH_NOTE);
    PlayNote(EIGHTH_NOTE);
    PlayNote(EIGHTH_NOTE);
    // ----
    PlayNote(EIGHTH_NOTE);
    PlayNote(EIGHTH_NOTE);
    PlayNote(SIXTEENTH_NOTE);
    PlayNote(SIXTEENTH_NOTE);    
}

void PlayNote(int nDuration)
{
    nDuration = (nDuration / 2);
    digitalWrite(LED_PIN, HIGH);        // Set the LED on
    delay(nDuration);                   // Wait for half the (original) duration
    digitalWrite(LED_PIN, LOW);         // Set the LED off
    delay(nDuration);                   // Wait for half the (original) duration
}
