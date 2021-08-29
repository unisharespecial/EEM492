/*
Basic Digital Input Control - Using Interrupts Code Part A
 
 This will read the input state from a button press and trigger an LED
 The simulated delay causes unpredictable output.
 
 Author: David M. Auld
 Date: 19th February 2010
 */

int pbIn = 2;          //digital input on pin 2
int ledOut = 4;        // The output LED pin
int state = LOW;       //The input state

void setup()
{                
  // Set up the digital pin 2 to an Input and Pin 4 to an Output
  pinMode(pbIn, INPUT); 
  pinMode(ledOut, OUTPUT);
}

void loop()                     
{
  state = digitalRead(pbIn);      //Read the button

  digitalWrite(ledOut, state);    //write the LED state

  //Simulate a long running process or complex task
  for (int i = 0; i < 100; i++)
  {
     // do nothing but waste some time
     delay(10); 
  }
}
