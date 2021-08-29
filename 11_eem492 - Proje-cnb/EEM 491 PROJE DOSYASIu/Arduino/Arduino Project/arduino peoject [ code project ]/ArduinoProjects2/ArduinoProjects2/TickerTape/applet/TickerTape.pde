/*
	TickerTape.cpp, based off of LCD_example from
	http://www.hacktronics.com/Tutorials/arduino-character-lcd-tutorial.html
*/

#include <LiquidCrystal.h>

const int BACK_LIGHT = 13;			// Pin 13 will control the backlight
const char* MESSAGE = "Example 2: Hello, CodeProject. ";
const int MESSAGE_LENGTH = 31;
const int DISPLAY_WIDTH = 16;


// Connections:
// RS (LCD pin 4) to Arduino pin 12
// RW (LCD pin 5) to Arduino pin 11
// Enable (LCD pin 6) to Arduino pin 10
// LCD pin 15 to Arduino pin 13
// LCD pins d4, d5, d6, d7 to Arduino pins 5, 4, 3, 2
LiquidCrystal g_lcd(12, 11, 10, 5, 4, 3, 2);


void setup()
{
	pinMode(BACK_LIGHT, OUTPUT);
	digitalWrite(BACK_LIGHT, HIGH);	// Turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
	g_lcd.clear();					// Start with a blank screen
	Serial.begin(9600);
}

void loop()
{
	static int s_nPosition = 0;
	int i;
	if(s_nPosition < (MESSAGE_LENGTH - DISPLAY_WIDTH))
	{
		for(i=0; i<DISPLAY_WIDTH; i++)
		{
			g_lcd.setCursor(i, 0);
			g_lcd.print(MESSAGE[s_nPosition + i]);
		}
	}
	else
	{
		int nChars = MESSAGE_LENGTH - s_nPosition;
		for(i=0; i<nChars; i++)
		{
			g_lcd.setCursor(i, 0);
			g_lcd.print(MESSAGE[s_nPosition + i]);
		}

		for(i=0; i<(DISPLAY_WIDTH - nChars); i++)
		{
			g_lcd.setCursor(nChars + i, 0);
			g_lcd.print(MESSAGE[i]);
		}
	}

	s_nPosition++;
	if(s_nPosition >= MESSAGE_LENGTH)
	{
		s_nPosition = 0;
	}

	delay(500);
}

