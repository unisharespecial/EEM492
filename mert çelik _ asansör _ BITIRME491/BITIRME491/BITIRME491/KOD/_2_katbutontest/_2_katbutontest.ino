//  Blink
 // Turns on an LED on for one second, then off for one second, repeatedly.
 
 // This example code is in the public domain.
 //*/
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int r1 = 8; 
int r2 = 9;
int r3 =10;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(r1, INPUT);
  pinMode(r3, INPUT);
  pinMode(r2, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  
  if(digitalRead(r1) == HIGH || digitalRead(r2) == HIGH || digitalRead(r3) == HIGH){
  digitalWrite(led,HIGH);
  }  // wait for a second
  if(digitalRead(r1) == LOW || digitalRead(r2) == LOW || digitalRead(r3) == LOW){
    digitalWrite(led,LOW);}
}
