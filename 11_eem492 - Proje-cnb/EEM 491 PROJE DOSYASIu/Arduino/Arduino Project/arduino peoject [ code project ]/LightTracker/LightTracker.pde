/*
  Arduino Light Tracker

  Author: David M. Auld
  Date: 22nd September 2010
  Version: 1.0
  
  This is the simple example of a differential gap controller which tracks light across a
  horizontal plane e.g. follows the Sun East/West.
  
  It uses the following Hardware;
  2 x Photoresistors for East / West Light
  2 x 10kOhm resistors
  1 x 5V servo
  1 x Arduino
 
  Built and tested on Arduino Duemilanove. 
  
  Change Log
  **********
  V1:  22nd September 2010
  ------------------------
  Initial Release
  
*/

#include <Servo.h>

//IO Pins
int pinL = 5;              //Left Sensor IO Pin
int pinR = 4;              //Right Sensor IO Pin
int pinServo = 11;         //Servo PWM pin

int leftValue = 0;         //The left Sensor Value
int rightValue = 0;        //The right Sensor Value
int error =0;              //The Deviation between the 2 sensors
int errorAVG = 0;          //Error Average - Rolling 2 Point

int deadband = 10;         //Range for which to do nothing with output 10 = -10 to +10      

//Servo Stuff
Servo hServo;              //The servo object
int Position = 45;         //Position to write out

int minPos = 5;            //Min Position
int maxPos = 150;          //Max Position

float output = (maxPos - minPos) /2;  //Initial output Position

void setup()
{
Serial.begin(9600); 

hServo.attach(pinServo);

//Set Servo to Centre for Alignment Purpose
Serial.println("Moving Servo to Minimum Position");
hServo.write(minPos);
delay(5000);
Serial.println("Moving Servo to Maximum Position");
hServo.write(maxPos);
delay(5000);
Serial.println("Moving Servo to Mid-Point");
hServo.write(output);
delay(5000);
Serial.println("Going Live................");
}

void loop()
{
  //Input Reading
   leftValue = analogRead(pinL);
   rightValue = analogRead(pinR);

 Serial.print("L = "); Serial.print(leftValue); Serial.print(" | ");
 Serial.print("R = "); Serial.print(rightValue); Serial.print(" | ");
 Serial.print("E = "); Serial.print(error); Serial.print(" | ");
 Serial.print("Eavg = "); Serial.print(errorAVG); 
 Serial.println();

  //Calculate
 error = leftValue - rightValue;
 errorAVG = (errorAVG + error) / 2;
 
 float newOutput = output + getTravel();
 
 if (newOutput > maxPos)
 {
   Serial.println("At Upper Limit");
   newOutput = maxPos;
 }
 else
 { 
   if (newOutput < minPos)
   {
     Serial.println("At Lower Limit");
     newOutput = minPos;
   }
 }
    Serial.println("Writing output");
    
    //Output Writing
    hServo.write(newOutput);
    output = newOutput;

}

int getTravel()
{
  // -1 = Left; +1 = Right
 
 if (errorAVG < (deadband * -1))
 {
   return 1;
 }
 else 
 {
   if (errorAVG > deadband)
   {
     return -1;
   }
   else
   {
     //Do not move within deadband
     return 0;
   }
 }
}
  



