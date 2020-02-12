/*
* Project Name: FourteenSegDisplay
* File: SixteenSegDisplay.h
* Description: header file for SixteenSegDisplay sub library of FourteenSegDisplay
* Author: Gavin Lyons.
* Created: Nov 2019
* URL: https://github.com/gavinlyonsrepo/FourteenSegDisplay
*/

#ifndef SixteenSegDisplay_h
#define SixteenSegDisplay_h

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define ASCII_OFFSET 32 // ASCII table offset to jump over first missing 32 chars
#define HEX_OFFSET   16 // ASCII table offset to reach 0 position for Hexadecimal
#define DOT_MASK_DEC   0x80 //  Mask to switch on decimal point in digit byte. 
#define DOT_MASK_ANODE_DEC  0x7F //  Mask to switch on decimal point in digit byte for common anode 
#define COMMON_ANODE_MASK 0xFFFF // mask to be applied to value if user wants common anode. 
#define LOWER_BYTE_MASK 0X00FF //mask to be applied to mask off lower byte of a uint16_t var

class SixteenSegDisplay  {

public:
    // Constructor 
    // passed GPIO pins for Rclk Sclk and serial data 74HC595
    // also passed a boolean value called common
    // common = true = Common Cathode(default)
    // common = false = Common Anode
    // NoDecimalPoint = false = use the decimal point , 7 digits max
    // NoDecimalPoint = true = do not use decimal point , 8 digits max
    SixteenSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common = true, bool nodecpoint = false);
    
    // Methods
    
    //Sets the Pinmodes , call in setup.
    void displayBegin(void);
    
    /*
    Note: 
    The digits/startPos parameter in the functions refers to the position/starting bit.
    0x80  b10000000 D8 LHS (optional if no dec point used)
    0x40- b01000000 D7 LHS 
    0x20- b00100000 D6  
    0x10- b00010000 D5
    0x08- b00001000 D4
    0x04- b00000100 D3
    0x02- b00000010 D2
    0x01- b00000001 D1 RHS
    */
    
    // Send ASCII value to 16 segment display, passed ASCII value byte, 
    // and digits position 0x40-0x20-0x10-0x08-0x04-0x02-0x01 D7-D1
    //boolean to set byte
    void displayASCII(uint8_t ascii, uint8_t digits = 0x00, bool dotOn = false);

    // Send HEX value to 16 segment display, passed a hex value  0-15 : 0x00 to 0x0F,  
    // and digits position 0x40-0x20-0x10-0x08-0x04-0x02-0x01 D7-D1
    void displayHex(uint8_t hex, uint8_t digits = 0x00);

    //  Send segment value to 16 segment display,
    //  Passed value corresponding to segments  (u-t-s-r-p-n-m-k-h-g-f-e-d-c-b-a) Two bytes. 
    //  and  digits position 0x40-0x20-0x10-0x08-0x04-0x02-0x01 D7-D1
    //  Doton is for decimal point on or off, true on
    void displaySeg(uint16_t value, uint8_t digits = 0x00, bool dotOn = false);
    
    // Passed a character string, 
    // and starting position 0x40-0x20-0x10-0x08-0x04-0x02-0x01 D7-D1
    // So to print AB as "AB" set start postion to 2.
    void displayString(const char* str, uint8_t startPos = 0x00);
    
private:
        uint8_t _sclk_IO;
        uint8_t _data_IO;
        uint8_t _rclk_IO;
        bool _commonCathode;
        bool _NoDecimalPoint;
};

 
#endif
