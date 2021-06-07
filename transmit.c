//From https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/
//https://learn.sparkfun.com/tutorials/mpl3115a2-pressure-sensor-hookup-guide?_ga=2.23559038.573030183.1623087976-1586840990.1623087976
//https://www.e-tinkers.com/2020/01/do-you-know-arduino-sprintf-and-floating-point/

//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <SparkFunMPL3115A2.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
//create additional objects for weather sensors
//TMP36 Sensor: connected to 5V, A0, GND
//Pressure sensor: MPL3115A2
int sensorPin = 0;
MPL3115A2 myPressure;

char pastring[10];
char tmpstring[10];

float pressure;
float temperature;

int ipress;
int itemp;


//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
  Wire.begin(); 
  myPressure.begin(); // Get sensor online

  myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  
  myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags 
}
void loop()
{
 pressure = myPressure.readPressure();
 ipress = pressure;
 sprintf(pareading, "Pressure: %d\n", ipress);
 int reading = analogRead(sensorPin);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 5.0;
 voltage /= 1024.0; 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree with 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 //char tempchar[8]; // Buffer big enough for 7-character float, possibly include temperature label
 //dtostrf(temperatureC, 6, 2, tempchar); // Leave room for too large numbers!
  
  char tmpchar[10];
  dtostrf(temperatureC,4,2,tmpchar);
  sprintf(tmpreading, "Temperature: %s\n", tmpchar);
  //Serial.print(buffer);
  
  //Send message to receiver, change to read data
  //const char temptext[] = "T:";
  //radio.write(&temptext, sizeof(temptext)); 
  radio.write(&tmpreading, sizeof(tmpreading)); //send out temperature
  
  delay(5000);
  
  radio.write(&pareading, sizeof(pareading));
  
  delay(10000);
}

/*
using aadafruit libraries:
https://github.com/adafruit/Adafruit_MPL3115A2_Library/blob/master/examples/testmpl3115a2/testmpl3115a2.ino
float pascals = baro.getPressure();
pascalsmm = pascals/3377;
char pachar[10];
dtostrf(pascalsmm,4,2,pachar);
sprintf(pareading, "Pressure (mmHg): %s\n", pachar); // <-


  float altm = baro.getAltitude();
  char altmchar[10];
  dtostrf(altm,4,2,altmchar);
  sprintf(altmreading, "Altitude (m): %s\n", altmchar);

  float tempC = baro.getTemperature();
  char tempchar[10];
  dtostrf(tempC,4,2,tempchar);
  sprintf(tempreading, "Temperature (C): %s\n", tempchar);

  delay(250);

*/
