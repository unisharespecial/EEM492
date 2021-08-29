//#include <ks0108.h>		// library header
#include <GLCD_Library_Beta1_2.h>		// library header

//#include <Arial14.h>	// font definition for 14 point Arial font. 
#include "Arial16.h"
//#include "Arial12.h"
#include "Arial11.h"
//#include "Arial10.h"
#include "Arial9.h"
//#include "Arial8.h"



// Constants
#include "WProgram.h"
void setup();
void loop();
void DisplayStartScreen();
void DisplayCrashScreen();
void EraseScreen();
void InitializeCourse();
void IncrementCourse(bool bIsRunning);
bool DrawRow(int i, int nYPos);
void DrawPlayer();
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int COURSE_WIDTH = 20;
const int DIRECTIONS[5] = {-2, -1, 0, 1, 2};
const int BUTTON_PIN = 2;	// Digital pin 2
const int POT_PIN = 5;		// Analog pin 5


// Globals
int g_course[SCREEN_HEIGHT];
int g_nCircularBuferPosition = 0;
int g_nDirection = 0;
int g_nPlayerPosition = SCREEN_WIDTH / 2;
bool g_bIsRunning = false;
unsigned long int g_ulRaceStart = 0;
int g_nHighScore = 0;


// Function definitions
void DisplayStartScreen();
void DisplayCrashScreen();
void EraseScreen();
void InitializeCourse();
void IncrementCourse(bool bIsRunning);
bool DrawRow(int i, int nYPos);
void DrawPlayer();



void setup()
{
	// Initialise the library, non inverted turns on written pixels
	GLCD.Init(NON_INVERTED);
	Serial.begin(9600);
	DisplayStartScreen();
}

void loop()
{
	if(g_bIsRunning != true)
	{
		int nButtonVal = digitalRead(BUTTON_PIN);		// Read input value from button
		delay(10);										// Wait 10ms
		int nBounceCheck = digitalRead(BUTTON_PIN);		// Check again
		if(nButtonVal == nBounceCheck)					// If val is the same then not a bounce
		{
			if(nButtonVal == LOW)
			{
				//Serial.println("Button was pressed");
				g_bIsRunning = true;
				InitializeCourse();
				EraseScreen();
			}
		}
	}
	
	if(g_bIsRunning == true)
	{
		// Draw the course
		for(int i = g_nCircularBuferPosition; i < SCREEN_HEIGHT; i++)
		{
			int nYPos = (SCREEN_HEIGHT - 1) + (g_nCircularBuferPosition - i);
			if(DrawRow(i, nYPos) != true)
				return;
		}

		for(int i = 0; i < g_nCircularBuferPosition; i++)
		{
			int nYPos = g_nCircularBuferPosition - i - 1;
			if(DrawRow(i, nYPos) != true)
				return;
		}

		IncrementCourse(true);
	}
	
	//delay(100);
	delay(50);
}

void DisplayStartScreen()
{
	GLCD.ClearScreen();
	GLCD.SelectFont(Arial_16);
	GLCD.GotoXY(52, 7);
	GLCD.Puts("Ski!");

	if(g_nHighScore > 0)
	{
		GLCD.SelectFont(Arial_11);
		GLCD.GotoXY(28, 30);
		GLCD.Puts("High score: ");
		GLCD.PrintNumber(g_nHighScore);
	}

	GLCD.SelectFont(Arial_9);
	GLCD.GotoXY(18, 56);
	GLCD.Puts("Push the button to start.");
}

void DisplayCrashScreen()
{
	g_bIsRunning = false;
	
	GLCD.ClearScreen();
	GLCD.SelectFont(Arial_11);
	GLCD.GotoXY(12, 8);
	GLCD.Puts("Whoops! You crashed!");

	unsigned long ulRaceEnd = millis();
	int nScore = (ulRaceEnd - g_ulRaceStart) / 1000;
	if(g_nHighScore < nScore)
		g_nHighScore = nScore;

	GLCD.SelectFont(Arial_11);
	GLCD.GotoXY(28, 30);
	GLCD.Puts("Your score: ");
	GLCD.PrintNumber(nScore);
	delay(4000); // Wait 4 seconds
	DisplayStartScreen();
}

void EraseScreen()
{
	GLCD.ClearScreen();
	for(int i=0; i<SCREEN_HEIGHT; i++)
	{
		/*GLCD.DrawLine(
			0,
			i,
			SCREEN_WIDTH - 1,
			i,
			BLACK);*/
		GLCD.DrawLine(
			0,
			i,
			g_course[SCREEN_HEIGHT - 1 - i],
			i,
			BLACK);
		GLCD.DrawLine(
			g_course[SCREEN_HEIGHT - 1 - i] + COURSE_WIDTH,
			i,
			SCREEN_WIDTH - 1,
			i,
			BLACK);
	}
}

void InitializeCourse()
{
	// Initialize/reset globals that are needed for the race
	g_nCircularBuferPosition = 0;
	g_nDirection = 0;
	g_nPlayerPosition = (SCREEN_WIDTH / 2) - 1;
	//bool g_bIsRunning = false;
	g_ulRaceStart = millis();
	//int g_nHighScore = 0;


	// Initialize the random number generator
	//randomSeed(analogRead(0));
	randomSeed(millis());

	// Initialize the buffer
	// The first half of the initial course is straight
	int i;
	for(i = 0; i < (SCREEN_HEIGHT / 2); i++)
	{
		// Initialize the first half of the screen to be straight (in the middle)
		g_course[i] = (SCREEN_WIDTH - COURSE_WIDTH) / 2;
		g_nCircularBuferPosition++;
	}

	// The first half of the initial course is random
	for(; i < SCREEN_HEIGHT; i++)
	{
		IncrementCourse(false);
	}
}

void IncrementCourse(bool bIsRunning)
{
	// First, update the player
	if(bIsRunning == true)
	{
		int nPotVal = analogRead(POT_PIN);
		int nPlayerDirection = map(nPotVal, 0, 1023, 0, 4);  
		if(nPlayerDirection == 0)
			g_nPlayerPosition -= 2;
		else if(nPlayerDirection == 1)
			g_nPlayerPosition -= 1;
		else if(nPlayerDirection == 2)
			; // facing forward -=> don't do anything
		else if(nPlayerDirection == 3)
			g_nPlayerPosition += 1;
		else if(nPlayerDirection == 4)
			g_nPlayerPosition += 2;
		// Note: If you find your player moving in the opposite directon you are
		// turning the pot (e.g. turning the pot clockwise causes the player to move to
		// the left), you have ground and +V switched on your pot.


		if(g_nPlayerPosition < 0)
			g_nPlayerPosition = 0;

		if(g_nPlayerPosition >= SCREEN_WIDTH)
			g_nPlayerPosition = SCREEN_WIDTH - 1;
	}

	if((g_nCircularBuferPosition % 16) == 0)
	{
		g_nDirection = DIRECTIONS[ random(0, 4) ];
	}

	if(g_nCircularBuferPosition == 0)
		g_course[g_nCircularBuferPosition] = g_course[SCREEN_HEIGHT - 1] + g_nDirection;
	else
		g_course[g_nCircularBuferPosition] = g_course[g_nCircularBuferPosition - 1] + g_nDirection;

	if(g_course[g_nCircularBuferPosition] < 1)
		g_course[g_nCircularBuferPosition] = 1;
	else if((g_course[g_nCircularBuferPosition] + COURSE_WIDTH) > (SCREEN_WIDTH - 1))
		g_course[g_nCircularBuferPosition] = SCREEN_WIDTH - 1 - COURSE_WIDTH;

	g_nCircularBuferPosition++;
	if(g_nCircularBuferPosition >= SCREEN_HEIGHT)
		g_nCircularBuferPosition = 0;
}

bool DrawRow(int i, int nYPos)
{
	int nEdge;
	nEdge = g_course[i] - 3;
	if(nEdge < 0)
		nEdge = 0;
	GLCD.DrawLine(
		nEdge,
		nYPos,
		g_course[i],
		nYPos,
		BLACK);

	if(nYPos == SCREEN_HEIGHT - 2
	|| nYPos == SCREEN_HEIGHT - 1)
	{
		if(g_nPlayerPosition <= g_course[i]
		|| g_nPlayerPosition >= (g_course[i] + COURSE_WIDTH))
		{
			Serial.print("g_nPlayerPosition: ");
			Serial.println(g_nPlayerPosition);
			Serial.print("nYPos: ");
			Serial.println(nYPos);
			Serial.print("i: ");
			Serial.println(i);
			Serial.print("g_course[i]: ");
			Serial.println(g_course[i]);
			DisplayCrashScreen();
			return false;
		}

		GLCD.DrawLine(
			g_course[i] + 1,
			nYPos,
			g_nPlayerPosition - 1,
			nYPos,
			WHITE);
		DrawPlayer();
		GLCD.DrawLine(
			g_nPlayerPosition + 2,
			nYPos,
			g_course[i] + COURSE_WIDTH - 1,
			nYPos,
			WHITE);
	}
	else
	{
		GLCD.DrawLine(
			g_course[i] + 1,
			nYPos,
			g_course[i] + COURSE_WIDTH - 1,
			nYPos,
			WHITE);
	}

	nEdge = g_course[i] + COURSE_WIDTH + 3;
	if(nEdge > SCREEN_WIDTH - 1)
		nEdge = SCREEN_WIDTH - 1;
	GLCD.DrawLine(
		g_course[i] + COURSE_WIDTH,
		nYPos,
		nEdge,
		nYPos,
		BLACK);
	
	return true;
}

void DrawPlayer()
{
	//Serial.println("player was drawn");
	GLCD.DrawLine(
		g_nPlayerPosition,
		SCREEN_HEIGHT - 2,
		g_nPlayerPosition + 1,
		SCREEN_HEIGHT - 2,
		BLACK);
	GLCD.DrawLine(
		g_nPlayerPosition,
		SCREEN_HEIGHT - 1,
		g_nPlayerPosition + 1,
		SCREEN_HEIGHT - 1,
		BLACK);
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

