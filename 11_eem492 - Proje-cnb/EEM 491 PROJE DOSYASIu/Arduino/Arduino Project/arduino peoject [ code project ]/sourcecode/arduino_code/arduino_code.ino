const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
int prevsensorValue = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  if (prevsensorValue != sensorValue) {
    
    // print the results to the serial monitor:
    Serial.print("A");
    Serial.print(sensorValue);
    Serial.print("B");
    
    prevsensorValue = sensorValue;
  }
  // wait 100 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(100);                     
}