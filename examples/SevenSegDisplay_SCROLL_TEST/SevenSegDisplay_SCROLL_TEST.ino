/*
  Project Name: FourteenSegDisplay
  File: SevenSegDisplay_SCROLL_TEST.ino
  Description: test example file for SevenSegDisplay sub library of FourteenSegDisplay
  In this case a 4 digit common cathode setup. SMA420564

  1. TEST 1 Scroll data (uses the String object)
  2. TEST 2 Scroll data using character array
  
  Author: Gavin Lyons.
  Created Jan 2020
  URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

//include the library
#include <SevenSegDisplay.h>

// GPIO I/O pins on the Arduino connected to SER_IN, SCLK, RCLK 74HC595
#define  RCLK595 6 //RCLK pin 12 74HC595
#define  SCLK595 7 //SCLK pin 11  74HC595
#define  SER595  8 //SERIN pin 14 74HC595

const boolean COMMON_C = true; //true for common_cathode(default) , false for common anode
const boolean TRANSISTORS = true; //true for using transistors on  digits, false for not

// Constructor object 
SevenSegDisplay  mydisplay(RCLK595, SCLK595,  SER595, COMMON_C, TRANSISTORS );


// TEST CONTROL VARS 
unsigned long previousMillis_display = 0;        // will store last time ADC was updated
const long interval_display = 1000;      // interval at which to read ADCs (milliseconds)
String textScroll = " Hello World ";
char textScrollTwo[11] = " Hiplanet ";
uint8_t testnumber = 1; // Set to 1 for test 1 , 2 for test two 

void setup()
{
  delay(1000);
  mydisplay.displayBegin();
}

void loop()
{
  switch (testnumber)
  {
    case 1: ScrollTest(); break;      // 1. TEST 1 Scroll data (uses the String object)
    case 2: ScrollTestTwo(); break;   // 2. TEST 2 Scroll data using character array
  } 
} 

 //   1. TEST 1 Scroll data (uses the String object)
void ScrollTest()
{
  char charbuf[6];
  textScroll.toCharArray(charbuf, 5);
  mydisplay.displayString(charbuf, 0x08);
  unsigned long currentMillis = millis();
  // Read the  Pots and update string every interval_display delay
  if (currentMillis - previousMillis_display >= interval_display)
  {
    previousMillis_display = currentMillis;
    if (textScroll.length() > 0)
    {
      textScroll.remove(0, 1);
    }else
    {
      textScroll = " Hello World ";
    }
  }
}

//  2. TEST 2 Scroll data using character array
void ScrollTestTwo()
{
  while(1)
  {
  mydisplay.displayString(textScrollTwo, 0x08);
    unsigned long currentMillis = millis();
  // Read the  Pots and update string every interval_display delay
  if (currentMillis - previousMillis_display >= interval_display)
  {
    previousMillis_display = currentMillis;
    if (strlen(textScrollTwo) > 0)
    {
      memmove(textScrollTwo, textScrollTwo+1, strlen(textScrollTwo));
    }else
    {
      return;
    }
   }
  }
}
