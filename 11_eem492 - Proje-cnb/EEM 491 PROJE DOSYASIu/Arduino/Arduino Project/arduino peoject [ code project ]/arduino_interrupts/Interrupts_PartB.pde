/*
Basic Digital Input Control - Using Interrupts Code Part B
 
 This will read the input state from a button press and trigger an LED
 Now we will use an interrupt to trigger the LED, regardless of
 where the simulated delay is upto.
 
 Author: David M. Auld
 Date: 19th February 2010
 */

int pbIn = 0;                   //Interrupt 0 is on DIGITAL PIN 2!
int ledOut = 4;                //The output LED pin
volatile int state = LOW;        //The input state toggle

void setup()
{                
  // Set up the digital pin 2 to an Interrupt and Pin 4 to an Output
  pinMode(ledOut, OUTPUT);

  //Attach the interrupt to the input pin and monitor for ANY Change 
  attachInterrupt(pbIn, stateChange, CHANGE);
}

void loop()                     
{
  //Simulate a long running process or complex task
  for (int i = 0; i < 100; i++)
  {
    // do nothing but waste some time
    delay(10); 
  }
}

void stateChange()
{
  state = !state;
  digitalWrite(ledOut, state);  
}


