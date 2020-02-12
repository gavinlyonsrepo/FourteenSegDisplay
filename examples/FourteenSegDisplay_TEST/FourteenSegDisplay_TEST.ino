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

// Settings for the constuctor
const boolean COMMON = true; //true for common_cathode(default) , false for common anode
//  model 2 , model 3 , outcome
//  false   , false   =  use model 1
//  true    , false   =  use model 2
//  false   , true   =   use model 3
//   true   , true   =   user error, return
const boolean MODEL2 = false; // if True use model 2 (If 2 & 3 false use Model 1)
const boolean MODEL3 = true; //  if True use model 3 (If 2 & 3 false use Model 1)

// Settings to control tests
// testnumber defines which test to run
//1= Hex 2= ASCII, 3 = ASCIIdot,  4 = segment, 5 & 6 = Stings
//note: Model 1 cannot do strings and Model 3 no dec point function)
uint8_t testnumber = 1; 
const boolean MODEL1 = false; // default set to true to run model 1 tests
#define initdelay 500  //optional
#define digitdelay 1   //optional

//testdata for single segment function.
#define testdata1 0x0202 // b j -> on :
#define testdata2 0x1708 // d h j k m -> on : Antenna shape
#define testdata3 0x4006 // DP b c -> on : Exclamination point
#define testdata4 0x0000 // all off
#define testdata5 0x7FFF // all on 

// Constructor object init an instance of the object.
FourteenSegDisplay  mydisplay(RCLK595, SCLK595,  SER595, COMMON, MODEL2, MODEL3);

void setup()
{
  // Start the display
  mydisplay.displayBegin();

  //Setup pins for digit control , this is for two digit module, add or take away for
  //number of digits used. optional, Model 1 ONLY
  if (MODEL1 == true)
  {
    ModelOneGPIOSetup();
  }

  delay(initdelay);
}

void loop()
{
  if (MODEL1 == true) {
    ModelOneTEST();
  } else if (MODEL2 == true) {
    ModelTwoTEST();
  } else if (MODEL3 == true) {
    ModelThreeTEST();
  }
}

//Function to setup GPIO for  Model 1 tests
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


//**** Function to run Model 1 tests ****
//Change testnumber at top of test to run test
void ModelOneTEST()
{
  //  **** Display digit one ****
  digitalWrite(D1, HIGH); //turn on digit one
  switch (testnumber)
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
  switch (testnumber)
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


// **** Function to run Model 2 tests,  8 digits max *****
void ModelTwoTEST()
{
  //**** Display String TEST ****
  if ( testnumber == 5 )
  {
    mydisplay.displayString("AB", 0x02); // print AB "     AB"
    return;
  }
  if ( testnumber == 6 ) //Showing decimal point use
  {
    mydisplay.displayString("A.B", 0x02); // print A.B "     A.B"
    return;
  }

  //  **** Display digit one ****
  switch (testnumber)
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
  switch (testnumber)
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


// **** Function to run Model 3 tests, *********
// 2 digits max, do NOT use dec point functions not supported by model3.
void ModelThreeTEST()
{
  //**** Display String TEST ****
  if ( testnumber == 5 )
  {
    mydisplay.displayString("Z", 0x01); // print ZX "ZX"
    return;
  }

  //  **** Display digit one ****
  switch (testnumber)
  {
    case 1:
      mydisplay.displayHex(0x03, 0x01);   // test 1 Hex
      break;
    case 2:
      mydisplay.displayASCII('B', 0x01); // test 2 ASCII
      break;
    case 3:
      // Not supported in model 3
      break;
    case 4:
      mydisplay.displaySeg(testdata1, 0x01);  // test 4 Segments manual
      break;
  }

  //  **** Display digit two ****
  switch (testnumber)
  {
    case 1:
      mydisplay.displayHex(0xF, 0x02);   // test 1 Hex
      break;
    case 2:
      mydisplay.displayASCII('A', 0x02); // test 2 ASCII
      break;
    case 3:
      // Not supported in model 3
      break;
    case 4:
      mydisplay.displaySeg(testdata1, 0x02);  // test 4 Segments manual
      break;
  }
}
