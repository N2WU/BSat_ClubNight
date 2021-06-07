//from https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/
//Requires multiple SPIs
//http://www.learningaboutelectronics.com/Articles/Multiple-SPI-devices-to-an-arduino-microcontroller.php
/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 Use logic converter with nRF24 since you are using arduino Uno
 */
//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  while (!Serial);
    Serial.begin(9600);
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Initializing");
}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text)); //could potentially be an issue where multiple transmissions are picked up
    Serial.println(text);
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(text);
    delay(250);
  }
  //add some fancy ways to read and display code, or package it up beforehand
  //https://www.hacktronics.com/Tutorials/arduino-character-lcd-tutorial.html
  //SLOCK, MOSI, MISO all have same wiring. Should work for multiple. Look into CS/SS/CSN
  
}
