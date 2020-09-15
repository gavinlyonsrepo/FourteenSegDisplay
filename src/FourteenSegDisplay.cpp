/*
* Project Name: FourteenSegDisplay
* File: FourteenSegDisplay.cpp
* Description: Source file for FourteenSegDisplay  library
* Author: Gavin Lyons.
* Created: June 2019
* URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

#include "FourteenSegDisplay.h"
#include "FourteenSegDisplayFont.h"

FourteenSegDisplay::FourteenSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common, bool Model2, bool Model3) 
{
  if (Model2 == true && Model3 == true){
	  return;} // User input error
  _sclk_IO = sclk;
  _data_IO = data;
  _rclk_IO = rclk;
  _commonCathode = common;
  _Model2 =  Model2;
  _Model3 = Model3;
}

void FourteenSegDisplay::displayBegin()
{
    pinMode(_sclk_IO, OUTPUT);
    pinMode(_data_IO, OUTPUT);
    pinMode(_rclk_IO, OUTPUT);
} 

void FourteenSegDisplay::displaySeg(uint16_t value, uint8_t digits) 
{ 
   if (_commonCathode == false) 
   {
     value = (value ^ COMMON_ANODE_MASK); // If common anode flip all bits.
     digits = (digits ^ LOWER_BYTE_MASK);
   }
   
  byte  upper , lower = 0;
  lower = (value) & LOWER_BYTE_MASK;  // select lower byte
  upper = (value >> 8) & LOWER_BYTE_MASK; //select upper 
  digitalWrite(_rclk_IO, LOW);
  if (_Model2 == true){ // Use model 2 if true
      shiftOut(_data_IO, _sclk_IO, MSBFIRST, digits); //digit control
  }
  if (_Model3 == true){ // Use model 3 if true
       digits = digits << 6;
       upper = upper | digits;
  }
  shiftOut(_data_IO, _sclk_IO, MSBFIRST, upper);
  shiftOut(_data_IO, _sclk_IO, MSBFIRST, lower);
  digitalWrite(_rclk_IO, HIGH); 
}

void FourteenSegDisplay::displayASCII(uint8_t ascii, uint8_t digits) {
  displaySeg(pgm_read_word(&FourteenSeg[ascii - ASCII_OFFSET]), digits);
}

void FourteenSegDisplay::displayASCIIwDot(uint8_t ascii, uint8_t digits) { 
    // add  0x4000 to turn on decimal point/dot in 14 seg
  displaySeg(pgm_read_word((&FourteenSeg[ascii - ASCII_OFFSET])) + DOT_MASK_DEC, digits);
}

void FourteenSegDisplay::displayHex(uint8_t hex, uint8_t digits) 
{
    uint8_t hexchar = 0;
    if (hex <= 9)
    {
        displaySeg(pgm_read_word(&FourteenSeg[hex + HEX_OFFSET]), digits);
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
        displaySeg(pgm_read_word(&FourteenSeg[hexchar - ASCII_OFFSET]), digits);
    }
    
}

void FourteenSegDisplay::displayString(const char* str, uint8_t startPos)
{
   char c;
   while ((c = (*str++))) {
        if (*str == '.') {
            displayASCIIwDot(c, startPos);
            str++;
        }  else {
            displayASCII(c, startPos);
        }
          startPos = (startPos>>1); //Bitshifting by one to right /2 to change postion of bit set position
   }
}

