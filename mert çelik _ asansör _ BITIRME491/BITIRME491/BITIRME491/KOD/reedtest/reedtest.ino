//  Blink
 // Turns on an LED on for one second, then off for one second, repeatedly.
 
 // This example code is in the public domain.
 //*/
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int reed = 2; 
int k;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(reed, INPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  k = digitalRead(reed);
  if(k == HIGH){
  digitalWrite(led,HIGH);
  }  // wait for a second
  if(k == LOW){
    digitalWrite(led,LOW);}
}
