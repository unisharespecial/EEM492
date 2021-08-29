/* 
   Testing Sketch to test construction of temp probes using DS18B20 IC for Stainless Steel probes.
   Sketch was created by Miles Burton and changed to display both C and F temperatures using the serial
   monitor for display.  
   
   created on 11/20/10
   by rik kretzinger   version 1.3
*/

#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 8 on the Arduino
#define ONE_WIRE_BUS 8
 
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
 
  // Start up the library
  sensors.begin();
}
 
 
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  delay(1000);
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  delay(1000);
   
  Serial.print("Temperature for Device 1 is:              ");
  Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus.
                                            // 0 refers to the first IC on the wire.
  Serial.println("  C");
  Serial.print("FAHRENHEIT CONVERSION                     ");
  Serial.print(((sensors.getTempCByIndex(0)*1.8)+32));  // test this line
  Serial.println("  F");
  Serial.println();
}
