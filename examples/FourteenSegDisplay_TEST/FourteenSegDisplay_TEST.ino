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
const boolean MODEL3 = false; //  if True use model 3 (If 2 & 3 false use Model 1)

// Constructor object init an instance of the object.
FourteenSegDisplay  mydisplay(RCLK595, SCLK595,  SER595, COMMON, MODEL2, MODEL3);


// ********* SETTINGS TO CONTROL TESTS ******************* 
//note: Model 1 cannot do strings and Model 3 no dec point function)
uint8_t modeltest = 0; 
uint8_t testnumber = 1; 
#define initdelay 500  //optional
#define digitdelay 1   //optional
unsigned long previousMillis = 0;  // will store last time testnumber was updated
const long interval = 5000;        // interval at which to change testnumber

//testdata for single segment function.
#define testdata1 0x0202 // b j -> on :
#define testdata2 0x1708 // d h j k m -> on : Antenna shape
#define testdata3 0x4006 // DP b c -> on : Exclamation point
#define testdata4 0x0000 // all off
#define testdata5 0x7FFF // all on 

void setup()
{
  // Start the display
  mydisplay.displayBegin();
  
  if ((MODEL2 == false ) && (MODEL3 == false )) modeltest = 1;
  if ((MODEL2 == true ) && (MODEL3 == false )) modeltest = 2;
  if ((MODEL2 == false ) && (MODEL3 == true )) modeltest = 3;
  if ((MODEL2 == true ) && (MODEL3 == true )) while(1); //  User input error. 
  
  if (modeltest == 1) ModelOneGPIOSetup(); 
  
  delay(initdelay);
}

void loop()
{
   unsigned long currentMillis = millis();
   switch (modeltest)
   {
    case  1: ModelOneTEST();  break;
    case  2: ModelTwoTEST();  break;
    case  3: ModelThreeTEST();  break;
   }
    if (currentMillis - previousMillis >= interval) 
	{
	  previousMillis = currentMillis;
	  testnumber ++;
	  if (testnumber == 7) testnumber = 1;
	}
}

//Function to setup GPIO for  Model 1 tests
//Setup pins for digit control , this is for two digit module, add or take away for
//number of digits used. optional, Model 1 ONLY
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


//**** Function to run MODEL ONE tests ****
//Change testnumber at top of test to run test
// TEST 1: HEX = F3
// TEST 2: ASCII = AB
// TEST 3: ASCII with dot = A.B.
// TEST 4: Testdata 1 b j -> on : "
// TEST 5: Testdata 2 d h j k m -> on : Antenna shape
// TEST 6: Testdata 3 DP b c -> on : !

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
    case 5:
      mydisplay.displaySeg(testdata2);  // test 5 Segments manual
      break;
    case 6:
      mydisplay.displaySeg(testdata3);  // test 6 Segments manual
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
      mydisplay.displaySeg(testdata1);  // test 4 Segments manual
      break;
    case 5:
      mydisplay.displaySeg(testdata2);  // test 5 Segments manual
      break;
    case 6:
      mydisplay.displaySeg(testdata3);  // test 6 Segments manual
      break;
  }
  digitalWrite(D2, LOW); //turn off digit two
  delay(digitdelay);

}


// **** Function to run Model 2 tests,  8 digits max *****
// TEST 1: HEX = F3
// TEST 2: ASCII = AB
// TEST 3: ASCIIDot = A.B.
// TEST 4: Testdata 1 b j -> on : "
// TEST 5: String ZX
// TEST 6: String A.B

void ModelTwoTEST()
{
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
    case 5:
      mydisplay.displayString("ZX", 0x02); // print ZX "       ZX"
      return;
      break;
    case 6:
      mydisplay.displayString("A.B", 0x02); // print A.B "     A.B"
      return;
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
      mydisplay.displaySeg(testdata1, 0x02);  // test 4 Segments manual
      break;
  }
}


// **** Function to run MODEL 3 tests, *********
// 2 digits max, do NOT use dec point functions not supported by model3.
//Change testnumber at top of test to run test
// TEST 1: HEX = F3
// TEST 2: ASCII = AB
// TEST 3: ASCII = FE
// TEST 4: Testdata 1 b j -> on : "
// TEST 5: String ZX
// TEST 6: String C

void ModelThreeTEST()
{
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
      mydisplay.displayASCII('E', 0x01); // test 2 ASCII again dec point functions not supported by model3.
      break;
    case 4:
      mydisplay.displaySeg(testdata1, 0x01);  // test 4 Segments manual
      break;
    case 5:
      mydisplay.displayString("ZX", 0x02); // print ZX "ZX"
      return;
      break;
    case 6:
      mydisplay.displayString("C", 0x01); // print C "C"
      return;
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
		mydisplay.displayASCII('F', 0x02); // test 2 ASCII again dec point functions not supported by model3.
      break;
    case 4:
      mydisplay.displaySeg(testdata1, 0x02);  // test 4 Segments manual
      break;
  }
}
