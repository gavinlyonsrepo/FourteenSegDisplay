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

FourteenSegDisplay::FourteenSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common) {
  _sclk_IO = sclk;
  _data_IO = data;
  _rclk_IO = rclk;
  _common = common;
  pinMode(sclk, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(rclk, OUTPUT);
}

void FourteenSegDisplay::displaySeg(uint16_t value) { 
   if (_common == false) 
   {
     value = (value ^ COMMON_ANODE_MASK); // If common anode flip all bits.
   }
  byte  upper , lower = 0;
  lower = (value) & LOWER_BYTE_MASK;  // select lower byte
  upper = (value >> 8) & LOWER_BYTE_MASK; //select upper 
  digitalWrite(_rclk_IO, LOW);
  shiftOut(_data_IO, _sclk_IO, MSBFIRST, upper);
  shiftOut(_data_IO, _sclk_IO, MSBFIRST, lower);
  digitalWrite(_rclk_IO, HIGH); 
}

void FourteenSegDisplay::displayASCII(uint8_t ascii) {
  displaySeg(pgm_read_word(&FourteenSeg[ascii - ASCII_OFFSET]));
}

void FourteenSegDisplay::displayASCIIwDot(uint8_t ascii) { 
    // add  0x4000 to turn on decimal point/dot in 14 seg
  displaySeg(pgm_read_word((&FourteenSeg[ascii - ASCII_OFFSET])) + DOT_MASK_DEC);
}

void FourteenSegDisplay::displayHex(uint8_t hex) 
{
    uint8_t hexchar = 0;
    if ((hex >= 0) && (hex <= 9))
    {
        displaySeg(pgm_read_word(&FourteenSeg[hex + HEX_OFFSET]));
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
        displaySeg(pgm_read_word(&FourteenSeg[hexchar - ASCII_OFFSET]));
    }
    
}


