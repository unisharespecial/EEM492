/*
	HelloCodeProject.cpp, based off of LCD_example from
	http://www.hacktronics.com/Tutorials/arduino-character-lcd-tutorial.html
*/

#include <LiquidCrystal.h>

const int BACK_LIGHT = 13;			// Pin 13 will control the backlight


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
	g_lcd.setCursor(0, 0);			// Set the cursor to the beginning
	g_lcd.print("Hello,");
	g_lcd.setCursor(0, 1);			// Set the cursor to the next row
	g_lcd.print("CodeProject");
}

void loop()
{
}
