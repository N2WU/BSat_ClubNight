# BSat_ClubNight
Club Night Arduino payload reading weather sensors and transmitting via an nRF24L01


_Transmit Side_
The transmitter code takes data from a TMP36 and an MLP3112A adafruit sensor. It packages up the readings and transmits ascii text using the nRF24L01.
It uses standard pinouts listed in the transmit.ino code. Ensure the adafruit library is downloaded correctly.
This version should use a 3V3 device since all sensors are 3v3 compliant like the Arduino Pro Mini.

_Receive Side_
The Receive code (specifically Receive_LCD.ino) receives these ascii strings then displays them on an LCD. It uses an Arduino Uno, LCD keypad shield and a non-standard pinout for
the nRF24L01 using the LCD wiring diagram. Pins **9 and 8** are substituted with pins **3 and 2** in the code.
The code also automatically text wraps based on where the ":" char is. Format your transmit strings correctly.

_Future_
Future versions will add GPS support and a datalogger.
