/*
* Project Name: FourteenSegDisplay
* File: FourteenSegDisplay.h
* Description: header file for FourteenSegDisplay  library
* Author: Gavin Lyons.
* Created: June 2019
* URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

#ifndef FourteenSegDisplay_h
#define FourteenSegDisplay_h

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define ASCII_OFFSET 32 // ASCII table offset to jump over first missing 32 chars
#define HEX_OFFSET   16 // ASCII table offset to reach 0 position
#define DOT_MASK_DEC   0x4000 //  Mask to switch on decimal point in fourteen segment.   
#define COMMON_ANODE_MASK 0xFFFF // mask to be applied if user wants common anode. 
#define LOWER_BYTE_MASK 0X00FF //mask to be applied to mask off lower byte of a uint16_t var

class FourteenSegDisplay  {

public:
    // Constructor 
    // passed GPIO pins for Rclk Sclk and serial data 74HC595
    // also passed a boolean value called common
    // common true = Common Cathode(default)
    // common false = Common Anode
    // Model2 false = use Model1(default)
    // Model2  true = use model2
    FourteenSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common = true, bool Model2 = false);
    
    // Methods

    // Send ASCII value to 14 segment display, passed ASCII value byte, 
    // and for Model2 only digit position 0x80-0x40-0x20-0x10-0x08-0x04-0x02-0x01 D8-D1
    void displayASCII(uint8_t ascii, uint8_t digits = 0x00);

    // Same as displayASCII function but turns on dot/decimal point as well ,
    // and for Model2 only digit position 0x80-0x40-0x20-0x10-0x08-0x04-0x02-0x01 D8-D1
    void displayASCIIwDot(uint8_t ascii, uint8_t digits = 0x00) ;

    // Send HEX value to 14 segment display, passed a hex value  0-15 : 0x00 to 0x0F,  
    // and for Model2 only digit position 0x80-0x40-0x20-0x10-0x08-0x04-0x02-0x01 D8-D1
    void displayHex(uint8_t hex, uint8_t digits = 0x00);

    // Send  segment value to  14 segment display
    //  Passed value corresponding to segments  (DP-N-M-L-K-J-H-G2-G1-F-E-D-C-B-A) Two bytes. 
    // eg 0000000100000001 or 0x0101 will switch on A and H
    //  and for Model2 only digit position 0x80-0x40-0x20-0x10-0x08-0x04-0x02-0x01 D8-D1
    void displaySeg(uint16_t value, uint8_t digits = 0x00);
    
    // This function is for Model 2 design only: passed a string 
    // and starting position 0x80-0x40-0x20-0x10-0x08-0x04-0x02-0x01 D8-D1
    // So to print AB as "AB" set start postion to 2.
    void displayString(const char* str, uint8_t startPos = 0x00);
    
private:
        uint8_t _sclk_IO;
        uint8_t _data_IO;
        uint8_t _rclk_IO;
        bool _commonCathode;
        bool _Model2;
};

 
#endif
