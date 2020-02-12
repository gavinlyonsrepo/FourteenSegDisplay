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
//testnumber defines which test to run 
uint8_t testnumber = 6; //1= Hex 2= ASCII, 3 = ASCIIdot,  4 = segment, 5 & 6 = Stings(model 2 only)

//Constructor object 
SevenSegDisplay  mydisplay(RCLK595, SCLK595,  SER595, COMMON_C);

void setup()
{
  // Setup serial for debug optional
  //Serial.begin(9600);
  //Serial.println("------------- Debug Comms UP ------------");.
  mydisplay.displayBegin();
}

void loop()
{
         ModelOneTEST();
}


void ModelOneTEST()
{
    //**** Display String TEST ****
    if( testnumber == 5 )
    {
    mydisplay.displayString("ABC", 0x04); // print ABC "     ABC"
    return;
    }
    if( testnumber == 6 ) //Showing decimal point use
    {
    // print A.BC "      A.BC" where the dot is dot of digit A 
    mydisplay.displayString("A.BC", 0x04); 
    return;
    }

    //  **** Display digit one D1****
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
        mydisplay.displaySeg(0x20, 0x01);  // test 4 Segments manual dash
    break;
    } 
    
    //  **** Display digit two D2 ****  
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
        mydisplay.displaySeg(0x03, 0x02);  // test 4 Segments manual AB ¬
    break;
    } 

    //  **** Display digit three D3 ****  
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
        mydisplay.displaySeg(0x40, 0x04);  // test 4 Segments manual dot
    break;
    } 
}
