/*
  Project Name: FourteenSegDisplay
  File: SixteenSegDisplay_TEST.ino
  Description: test example file for SixteenSegDisplay library
  In this case a 2 digit setup.
  Author: Gavin Lyons.
  URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

//include the library
#include <SixteenSegDisplay.h>

// GPIO I/O pins on the Arduino connected to SER_IN, SCLK, RCLK 74HC595
#define  RCLK595 6 //RCLK
#define  SCLK595 7 //SCLK 
#define  SER595  8 //SERIN

// common = true = Common Cathode(default)
// common = false = Common Anode
// NoDecimalPoint = false = use the decimal point , 7 digits max
// NoDecimalPoint = true = do not use decimal point , 8 digits max
const boolean COMMON = true; 
const boolean NODECPOT = true; 

//testnumber defines which test to run 
uint8_t testnumber = 1; //1= Hex 2= ASCII, 3 = ASCIIdot,  4 = segment, 5 & 6 = Stings
  
#define initdelay 500  //optional


//Constructor object 
SixteenSegDisplay  mydisplay(RCLK595, SCLK595,  SER595, COMMON, NODECPOT);

void setup()
{
  // Setup serial for debug optional
  Serial.begin(9600);
  Serial.println("------------- Debug Comms UP ------------");
  delay(initdelay);
}

void loop()
{
  myTEST();
}


void myTEST()
{
    //**** Display String TEST ****
    if( testnumber == 5 )
    {
    mydisplay.displayString("AB", 0x02); // print AB "     AB"
    return;
    }
    if( testnumber == 6 ) //Showing decimal point use
    {
    mydisplay.displayString("A.B", 0x02); // print A.B "     A.B"
    return;
    }

    //  **** Display digit one ****
    switch(testnumber)
    {
    case 1:
        mydisplay.displayHex(0x3, 0x01);   // test 1 Hex
    break;
    case 2:
        mydisplay.displayASCII('B', 0x01,false); // test 2 ASCII
    break;
    case 3:
       mydisplay.displayASCII('B', 0x01, true);  //test 3 ASCII with dot
    break;
    case 4:
        mydisplay.displaySeg(0x4000, 0x01, false);  // test 4 Segments manual, t seg
    break;
    } 
    
    //  **** Display digit two ****  
    switch(testnumber)
    {
    case 1:
        mydisplay.displayHex(0xF, 0x02);   // test 1 Hex
    break;
    case 2:
        mydisplay.displayASCII('A', 0x02, false); // test 2 ASCII
    break;
    case 3:
        mydisplay.displayASCII('A', 0x02, true);  //test 3 ASCII with dot
    break;
    case 4:
        mydisplay.displaySeg(0x8800, 0x02,false);  // test 4 Segments manual, u-p segs two center segs
    break;
    } 
}
