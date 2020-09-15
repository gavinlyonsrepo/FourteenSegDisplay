/*
* Project Name: FourteenSegDisplay
* File: NineSegDisplay.cpp
* Description: Source file for NineSegDisplay sub library
* Author: Gavin Lyons.
* Created: June 2019
* URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

#include "NineSegDisplay.h"
#include "NineSegDisplayFont.h"

NineSegDisplay::NineSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common) 
{
  _sclk_IO = sclk;
  _data_IO = data;
  _rclk_IO = rclk;
  _commonCathode = common;
}

void NineSegDisplay::displayBegin() 
{ 
  pinMode(_sclk_IO, OUTPUT);
  pinMode(_data_IO, OUTPUT);
  pinMode(_rclk_IO, OUTPUT);
}

void NineSegDisplay::displaySeg(uint16_t value, uint8_t digits) 
{ 
   if (_commonCathode == false) 
   {
     value = (value ^ COMMON_ANODE_MASK); // If common anode flip all bits.
     digits = (digits ^ LOWER_BYTE_MASK);
   }
   
   // Combine digit and value D6D5D4D3D2D1DPIHGFEDCBA
   value = ((uint16_t)digits << 10) | value;

  // Spilt into two for transmission to Segments
  byte  upper , lower = 0;
  lower = (value) & LOWER_BYTE_MASK;  // select lower byte
  upper = (value >> 8) & LOWER_BYTE_MASK; //select upper 
  digitalWrite(_rclk_IO, LOW);

  shiftOut(_data_IO, _sclk_IO, MSBFIRST, upper);
  shiftOut(_data_IO, _sclk_IO, MSBFIRST, lower);
  digitalWrite(_rclk_IO, HIGH); 
}

void NineSegDisplay::displayASCII(uint8_t ascii, uint8_t digits) {
  displaySeg(pgm_read_word(&NineSeg[ascii - ASCII_OFFSET]), digits);
}

void NineSegDisplay::displayASCIIwDot(uint8_t ascii, uint8_t digits) { 
    // add  0x200 to turn on decimal point/dot in nine seg
  displaySeg(pgm_read_word((&NineSeg[ascii - ASCII_OFFSET])) + DOT_MASK_DEC, digits);
}

void NineSegDisplay::displayHex(uint8_t hex, uint8_t digits) 
{
    uint8_t hexchar = 0;
    if (hex <= 9)
    {
        displaySeg(pgm_read_word(&NineSeg[hex + HEX_OFFSET]), digits);
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
        displaySeg(pgm_read_word(&NineSeg[hexchar - ASCII_OFFSET]), digits);
    }
    
}

void NineSegDisplay::displayString(const char* str, uint8_t startPos)
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

