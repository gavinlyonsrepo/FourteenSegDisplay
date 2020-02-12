/*
* Project Name: FourteenSegDisplay
* File: NineSegDisplay.h
* Description: header file for NineSegDisplay sub library
* Author: Gavin Lyons.
* Created: Jan 2020
* URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

#ifndef NineSegDisplay_h
#define NineSegDisplay_h

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define ASCII_OFFSET 32 // ASCII table offset to jump over first missing 32 chars
#define HEX_OFFSET   16 // ASCII table offset to reach 0 position
#define DOT_MASK_DEC   0x200 //  Mask to switch on decimal point in nine segment.   
#define COMMON_ANODE_MASK 0x3FF // mask to be applied if user wants common anode. 
#define LOWER_BYTE_MASK 0X00FF //mask to be applied to mask off lower byte of a uint16_t var

class NineSegDisplay  {

public:
    // Constructor 
    // passed GPIO pins for Rclk Sclk and serial data 74HC595
    // also passed a boolean value called common
    // common true = Common Cathode(default)
    // common false = Common Anode
    NineSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common = true);
    
    // Methods
    
    //Sets the Pinmodes , call in setup.
	void displayBegin();
	
    /*
    Note: 
    The digits/startPos parameter in the functions refers to the position/starting bit
    0x20- b100000 D6 LHS 
    0x10- b010000 D5
    0x08- b001000 D4
    0x04- b000100 D3
    0x02- b000010 D2
    0x01- b000001 D1 RHS
    */
    
    // Send ASCII value to nine segment display, passed ASCII value byte, 
    // and  starting  digit position 0x20-0x10-0x08-0x04-0x02-0x01 D6-D1
    void displayASCII(uint8_t ascii, uint8_t digits = 0x00);

    // Same as displayASCII function but turns on dot/decimal point as well ,
    // and starting  digit position 0x20-0x10-0x08-0x04-0x02-0x01 D6-D1
    void displayASCIIwDot(uint8_t ascii, uint8_t digits = 0x00) ;

    // Send HEX value to nine segment display, passed a hex value  0-15 : 0x00 to 0x0F,  
    // and starting  digit position 0x20-0x10-0x08-0x04-0x02-0x01 D6-D1
    void displayHex(uint8_t hex, uint8_t digits = 0x00);

    // Send  segment value to nine segment display
    //  Passed value corresponding to segments  (DP-I-H-G-F-E-D-C-B-A) Two bytes. 
    // eg 0010000001 or 0x0101 will switch on A and H
    //  and  starting  digit position 0x20-0x10-0x08-0x04-0x02-0x01 D6-D1
    void displaySeg(uint16_t value, uint8_t digits = 0x00);
    
    // Passed a string 
    // and starting position 0x20-0x10-0x08-0x04-0x02-0x01 D6-D1
    // So to print AB as "AB" set start postion to 2.
    void displayString(const char* str, uint8_t startPos = 0x00);
    
private:
        uint8_t _sclk_IO;
        uint8_t _data_IO;
        uint8_t _rclk_IO;
        bool _commonCathode;
};

 
#endif
