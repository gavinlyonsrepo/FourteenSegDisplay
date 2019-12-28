/*
* Project Name: SixteenSegDisplay
* File: SixteenSegDisplay.cpp
* Description: Source file for SixteenSegDisplay  library
* Author: Gavin Lyons.
* Created: June 2019
* URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

#include "SixteenSegDisplay.h"
#include "SixteenSegDisplayFont.h"

SixteenSegDisplay::SixteenSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common, bool nodecpoint) 
{
  _sclk_IO = sclk;
  _data_IO = data;
  _rclk_IO = rclk;
  _commonCathode = common;
  _NoDecimalPoint = nodecpoint;
  pinMode(sclk, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(rclk, OUTPUT);
}

void SixteenSegDisplay::displaySeg(uint16_t value, uint8_t digits, bool dotOn) 
{ 
    if (_NoDecimalPoint == false) // Are we using dots (dec point)
     {
          if (dotOn == true) // is dot set on for this digit, apply mask
          {
             digits = (digits + DOT_MASK_DEC);
          } 
     }
  
  if (_commonCathode == false) 
   {
     value = (value ^ COMMON_ANODE_MASK); // If common anode flip all bits.
     digits = (digits ^ LOWER_BYTE_MASK); 
   }
   

  byte  upper , lower = 0;
  lower =  value & LOWER_BYTE_MASK;  // select lower byte
  upper = (value >> 8) & LOWER_BYTE_MASK; //select upper 
  
  digitalWrite(_rclk_IO, LOW);
  shiftOut(_data_IO, _sclk_IO, MSBFIRST, digits); //digit + dot control
  shiftOut(_data_IO, _sclk_IO, MSBFIRST, upper);
  shiftOut(_data_IO, _sclk_IO, MSBFIRST, lower);
  digitalWrite(_rclk_IO, HIGH); 
}

void SixteenSegDisplay::displayASCII(uint8_t ascii, uint8_t digits, bool dotOn) {
  displaySeg(pgm_read_word(&SixteenSeg[ascii - ASCII_OFFSET]), digits, dotOn);
}

void SixteenSegDisplay::displayHex(uint8_t hex, uint8_t digits) 
{
    uint8_t hexchar = 0;
    if ((hex >= 0) && (hex <= 9))
    {
        displaySeg(pgm_read_word(&SixteenSeg[hex + HEX_OFFSET]), digits);
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
        displaySeg(pgm_read_word(&SixteenSeg[hexchar - ASCII_OFFSET]), digits, false);
    }
    
}

void SixteenSegDisplay::displayString(const char* str, uint8_t startPos)
{
   char c;
   while (c = (*str++)) {
        if (*str == '.') {
            displayASCII(c, startPos, true);
            str++;
        }  else {
            displayASCII(c, startPos, false);
        }
          startPos = (startPos>>1); //Bitshifting by one to right /2 to chnage postion of bit set position
   }
}

