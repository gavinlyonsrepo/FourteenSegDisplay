/*
  Project Name: FourteenSegDisplay
  File: FourteenSegDisplay_TEST.ino
  Description: test example file for FourteenSegDisplay library
  In this case a 2 digit setup.
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
const boolean MODEL2 = false; //false use Model1(default) , True use model 2
//testnumber defines which test to run 
uint8_t testnumber = 1; //1= Hex 2= ASCII, 3 = ASCIIdot,  4 = segment, 5 & 6 = Stings(model 2 only)
  
#define initdelay 500  //optional
#define digitdelay 1   //optional

//testdata for single segment function.
#define testdata1 0x0202 // b j -> on :
#define testdata2 0x1708 // d h j k m -> on : Antenna shape
#define testdata3 0x4006 // DP b c -> on : Exclamination point
#define testdata4 0x0000 // all off
#define testdata5 0x7FFF // all on 

//Constructor object 
FourteenSegDisplay  mydisplay(RCLK595, SCLK595,  SER595, COMMON, MODEL2);

void setup()
{
  // Setup serial for debug optional
  Serial.begin(9600);
  Serial.println("------------- Debug Comms UP ------------");
  
  //Setup pins for digit control , this is for two digit module, add or take away for
  //number of digits used. optional Model 1 ONLY
  if (MODEL2 == false)
  {
    ModelOneGPIOSetup();
  }

  delay(initdelay);
}

void loop()
{
  if (MODEL2 == false)
   {
         ModelOneTEST();
   }else
   {
         ModelTwoTEST();
   }
}

void  ModelOneGPIOSetup()
{
   // GPIO I/O pins on the Arduino connected to D1 and D2 of a two digit common
   // common-cathode 14 segment Display. OPTIONAL Model 1 only  D2:D1
  #define D1 4 //digit 1 RIGHT
  #define D2 5 //digit 2 LEFT
  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);
  pinMode(D2, OUTPUT);
  digitalWrite(D2, HIGH);
}

//Change testnumber at top of test to run test
void ModelOneTEST()
{
    //  **** Display digit one ****
    digitalWrite(D1, HIGH); //turn on digit one
    switch(testnumber)
    {
    case 1:
        mydisplay.displayHex(0x3);   // test 1 Hex
    break;
    case 2:
        mydisplay.displayASCII('B'); // test 2 ASCII
    break;
    case 3:
        mydisplay.displayASCIIwDot('B');  //test 3 ASCII with dot
    break;
    case 4:
        mydisplay.displaySeg(testdata1);  // test 4 Segments manual
    break;
    } 
    digitalWrite(D1, LOW); //turn off digit one
    delay(digitdelay);
     
     //  **** Display digit two ****      
    digitalWrite(D2, HIGH); //turn on digit two
    switch(testnumber)
    {
    case 1:
        mydisplay.displayHex(0xF);   // test 1 Hex
    break;
    case 2:
        mydisplay.displayASCII('A'); // test 2 ASCII
    break;
    case 3:
        mydisplay.displayASCIIwDot('A');  //test 3 ASCII with dot
    break;
    case 4:
        mydisplay.displaySeg(testdata3);  // test 4 Segments manual
    break;
    } 
    digitalWrite(D2, LOW); //turn off digit two
    delay(digitdelay);

}

void ModelTwoTEST()
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
        mydisplay.displayASCII('B', 0x01); // test 2 ASCII
    break;
    case 3:
        mydisplay.displayASCIIwDot('B', 0x01);  //test 3 ASCII with dot
    break;
    case 4:
        mydisplay.displaySeg(testdata1, 0x01);  // test 4 Segments manual
    break;
    } 
    
    //  **** Display digit two ****  
    switch(testnumber)
    {
    case 1:
        mydisplay.displayHex(0xF, 0x02);   // test 1 Hex
    break;
    case 2:
        mydisplay.displayASCII('A', 0x02); // test 2 ASCII
    break;
    case 3:
        mydisplay.displayASCIIwDot('A', 0x02);  //test 3 ASCII with dot
    break;
    case 4:
        mydisplay.displaySeg(testdata3, 0x02);  // test 4 Segments manual
    break;
    } 
}
