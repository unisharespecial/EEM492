/*
  Arduino Simon Game

  Author: David M. Auld
  Date: 19th October 2009
  Version: 2.0
  
  This is the simple game of Simon built on the Arduino Platform.
  
  It uses the following Hardware;
  4 x LEDs for Visual Feedback of step
  4 x Pushbuttons for Input of step
  1 x Speaker for Audio Feedback of Step
  1 x LCD for Game Info and Scoring.
  1 x Arduino
  +various Resistors/pots etc.
 
  Built and tested on Arduino Duemilanove. 
  
  Change Log
  **********
  V2: 19th October 2009
  ---------------------
  NEW: Added progressive game mode, V1 was random only
  NEW: Correct sequence playback on Game Over
  NEW: Sound On/Off Mode
  FIX: Removed surplus variables, and code tidy
  IMP: Random Seed Generator now reads and adds all analog inputs to generate seed value
  
  V1: 17th October 2009
  ---------------------
  Initial Release
  
*/

#include <LiquidCrystal.h>

//initialise the library with the numbers of the interface pins
LiquidCrystal lcd(13,12,11,10,9,8);

int userInput = 0;      //Analog pin for user input from buttons
int led1 = 2;           //LED 1
int led2 = 3;           //LED 2
int led3 = 4;           //LED 3
int led4 = 5;           //LED 4
int speaker = 6;        //Speaker

//Game Stats
boolean started = false;    //Has the game started yet
boolean gameover = false;   //Has the game ended
int level = 0;              //What level is the user on (Score at end = level -1)

int gameMode = 0;           //Which game mode is being used
                            // 1 = Progressive
                            // 2 = Random
                            
boolean soundEnabled = true;  //Is the sound enabled or not
                            
int lastLevelSeq[50];        //The sequence for the steps used in progressive mode previous level
                             //Also used by game over to replay correct sequence back
                             //Nobody can get passed 50, surely!

//Setup Routine
void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(speaker, OUTPUT);
  
  //Set up the LCD Col and Row count
  lcd.begin(16,2);
  delay(100);
  lcd.clear();
  lcd.print("Welcome to");
  lcd.setCursor(0,1);
  lcd.print("Arduino SIMON");
  delay(3000);
  for (int i = 0; i < 14; i++)
    {
    lcd.scrollDisplayLeft();
    delay(300);
    }
  lcd.clear();
  lcd.print("initialising...");
  for (int i = 1; i<7; i++)
  {
    if (i<5)
    {
      lightLed(i);    //Light each LED
    }
      playTone(i);    //Play each tone used
      lightLed(0);    //Clear the LED's
  }
}
  
  void loop()
  {
  lcd.clear();
  lcd.print("To Start");
  lcd.setCursor(0,1);
  lcd.print("PRESS ANY BUTTON");
    while (started == false)
    {
      if (getButtonPressed() > 0)
      {
        playTone(5);
        started=true;
      }
    }
    
    //Clear the previous game Last Level Steps
    for (int s=0; s < 50; s++)
    {
      lastLevelSeq[s] = 0;
    }
    
     delay(500);
     
     // Select Game Mode Here
     lcd.clear();
     lcd.print("Select Game Mode");
     
     while (gameMode == 0)
    {
     lcd.setCursor(0,1);
     lcd.print("1=P 2=R 4=TGLSND");
     
      switch (getButtonPressed())
      {
      case 1:
        if (soundEnabled)
        {
          playTone(5);
        }
        gameMode = 1;
        lcd.clear();
        lcd.print("Progressive");
        lcd.setCursor(0,1);
        lcd.print("Mode Selected");
        break;
       
      case 2:
        if (soundEnabled)
        {
          playTone(5);
        }
        
        gameMode = 2;
        lcd.clear();
        lcd.print("Random");
        lcd.setCursor(0,1);
        lcd.print("Mode Selected");
        break;
      
      case 4:
        soundEnabled = (!soundEnabled);
        lcd.setCursor(0,1);
        
        if (soundEnabled)
        {
          lcd.print("Sound Mode: ON  "); 
          playTone(5);          
        }
        else
        {
         lcd.print("Sound Mode: OFF "); 
        }
        delay(1000);
        break;  
      }
    }    
    
    delay(1000);
    
     //Set start level
     level =1;
     
    while (gameover == false)
    {
      if (doLevel(level)==true)
        {
          //Level Correct, increment Level and repeat
          lcd.clear();
          lcd.print("LEVEL: "); lcd.print(level);
          lcd.setCursor(0,1);
          lcd.print("Completed......"); 
          
          if (soundEnabled)
          {
            //play level correct sound
            for (int i =0; i < 3; i++)
            {
              playTone(5);
              delay(50);
            }
          }
          else
          {
            delay(125);
          }
          delay(1000);    //Delay so user can see level completed message
          level++;        //Set next level
        } 
       else
      {
       //Level Wrong, set game over
       gameover = true;
      }  
    }
    
    if (gameover == true)
    {
      lcd.clear();
      lcd.print("WRONG! GAME OVER");
      lcd.setCursor(0,1);
      lcd.print("SCORE: "); lcd.print(level-1);
      
      if (soundEnabled)
      {
        for (int i = 0; i < 5; i++)
        {
          playTone(6);
          delay(50);
        }
      }
      else
      {
        delay(125);
      }
    }
        
      //Playback the correct sequence
      lcd.clear();
      lcd.print("Sequence");
      lcd.setCursor(0,1);
      lcd.print("should have been");
      delay(500);
      for(int s=0; s < level; s++)
      {
        playStep(lastLevelSeq[s]);
        //lightLed(lastLevelSeq[s]);
        //playTone(lastLevelSeq[s]);
        //lightLed(0);
        //delay(250);
      }
      
      lcd.clear();
      lcd.print("Your Score: "); lcd.print(level-1);
      lcd.setCursor(0,1);
      lcd.print("PRESS ANY BUTTON");
      
      //Wait for user
      while (gameover == true)
      {
       if (getButtonPressed() > 0)
        {
        level = 0;
        
        if (soundEnabled)
        {
          playTone(5);
        }
        gameover = false;
        started = false;
        gameMode = 0;
        }        
      }     
    }
  
   /*
  Read the analog input and determine which button is pressed
  */  
  int getButtonPressed()
  {
    int userValue = 0;      // What is the pushbutton resistor matrix value
    userValue = analogRead(userInput);
    
    int buttonPressed = 0;
      
    if (userValue > 850)
    {
      buttonPressed = 0;      //No Button Pressed
    }
    if (userValue < 850)
    { 
      buttonPressed = 4;      // Maybe Button 4 still to check others
    }
    if (userValue < 800)
    {
      buttonPressed = 3;      // Maybe Button 3 still to check others
    }
    if (userValue < 700)
    {
      buttonPressed = 2;      // Maybe Button 2 still to check last one
    }
    if (userValue < 600)
    {
      buttonPressed = 1;      // Done Checking buttons
    }
    return buttonPressed;  
  }
  
  /*
  This will light the led, play the tone, switch off the led 
  */
  void playStep(int number)
  {
    lightLed(number);
    if (soundEnabled)
    {
      playTone(number);
    }
    else
    {
      delay(100);
    }
    delay(250);
    lightLed(0);
  }
  
  
  /*
  Light the Relevant LED
  param led = which LED to light
  */
  void lightLed(int led)
  {
    switch (led)
    {
    case 0:
      digitalWrite(led1,LOW);          //Set all the LEDs off
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      delay(50);                      //Give time for the LED to go
      break;
    case 1:
      digitalWrite(led1,HIGH);        //LED 1 on
      break;
    case 2:
      digitalWrite(led2,HIGH);        //LED 2 on
      break;
    case 3:
      digitalWrite(led3,HIGH);        //LED 3 on
      break;
    case 4:
      digitalWrite(led4,HIGH);        //LED 4 on
      break;
    }
  }
 
  /*
  Play the tones for the game
  param tone = which tone to play
  tone 1 to 4 are the button tones
  tone 5 is level correct tone / start tone (any button pressed)
  tone 6 is level wrong and game over tone
  */
  void playTone(int tone)
  {
      int tones[6] = { 1000, 1250, 1500, 1750, 500, 3000}; 
      for (long i = 0; i < 125; i++)
      {
        //generate a square wave
        digitalWrite(speaker, HIGH);
        delayMicroseconds(tones[tone-1]);
        digitalWrite(speaker, LOW);
        delayMicroseconds(tones[tone-1]);
      }
  }

/* 
This is the actual game level.
Return TRUE if success or FALSE if fail
*/
boolean doLevel(int level)
{
  int steps[level];                //Which steps the user must match
  int userStep = 0;                //Which button has the user pressed
  int userLength =0;               //How many steps has the user entered
  boolean levelPass = false;       //Level was won or lost  
  boolean inProgress = true;       //Level currently running
    
  //Display a message to the user that the Arduino is doing its bit
  lcd.clear();
  lcd.print("Arduino Turn");
  lcd.setCursor(0,1);
  lcd.print("Pay Attention");
  delay(1000);                    //Add a delay
  
  //Seed the random number generator
  randomSeed(analogRead(0) + analogRead(1) + analogRead(2)+ analogRead(3)+analogRead(4)+analogRead(5));
  
  //The steps to be played are dependent on gameMode
  //Setup the steps based on which mode we are playing
  
  if (gameMode == 1)
  {
     //Progressive 
     //Get last level
     for (int s=0; s < level; s++)
     {
       if (level > 1)
       {
         // Can only copy if higher than level 1
         steps[s] = lastLevelSeq[s];
       }
       //Add new step
       steps[level-1] = (int)random(1,5);
     }
  }
  if (gameMode == 2)
  {
     //Random
    for (int s=0; s < level; s++)
    {
      steps[s] = (int)random(1,5);
    }
  }
  
     //Copy back to last level for next time and gameOver
     for (int s=0; s < level; s++)
     {
       lastLevelSeq[s] = steps[s];
     }
  
  //Play the steps
  for (int s=0; s < level; s++)
  {
    playStep(steps[s]);
    //lightLed(steps[s]);        //Light the led for the step from the sequence
    //playTone(steps[s]);        //Play the step tone from the sequence
    //lightLed(0);               //Turn off the LEDs
  }
  
  //Display user turn message
  lcd.clear();
  lcd.print("LEVEL: "); lcd.print(level);
  lcd.setCursor(0,1);
  lcd.print("Your Turn.....");
  
  while (inProgress)
  {
    //Get the user input  
   userStep = getButtonPressed();
   if (userStep >0)
   {
     userLength++;
     playStep(userStep);
     
     //lightLed(userStep);
     //playTone(userStep);
     //lightLed(0);
   
     //Check the user input against the sequence
     if (steps[userLength-1] == userStep)
     {
       //Correct button pressed, check if sequence still to complete
       if (userLength ==level)
       {
         //finished the sequence
         inProgress = false;
         levelPass = true;
       }
     }
     else
     {
       //wrong button pressed
       inProgress = false;
       levelPass = false;
     }
    }
  }
  return levelPass;
}


