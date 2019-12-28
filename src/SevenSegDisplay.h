/*
* Project Name:  FourteenSegDisplay
* File: SevenSegDisplay.h
* Description: header file for SevenSegDisplay sub library
* Author: Gavin Lyons.
* Created: Nov 2019
* URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

#ifndef SevenSegDisplay_h
#define SevenSegDisplay_h

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define ASCII_OFFSET 32 // ASCII table offset to jump over first missing 32 chars
#define HEX_OFFSET   16 // ASCII table offset to reach 0 position
#define DOT_MASK_DEC   0x80 //  Mask to switch on decimal point in fourteen segment.   
#define COMMON_ANODE_MASK 0xFF // mask to be applied if user wants common anode. 


class SevenSegDisplay  {

public:
    // Constructor 
    // passed GPIO pins for Rclk Sclk and serial data 74HC595
    // also passed a boolean value called common
    // common true = Common Cathode(default)
    // common false = Common Anode
    SevenSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common = true);
    
    // Methods

    // Send ASCII value to 7 segment display, passed ASCII value byte, 
    // and  digit position0x80-0x40-0x20-0x10-0x08-0x04-0x02-0x01-0x00  D8-D1
    void displayASCII(uint8_t ascii, uint8_t digits = 0x00);

    // Same as displayASCII function but turns on dot/decimal point as well ,
    // and digit position0x80-0x40-0x20-0x10-0x08-0x04-0x02-0x01-0x00  D8-D1
    void displayASCIIwDot(uint8_t ascii, uint8_t digits = 0x00) ;

    // Send HEX value to 14 segment display, passed a hex value  0-15 : 0x00 to 0x0F,  
    // and  digit position0x80-0x40-0x20-0x10-0x08-0x04-0x02-0x01-0x00  D8-D1
    void displayHex(uint8_t hex, uint8_t digits = 0x00);

    // Send  segment value to  14 segment display
    //  Passed value corresponding to segments  (DP-G-F-E-D-C-B-A) One bytes. 
    //  eg 0x01 will switch on A 
    //  and  digit position 0x80-0x40-0x20-0x10-0x08-0x04-0x02-0x01-0x00 D8-D1
    void displaySeg(uint8_t value, uint8_t digits = 0x00);
    
    // This function is for Model 2 design only: passed a string and starting position0x80-0x40-0x20-0x10-0x08-0x04-0x02-0x01-0x00  D8-D1
    // So to print AB as "AB" set start postion to 2.
    void displayString(const char* str, uint8_t startPos = 0x00);
    
private:
        uint8_t _sclk_IO;
        uint8_t _data_IO;
        uint8_t _rclk_IO;
        bool _commonCathode;
};

 
#endif