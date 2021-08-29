/* 
Script by Manuel Schutze - June 2013
Connections:
DS18B20 thermometer - pin 2
Relay module - pin 3
SD CS - pin 10 (optional)
SD MOSI - pin 11 (optional)
SD MISO - pin 12 (optional)
SD CLK - pin 13 (optional)
*/

// Include necessary libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SD.h>
#include <PID_v1.h>

// Setup vars
long intervalTemp = 1000; // interval between temperature measurements / PID computation
int minOn = 1; // minimum time for the relay to be on
int maxOn = 60; // maximum time for the relay to be on, IE, one cicle
long intervalSD = 5000; // interval between saving data on the SD card
double Setpoint = 43; // temperature to be manteined
int relayPin = 3; // pin where the relay is connected
const int chipSelect = 10; // pin CS (SD card) (optional)

// Internal vars (don't change)
long previousMillisTemp = 0;
long previousMillisSD = 0;
unsigned long windowStartTime;
float tempAtual = 0; // current temp
int stat = 0; // 0 = relay off / 1 = relay on
static char tempBuff[15];
File datafile;

// PID parameters (input, output, setpoint, Kp, Ki, Kd, direction)
double Input, Output;
PID myPID(&Input, &Output, &Setpoint,35,30,5, DIRECT);

// Configures thermometer
OneWire oneWire(2); // pin where the themometer is connected
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;

void setup() {
  sensors.begin();
  sensors.getAddress(insideThermometer, 0);
  //sensors.setResolution(insideThermometer, 11); //set thermometer do max resolution
  pinMode(relayPin, OUTPUT);
  pinMode(10, OUTPUT);
  
  // PID
  windowStartTime = ceil(millis()/1000);
  myPID.SetOutputLimits(minOn, maxOn);
  myPID.SetMode(AUTOMATIC);
     
  Serial.begin(9600);
  Serial.println("### Yogurtator ###");
 
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card failed, or not present");
  } else {
    Serial.println("SD card initialized.");
    
    // Create a new file
    char filename[] = "DATA00.TXT";
    for (uint8_t i = 0; i < 100; i++) {
      filename[4] = i/10 + '0';
      filename[5] = i%10 + '0';
      if (! SD.exists(filename)) {
        // only open a new file if it doesn't exist
        datafile = SD.open(filename, FILE_WRITE); 
        break;  // leave the loop!
      }
    }
  
    if (! datafile) {
    Serial.println("Couldnt create file");
    } else {
      Serial.print("Logging to: ");
      Serial.println(filename);
    }
  }
  
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" thermometers.");
  Serial.print("Device 0 Resolution: ");
  Serial.println(sensors.getResolution(insideThermometer), DEC); 
  
  Serial.print("Set temperature: ");
  Serial.println(Setpoint);
  Serial.println("##################");
  
  
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Checks current temp and prints it on serial
  if((currentMillis - previousMillisTemp > intervalTemp)||(currentMillis - previousMillisTemp < 0)) {
    
    // Updates previous millis
    previousMillisTemp = currentMillis;
    
    // Gets temperature
    sensors.requestTemperatures();
    tempAtual = sensors.getTempCByIndex(0);
    
    // Computes PID
    Input = tempAtual;
    myPID.Compute();
      
    // Controls relay
    unsigned long now = ceil(millis()/1000);
    if(now - windowStartTime > maxOn) { // maximumOn reached
      windowStartTime += maxOn;
    }
    if(Output >= now - windowStartTime) { // output defines how much of the time >minOn and <maxOn the relay will be on, the remaining time it will be off.
      digitalWrite(relayPin, HIGH);
      stat = 1;
    } else {
      digitalWrite(relayPin, LOW);
      stat = 0;
    }
    
    // Prints current temperature on serial
    Serial.print("Temp: ");
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print("C | Output: ");
    Serial.print(Output);
    Serial.print(" | Heat: ");
    if(stat == 0) {
      Serial.println("off");
    } else {
      Serial.println("on");
    }
      
  }
  
  // Saves data on the SD card
  if((currentMillis - previousMillisSD > intervalSD)||(currentMillis - previousMillisSD < 0)) {
    
    // Updates previous millis
    previousMillisSD = currentMillis;
    
    // Creates string to save on file
    String dataString = "";
    dtostrf(tempAtual, 5, 2, tempBuff);
    dataString.concat(tempBuff);
    dataString.concat(","); 
    dataString.concat(stat); 
  
    // If the file is available, write to it:
    if (datafile) {
      datafile.println(dataString);
      datafile.flush();
    }  
    
    // If the file isn't open, pop up an error:
    else {
      Serial.println("Error opening data file.");
    } 
  }     
}

/* Code ends here! */
