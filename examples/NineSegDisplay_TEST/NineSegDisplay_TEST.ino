/*
  Project Name: FourteenSegDisplay
  File: NineSegDisplay_TEST.ino
  Description: test example file for NineSegDisplay library
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
uint8_t testnumber = 1; //1= Hex 2= ASCII, 3 = ASCIIdot,  4 = segment, 5 & 6 = Stings
//testdata for single segment function. 10 bits (DP)ihgfedcba
#define testdata1 0x111 // a e i-> on 
#define testdata2 0x000 // all off
#define testdata3 0x3FF // all on 

void setup()
{
	mydisplay.displayBegin();
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
	mydisplay.displayString("AB", 0x02); // print AB "   AB" starting in position 2, 0x02, b000010
	return;
	}
	if( testnumber == 6 ) //Showing decimal point use
	{
	// print A.BCDEF. "A.B" where the dots are the decimal point of digit. 
	mydisplay.displayString("A.B", 0x02); 
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
