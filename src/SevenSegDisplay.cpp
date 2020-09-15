/*
* Project Name: FourteenSegDisplay
* File: SevenSegDisplay.cpp
* Description: Source file for SevenSegDisplay sub library
* Author: Gavin Lyons.
* Created: Nov 2019
* URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

#include "SevenSegDisplay.h"
#include "SevenSegDisplayFont.h"

SevenSegDisplay::SevenSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common, bool transistors) 
{
  _sclk_IO = sclk;
  _data_IO = data;
  _rclk_IO = rclk;
  _commonCathode = common;
  _transistors = transistors;
}

void SevenSegDisplay::displayBegin() 
{ 
  pinMode(_sclk_IO, OUTPUT);
  pinMode(_data_IO, OUTPUT);
  pinMode(_rclk_IO, OUTPUT);
}

void SevenSegDisplay::displaySeg(uint8_t value, uint8_t digits) 
{ 
   if (_commonCathode == false) 
   {
     //common anode
     value = (value ^ FLIP_MASK); // flip all bits on segments
     if (_transistors == true) digits = (digits ^ FLIP_MASK); // if using transistor on digits, flip bits
   }else
   { 
	  //common_cathode
	   if (_transistors == false) digits = (digits ^ FLIP_MASK); // if not using transistor on digits, flip bits
   }
   
   digitalWrite(_rclk_IO, LOW);
   shiftOut(_data_IO, _sclk_IO, MSBFIRST, digits); //digit control
   shiftOut(_data_IO, _sclk_IO, MSBFIRST, value);
   digitalWrite(_rclk_IO, HIGH); 
}

void SevenSegDisplay::displayASCII(uint8_t ascii, uint8_t digits) {
  displaySeg(pgm_read_byte(&SevenSeg[ascii - ASCII_OFFSET]), digits);
}

void SevenSegDisplay::displayASCIIwDot(uint8_t ascii, uint8_t digits) { 
    // add  0x40 to turn on decimal point/dot in 7 seg
  displaySeg(pgm_read_byte((&SevenSeg[ascii - ASCII_OFFSET])) + DOT_MASK_DEC, digits);
}

void SevenSegDisplay::displayHex(uint8_t hex, uint8_t digits) 
{
    uint8_t hexchar = 0;
    if (hex <= 9)
    {
        displaySeg(pgm_read_byte(&SevenSeg[hex + HEX_OFFSET]), digits);
        // 16 is offset in reduced ASCII table for 0 
    }else if ((hex >= 10) && (hex <=15))
    {
        // Calculate offset in reduced ASCII table for ABCDEF
        switch(hex) 
        {
         case 10: hexchar = 'A'; break;
         case 11: hexchar = 'B'; break;
         case 12: hexchar = 'C'; break;
         case 13: hexchar = 'D'; break;
         case 14: hexchar = 'E'; break;
         case 15: hexchar = 'F'; break;
        }
        displaySeg(pgm_read_byte(&SevenSeg[hexchar - ASCII_OFFSET]), digits);
    }
    
}

void SevenSegDisplay::displayString(const char* str, uint8_t startPos)
{
   char c;
   while ((c = (*str++))) {
        if (*str == '.') {
            displayASCIIwDot(c, startPos);
            str++;
        }  else {
            displayASCII(c, startPos);
        }
          startPos = (startPos>>1);//Bitshifting by one to right (/2) to change position of bit set position
   }
}

