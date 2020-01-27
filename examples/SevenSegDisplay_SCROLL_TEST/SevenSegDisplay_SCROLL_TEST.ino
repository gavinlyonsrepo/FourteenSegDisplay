/*
  Project Name: FourteenSegDisplay
  File: SevenSegDisplay_SCROLL_TEST.ino
  Description: test example file for SevenSegDisplay sub library of FourteenSegDisplay
  In this case a 4 digit common cathode setup. SMA420564
  
  1. TEST 1 display Integer
  2. TEST 2 display FLoat
  3. TEST 3 Scroll data
  
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
// DEVELOPER NOTE: pinout Connectors on custom development board: VCC, SERIN-14 , SCLK-11 , RCLK-12 , GND
const boolean COMMON_C = true; //true for common_cathode(default) , false for common anode
//Constructor object
SevenSegDisplay  mydisplay(RCLK595, SCLK595,  SER595, COMMON_C);




//Control Vars &  defines.
#define POT0 A0
uint16_t sensorValue0 = 0;
unsigned long previousMillis_display = 0;        // will store last time ADC was updated
const long interval_display = 1000;      // interval at which to read ADCs (milliseconds)
String textScroll = "Hello ";
uint8_t testnumber = 1; // testnumber defines which test to run 1= integer 2 =float  3 =scroll

void setup()
{
  //Setup serial for debug optional
  Serial.begin(9600);
#define initdelay 500  //optional
  Serial.println("------------- Debug Comms UP ------------");
}

void loop()
{
  ADC_Read();
  switch (testnumber)
  {
    case 1: IntTest(); break; // TEST 1 Display a decimal interger
    case 2: FloatTest(); break; // TEST 2 Display a float number
    case 3: ScrollTest(); break; // TEST 3 SCROLL TEXT
  }
}

void IntTest()
{
  // TEST 1 integer
  char workStr[5];
  sprintf(workStr, "%04d", sensorValue0); // "0234" with leaidng zeros
  mydisplay.displayString(workStr, 1 << 3);
}


void FloatTest()
{
  // TEST 2 float
  char workStr[6];
  uint8_t  digit1, digit2, digit3 , digit4;
  uint16_t voltage;

  // To avoid using float we convert the ADC to a number representing  voltage ~ 1023ADC -> 500 = 5.00 volts
  //  5/1024 = .00488, .0048 * 10000 = 49,
  //  2.5 volt ~ 500ADC , so (500*49)/100 = 250,  parse 250 to make look like 02.50
  voltage = ((sensorValue0 * 49) / 100);
  digit1 = (voltage / 1000) % 10;
  digit2 = (voltage / 100) % 10;
  digit3 = (voltage / 10) % 10;
  digit4 =  voltage % 10;

  sprintf(workStr, "%d%d.%d%d", digit1, digit2, digit3, digit4);
  mydisplay.displayString(workStr, 1 << 3);
}


void ScrollTest()
{
  // TEST 3 scroll text
  char charbuf[6];
  textScroll.toCharArray(charbuf, 5);
  mydisplay.displayString(charbuf, 1 << 3);
}

void ADC_Read()
{
  unsigned long currentMillis = millis();
  // Read the  Pots and update string every interval_display delay
  if (currentMillis - previousMillis_display >= interval_display)
  {
    previousMillis_display = currentMillis;
    sensorValue0 = analogRead(POT0); // read the input on analog pin 0
    // Send ADC data to serial port DEBUG
    // Serial.print("POT0 : ");
    // Serial.println(sensorValue0);
    if (textScroll.length() > 0)
    {
      textScroll.remove(0, 1);
    }else
    {
      textScroll = textScroll + " ADC0 = " + sensorValue0 + " ";
    }
  }
}
