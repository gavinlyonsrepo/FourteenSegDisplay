

Overview
--------------------------------------------
* Name: FourteenSegDisplay
* Description: An Arduino library to display data on a 14 segment LED module.
It requires two Daisy chained shift registers.
The module was tested on a two digit LDD-F5406RI common cathode module.
Library is also designed to work with common anode.
Library includes ASCII font and also supports Hexadecimal, Decimal point.
Optimized low memory footprint. It also provides a function for manually setting
segments to any user defined pattern. It requires (3+N) Digital GPIO pins where 
N is number of digits used. 
* Author: Gavin Lyons.
* Development platform: Arduino NANO


Table of contents
---------------------------

  * [Overview](#overview)
  * [Features](#features)
  * [Install](#install)
  * [Pictures](#pictures)
  * [Copyright](#copyright)

Features
----------------------

An Arduino library to display data on a 14 segment LED module.
It requires two daisy chained shift registers.
Tested with 74HC595.
The module was tested on was a two digit LDD-F5406RI common cathode module.
Library is also designed to work with common anode.
Library includes ASCII font and also supports Hexadecimal, Decimal point.
Optimized low memory footprint. It also provides a function for manually setting
segments to any user defined pattern. It requires (3+N) Digital GPIO pins where 
N is number of digits used. 
Sketch uses 1476 bytes (4%) of program storage space. 
Global variables use 13 bytes (0%) of dynamic memory.

The LDD-F5406RI short-form datasheet is in extra folder.

Use transistors to switch Digits on/off unless using high value of 
current limit resistor: For example 2.2K resistors will ((1.44mA) * 15= 21.6mA )will 
give total current per digit of 21.6mA with all segments on. 



**Connections**

Note: N is number of digits

| Arduino |  Shift register 1 | Shift register 2 | Digit(N) LDD-F5406RI |
| --- | --- | --- | --- |
| GPIO | SCLK 74HC595 | SCLK 74HC595| n/c |
| GPIO | RCLK 74HC595 | RCLK 74HC595| n/c |
| GPIO | SER 74HC595 | n/c |  n/c |
| n/c | QH' 74HC595 | SER 74HC595 | n/c |
| GPIO(N) | n/c |  n/c | D(N) pins |

| Shift register 1 | Shift register 2 | LDD-F5406RI |
| --- | --- | --- |
| QA |  | a 12 |
| QB |  | b 10 |
| QC |  | c 9 |
| QD |  | d 7 |
| QE |  | e 1 |
| QF |  | f 18 |
| QG |  | g1 13 |
| QH |  |  g2 6 |
|    | QA | h 17 |
|    | QB | j 15 |
|    | QC | k 14 |
|    | QD | l 2  |
|    | QE | m 4 |
|    | QF | n 5 |
|    | QG | DP 8 |


**Library Functions**

The commented functions can be found in library header file FourteenSegDisplay.h.
See this file for more details on functions.
The font is in a separate file FourteenSegDisplayFont.h.

The FourteenSegDisplay_TEST.ino contains a set of tests demonstrating library functions.

1. FourteenSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common);
2. void displayASCII(uint8_t ascii); 
3. void displayASCIIwDot(uint8_t ascii) ;
4. void displayHex(uint8_t hex);
5. void displaySeg(uint16_t value);

Install
-----------------------

The library is included in the official Arduino library manger and the optimum way to install it 
is using the library manager which can be opened by the *manage libraries* option in Arduino IDE. 
Search "fourteen" in search bar of library manager to find it.

See link below for instruction for this and for the other installation methods too.

[Installing Additional Arduino Libraries guide](https://www.arduino.cc/en/Guide/Libraries)


Pictures
------------------------------

![ sch ](https://github.com/gavinlyonsrepo/FourteenSegDisplay/blob/master/extra/image/14seg1.png)

![ layout ](https://github.com/gavinlyonsrepo/FourteenSegDisplay/blob/master/extra/image/14seg2.png)

![ module ](https://github.com/gavinlyonsrepo/FourteenSegDisplay/blob/master/extra/image/14seg4.jpg)

![ working ](https://github.com/gavinlyonsrepo/FourteenSegDisplay/blob/master/extra/image/14seg3.jpg)


Copyright
------------------------

Copyright (C) 2019 G Lyons This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, see license.md for more details
