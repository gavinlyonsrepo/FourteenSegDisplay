/*
  Project Name: FourteenSegDisplay
  File: SevenSegDisplay_TEST.ino
  Description: test example file for SevenSegDisplay sub library
  In this case a 3 digit common anode setup.
  Author: Gavin Lyons.
  Created June 2019
  URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

//include the library
#include <SevenSegDisplay.h>

// GPIO I/O pins on the Arduino connected to SER_IN, SCLK, RCLK 74HC595
#define  RCLK595 6 //RCLK
#define  SCLK595 7 //SCLK 
#define  SER595  8 //SERIN

const boolean COMMON_C = false; //true for common_cathode(default) , false for common anode
const boolean TRANSISTORS = true; //true for using transistors on  digits, false for not

// Constructor object 
SevenSegDisplay  mydisplay(RCLK595, SCLK595,  SER595, COMMON_C, TRANSISTORS );


//  ********* VARIABLES TO RUN THE TESTS *******************
uint8_t testnumber = 1; 
unsigned long previousMillis = 0;  // will store last time testnumber was updated
const long interval = 5000;        // interval at which to change testnumber
char workStr[6];
uint8_t voltage = 0;
// TESTS
// 1= Hex 2= ASCII, 3 = ASCIIdot,  4 = segment, 5 & 6 = Stings, 7 integer , 8 float
// TEST1 = HEX = display = FF3
// TEST2 = ASCII = display = ABC
// TEST3 = ASCIIdot = display =  A.B.C.
// TEST4 = segment = display =  -¬' ( g , ab , f) segments
// TEST5 = String = display =  ABC
// TEST6 = String with dot = display =  A.BC
// TEST7 = Integer = display = 013
// TEST8 = Float =  display = 2.51


//  ********* SETUP **********
void setup()
{
  // Setup serial for debug optional
  Serial.begin(9600);
  Serial.println("------------- Debug Comms UP ------------");
  
  mydisplay.displayBegin();
}


//  ********* MAIN LOOP **********
void loop()
{
         unsigned long currentMillis = millis();
         ModelOneTEST();
        if (currentMillis - previousMillis >= interval) 
        {
          previousMillis = currentMillis;
          testnumber ++;
          if (testnumber == 9) testnumber = 1;
        }
}


//  ********* FUNCTIONS  **********


void ModelOneTEST()
{
    //********** Test 5 - 8 Strings integers and floats All digits in one pass**********
    switch(testnumber)
    {
    case 5:
        mydisplay.displayString("ABC", 0x04); // test 5 string  print ABC "     ABC"
    break;
    case 6: 
         mydisplay.displayString("A.BC", 0x04); // test 6 string print A.BC "      A.BC" where the dot is dot of digit A
    break;
    case 7:
          voltage = 13;
          sprintf(workStr, "%03u", voltage); // test 7 integer "013" with leading zero
          mydisplay.displayString(workStr, 0x04);
    break;
    case 8:     
        voltage = 251;
        sprintf(workStr, "%u.%u%u", (voltage / 100) % 10, (voltage / 10) % 10,  voltage % 10);
        mydisplay.displayString(workStr, 0x04);  // test 8 float "2.51" 
    break;
    }
    
    //  **** Display digit one D1 test 1-4****
    switch(testnumber)
   { 
    case 1:
        mydisplay.displayHex(0x3, 0x01);   // test 1 Hex
    break;
    case 2:
        mydisplay.displayASCII('C', 0x01); // test 2 ASCII
    break;
    case 3:
        mydisplay.displayASCIIwDot('C', 0x01);  //test 3 ASCII with dot
    break;
    case 4:
        mydisplay.displaySeg(0x20, 0x01);  // test 4 Segments manual dash , 0x20 = 0010-0000 turns on f segment
    break;
    default:
      return;
    break;
    } 
    
    //  **** Display digit two D2  test 1-4 ****  
    switch(testnumber)
    {
    case 1:
        mydisplay.displayHex(0xF, 0x02);   // test 1 Hex
    break;
    case 2:
        mydisplay.displayASCII('B', 0x02); // test 2 ASCII
    break;
    case 3:
        mydisplay.displayASCIIwDot('B', 0x02);  //test 3 ASCII with dot
    break;
    case 4:
        mydisplay.displaySeg(0x03, 0x02);  // test 4 Segments manual  ¬ , 0x03 = 0000-0011 turns on a & b segment
    break;
    default:
      return;
    break;
    } 

    //  **** Display digit three D3  test 1-4 ****  
    switch(testnumber)
    {
    case 1:
        mydisplay.displayHex(0xF, 0x04);   // test 1 Hex
    break;
    case 2:
        mydisplay.displayASCII('A', 0x04); // test 2 ASCII
    break;
    case 3:
        mydisplay.displayASCIIwDot('A', 0x04);  //test 3 ASCII with dot
    break;
    case 4:
        mydisplay.displaySeg(0x40, 0x04);  // test 4 Segments manual dot, 0x40 = 0100-0000 turns on g segment
    break;
    default:
      return;
    break;
    } 
}


