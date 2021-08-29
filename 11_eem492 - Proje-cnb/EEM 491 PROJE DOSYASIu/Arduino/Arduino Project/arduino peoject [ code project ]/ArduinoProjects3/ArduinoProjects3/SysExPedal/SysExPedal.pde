//#define DEBUG					1

// Constants
const int LED_PIN = 13;				// LED connected to digital pin 13
const int POT_PIN = 0;				// Pot connected to analog pin 0
const int POT_THRESHOLD = 7;		// Threshold amount to guard against false values
const int MIDI_CHANNEL = 1;			// MIDI Channel 2 
const int PATCH_NUMBER = 76;		// Patch 76


#ifdef DEBUG
const int DEBUG_RATE = 9600;		// Serial debugging communicates at 9600 baud
const int SERIAL_PORT_RATE = DEBUG_RATE;
#else
const int MIDI_BAUD_RATE = 31250;	// MIDI communicates at 31250 baud
const int SERIAL_PORT_RATE = MIDI_BAUD_RATE;
#endif


void setup()
{
	pinMode(LED_PIN, OUTPUT);						// Sets the digital pin as output
	digitalWrite(LED_PIN, HIGH);					// Turn the LED on
	Serial.begin(SERIAL_PORT_RATE);					// Starts communication with the MIDI out port

	// Since the SysEx can chnage any patch, send a Program Change message
	// first to set the device to the desired patch.
	MidiProgramChange(MIDI_CHANNEL, PATCH_NUMBER);
}

void loop()
{
	static int s_nLastPotValue = 0;
	static int s_nLastMappedValue = 0;

	int nCurrentPotValue = analogRead(POT_PIN);
	if(abs(nCurrentPotValue - s_nLastPotValue) < POT_THRESHOLD)
		return;
	s_nLastPotValue = nCurrentPotValue;

	//int nMappedValue = map(nCurrentPotValue, 0, 1023, 0, 127);		// Map the value to 0-127
	int nMappedValue = map(nCurrentPotValue, 0, 1002, 0, 127);		// Map the value to 0-127
	if(nMappedValue > 127)
		nMappedValue = 127;
	s_nLastMappedValue = nMappedValue;

	SendSysEx(MIDI_CHANNEL, nMappedValue);
}


/*
void MidiVolume(byte channel, byte volume)
{
	SerialOutput(0xB0 | (channel & 0x0F), BYTE);	//  Control change command
	SerialOutput(0x07, BYTE);						//  Volume command
	SerialOutput(volume & 0x7F, BYTE);				//  Volume 0-127
}
*/


void MidiProgramChange(byte channel, byte patch)
{
	SerialOutput(0xC0 | (channel & 0x0F));			//  Program change command
	SerialOutput(patch & 0x7F);						//  Patch number 0-127
}

void SendSysEx(byte channel, byte volume)
{
#ifdef DEBUG
	Serial.println(volume, DEC);
#else
	SerialOutput(0xF0);         // SysEx start
	SerialOutput(0x00);         // Manufacturer 0
	SerialOutput(0x01);         // Model 1
	SerialOutput(channel);      // MIDI channel
	SerialOutput(0x42);         // Data
	SerialOutput(0x42);         // Data
	SerialOutput(volume);       // Data
	SerialOutput(0x42);         // Data
	SerialOutput(0x42);         // Data
	SerialOutput(0xF7);         // SysEx end
#endif
}

void SerialOutput(byte value)
{
#ifdef DEBUG
	Serial.println(value, HEX);
#else
	Serial.print(value);
#endif
}
