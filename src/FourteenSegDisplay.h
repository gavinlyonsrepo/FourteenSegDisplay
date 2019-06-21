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
    FourteenSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common = true);
    
    // Methods

    // Send ASCII value to 14 segment display, passed ASCII value byte
    void displayASCII(uint8_t ascii);

    // Same as displayASCII function but turns on dot/decimal point as well 
    void displayASCIIwDot(uint8_t ascii) ;

    // Send HEX value to 14 segment display, passed a hex value  0-15 : 0x00 to 0x0F
    void displayHex(uint8_t hex);

    // Send  segment value to  14 segment display
    //  Passed value corresponding to segments  (DP-N-M-L-K-J-H-G2-G1-F-E-D-C-B-A) Two bytes. 
    // eg 0000000100000001 or 0x0101 will switch on A and H
    void displaySeg(uint16_t value);
    
private:
        uint8_t _sclk_IO;
        uint8_t _data_IO;
        uint8_t _rclk_IO;
        bool _common;

};

 
#endif
