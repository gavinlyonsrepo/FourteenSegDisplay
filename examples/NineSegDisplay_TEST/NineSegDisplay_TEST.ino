/*
  Project Name: FourteenSegDisplay
  File: NineSegDisplay_TEST.ino
  Description: test example file for NineSegDisplay library
  In this case a 2 digit setup.
  Author: Gavin Lyons.
  Created Jan 2020
  URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

//include the library
#include <NineSegDisplay.h>

// GPIO I/O pins on the Arduino connected to SER_IN, SCLK, RCLK 74HC595
#define  RCLK595 6 //RCLK
#define  SCLK595 7 //SCLK 
#define  SER595  8 //SERIN

const boolean COMMON = true; //true for common_cathode(default) , false for common anode
//Constructor object 
NineSegDisplay  mydisplay(RCLK595, SCLK595,  SER595, COMMON);
 
//testnumber defines which test to run 
//test data vars for this file.
int8_t testnumber = 1; //1= Hex 2= ASCII, 3 = ASCIIdot,  4 = segment, 5 & 6 = Stings
//testdata for single segment function. 10 bits (DP)ihgfedcba
#define testdata1 0x111 // a e i-> on 
#define testdata2 0x000 // all off
#define testdata3 0x3FF // all on 

void setup()
{
  // Setup serial for debug optional
  /*
  Serial.begin(9600);
  Serial.println("------------- Debug Comms UP ------------");
  delay(initdelay);
  */
}

void loop()
{
         ModelTEST();
}


void ModelTEST()
{
    //**** Display String TEST ****
    if( testnumber == 5 )
    {
    mydisplay.displayString("ABC", 0x04); // print ABC "   ABC" starting in position 3, 0x04, b000100
    return;
    }
    if( testnumber == 6 ) //Showing decimal point use
    {
    // print A.BCDEF. "A.BCDEF." where the dots are the decimal point of digit. 
    // in position 6 0x20 or  b100000
    mydisplay.displayString("A.BCDEF.", 0x20); 
    return;
    }

    //  **** Display digit one ****
    switch(testnumber)
    {
    case 1:
        mydisplay.displayHex(0x3, 0x01);   // test 1 Hex, pos 1 b000001
    break;
    case 2:
        mydisplay.displayASCII('B', 0x01); // test 2 ASCII, pos 1 b000001
    break;
    case 3:
        mydisplay.displayASCIIwDot('B', 0x01);  //test 3 ASCII with dot, pos 1 b000001
    break;
    case 4:
        mydisplay.displaySeg(testdata3, 0x01);  // test 4 Segments manual, pos 1 b000001
    break;
    } 
    
    //  **** Display digit two ****  
    switch(testnumber)
    {
    case 1:
        mydisplay.displayHex(0xF, 0x02);   // test 1 Hex , pos 2 b000010
    break;
    case 2:
        mydisplay.displayASCII('A', 0x02); // test 2 ASCII, pos 2 b000010
    break;
    case 3:
        mydisplay.displayASCIIwDot('A', 0x02);  //test 3 ASCII with dot, pos 2  b000010
    break;
    case 4:
        mydisplay.displaySeg(testdata2, 0x02);  // test 4 Segments manual ,pos 2 b000010
    break;
    } 
}
