/*
  Project Name: FourteenSegDisplay
  File: SevenSegDisplay_BASIC.ino
  Description: basic test setup for single digit cathode to display ASCII = H
  Author: Gavin Lyons.
  Created FEB 2020
  URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

//include the library
#include <SevenSegDisplay.h>

// GPIO I/O pins on the Arduino connected to SER_IN, SCLK, RCLK 74HC595
#define  RCLK595 6 //RCLK
#define  SCLK595 7 //SCLK 
#define  SER595  8 //SERIN
const boolean COMMON_C = true; //true for common_cathode(default) , false for common anode

//Constructor object
SevenSegDisplay  mydisplay(RCLK595, SCLK595,  SER595, COMMON_C);

void setup()
{
  mydisplay.displayBegin(); // Start the  Display
}

void loop()
{
   mydisplay.displayASCII('H', 0x01);   // Display H 
   delay(5000);
}
