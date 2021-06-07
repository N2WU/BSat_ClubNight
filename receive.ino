//from https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/
//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

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
}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text)); //could potentially be an issue where multiple transmissions are picked up
    Serial.println(text);
    delay(250);
  }
  //add some fancy ways to read and display code, or package it up beforehand
  //https://www.hacktronics.com/Tutorials/arduino-character-lcd-tutorial.html
  
}
