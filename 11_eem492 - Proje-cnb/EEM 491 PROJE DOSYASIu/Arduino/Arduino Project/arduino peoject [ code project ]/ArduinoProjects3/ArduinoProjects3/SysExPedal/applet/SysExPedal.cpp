//#define DEBUG					1

// Constants
#include "WProgram.h"
void setup();
void loop();
void MidiProgramChange(byte channel, byte patch);
void SendVolumeSysEx(byte volume);
void SerialOutput(byte value);
void DebugPrintValue(int nValue);
const int LED_PIN = 13;				// LED connected to digital pin 13
const int POT_PIN = 0;				// Pot connected to analog pin 0
const int POT_THRESHOLD = 7;		// Threshold amount to guard agains false values
const int MIDI_CHANNEL = 1;			// MIDI Channel 2 
const int PATCH_NUMBER = 76;		// Patch 76
const int MIN_VOLUME = 29;
const int MAX_VOLUME = 99;

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


	//int nMappedValue = map(nCurrentPotValue, 0, 1023, 0, 127);						// Map the value to 0-127
	int nMappedValue = map(nCurrentPotValue, 0, 1023, MIN_VOLUME - 1, MAX_VOLUME + 1);	// Map the value to 29-100
	if(nMappedValue < MIN_VOLUME)
		nMappedValue = MIN_VOLUME;
	if(nMappedValue > MAX_VOLUME)
		nMappedValue = MAX_VOLUME;
	s_nLastMappedValue = nMappedValue;

	SendVolumeSysEx(nMappedValue);
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

//void SendSysEx(byte channel, byte volume)
void SendVolumeSysEx(byte volume)
{
#if 0
	//SerialOutput(volume);
	Serial.println(volume, DEC);
	return;
#endif
	return;

	// Volume should be between 30 and 99
	if(volume < MIN_VOLUME)
		volume = MIN_VOLUME;
	else if(volume > MAX_VOLUME)
		volume = MAX_VOLUME;
	
	// Calculate LSB and MSB
	byte lsb = volume % 16;
	byte msb = volume / 16;

	// F0 00 01 0x37 02 01 01 00 0x10 aa bb F7
	SerialOutput(0xF0);			// SysEx start
	SerialOutput(0x00);			// Roger Linn Design manufacturer ID byte 1
	SerialOutput(0x01);			// Roger Linn Design manufacturer ID byte 2
	SerialOutput(0x37);			// Roger Linn Design manufacturer ID byte 3
	SerialOutput(0x02);			// AdrenaLinn II product ID
	SerialOutput(0x01);			// File Version
	SerialOutput(0x01);			// Message ID for 'Receive single parameter into preset'
	SerialOutput(0x00);			// Parameter within preset edit buffer
	SerialOutput(0x10);			// Amp Drive parameter
	SerialOutput(lsb);			// LS 4 bits of datum
	SerialOutput(msb);			// MS 4 bits of datum
	SerialOutput(0xF7);			// SysEx end
}

void SerialOutput(byte value)
{
#ifdef DEBUG
	Serial.println(value, HEX);
#else
	Serial.print(value);
#endif
}

#ifdef DEBUG
void DebugPrintValue(int nValue)
{
	char chBuffer[7];	// int has range of -65535...65535
	sprintf(chBuffer, "%d", nValue);
	//Serial.println(chBuffer, HEX);
	Serial.println(nValue, HEX);
}
#endif

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

