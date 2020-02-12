/*
  Project Name: FourteenSegDisplay
  File: FourteenSegDisplay_ADC.ino
  Description: Test example file number two for FourteenSegDisplay library
  In this case a practical example for 2 digit setup fourteen segment. 
  converts ADC form 1023-0 to 99-1 and 
  displays on digits. Model 2 only.
  Author: Gavin Lyons.
  Created Nov 2019
  URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

//include the library
#include <FourteenSegDisplay.h>

// GPIO I/O pins on the Arduino connected to SER_IN, SCLK, RCLK 74HC595
#define  RCLK595 6 //RCLK
#define  SCLK595 7 //SCLK 
#define  SER595  8 //SERIN
//Constructor object 
FourteenSegDisplay  mydisplay(RCLK595, SCLK595,  SER595, COMMON_C, MODEL2);

// Test control vars
const boolean COMMON_C = true; //true for common_cathode(default) , false for common anode
const boolean MODEL2 = true; //false use Model1(default) , True use model 2
const boolean Method1 = true; //true for method 1 , false use method 2

//Vars to read ADC on interval to provide data to display
unsigned long previousMillis = 0;        // will store last time ADC was updated
const long interval = 1000;           // interval at which to read ADC (milliseconds)
uint8_t  ADC_PIN = 14;    // select the input pin for the potentiometer A0
uint16_t ADC_Value = 0;  // variable to store the value coming from the ADC

void setup()
{
  mydisplay.displayBegin();
}

void loop()
{
	
unsigned long currentMillis = millis();

if (currentMillis - previousMillis >= interval) 
    {
         previousMillis = currentMillis;
         ADC_Value = analogRead(ADC_PIN);
         ADC_Value = map(ADC_Value, 0, 1023, 1, 99);
     }

ModelTwoADC();
}

//Function ModelTwoADC to display 0-99 from ADC on to two digits
//Two methods:
//Method 1  : parses number and displays as ASCII D2D1
//Method 2  : converts number to a character array and displays as string
//boolean  method 1 defines which is run 

void ModelTwoADC()
{

    if ( Method1 == true) //Method 1  
    {
    mydisplay.displayHex((ADC_Value /10)%10, 0x02);   // D2        
    mydisplay.displayHex((ADC_Value /1)%10, 0x01);   // D1
     }else     // Method 2  
     {
    char str1[2];
    sprintf(str1, "%u%u", ( ADC_Value /10)%10, (ADC_Value /1)%10);
    mydisplay.displayString(str1, 0x02);
    }
}

//******************EOF*************
