/*
  Project Name: FourteenSegDisplay
  File: FourteenSegDisplay_TEST.ino
  Description: test example file for FourteenSegDisplay library
  Author: Gavin Lyons.
  Created June 2019
  URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

//include the library
#include <FourteenSegDisplay.h>

// GPIO I/O pins on the Arduino connected to SER_IN, SCLK, RCLK 74HC595
#define  RCLK595 6 //RCLK
#define  SCLK595 7 //SCLK 
#define  SER595  8 //SERIN

const boolean COMMON = true; //true for common_cathode(default) , false for common anode

// GPIO I/O pins on the Arduino connected to D1 and D2 of a two digit common
// common-cathode 14 segment Display.
#define D1 5 //digit 1
#define D2 4 //digit 2 

#define initdelay 500
#define digitdelay 1

//testdata for single segment function.
#define testdata1 0x0202 // b j -> on :
#define testdata2 0x1708 // d h j k m -> on : Antenna shape
#define testdata3 0x4006 // DP b c -> on : Exclamination point
#define testdata4 0x0000 // all off
#define testdata5 0x7FFF // all on 

//Constructor object 
FourteenSegDisplay  mydisplay(RCLK595, SCLK595,  SER595, COMMON);

void setup()
{
  //Setup pins for digit control , this is for two digit module, add or take away for
  //number of digits used.
  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);
  pinMode(D2, OUTPUT);
  digitalWrite(D2, HIGH);

  // Setup serial for debug
  // Serial.begin(9600);
  // Serial.println("------------- Debug Comms UP ------------");
  delay(initdelay); //optional
}
void loop()
{
  //  **** Display digit one ****

  digitalWrite(D1, HIGH); //turn on digit one

  // test 1 Hex
  mydisplay.displayHex(0x3);

  // test 2 ASCII
  //mydisplay.displayASCII('A');

  //test 3 ASCII with dot
  //mydisplay.displayASCIIwDot('A');

  // test 4 Segments manual
  //mydisplay.displaySeg(testdata1);

  digitalWrite(D1, LOW); //turn off digit one
  delay(digitdelay);

  // ***** Display digit two ****
  digitalWrite(D2, HIGH); //turn on digit two

  // test 1 Hex
  mydisplay.displayHex(0xF);

  // test 2 ASCII
  // mydisplay.displayASCII('B');

  //test 3 ASCII with dot
  //mydisplay.displayASCIIwDot('B');

  // test 4 Segments manual
  //mydisplay.displaySeg(testdata3);

  digitalWrite(D2, LOW); //turn off digit two
  delay(digitdelay);
}
