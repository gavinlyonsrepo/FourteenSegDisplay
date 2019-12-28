![ module ](https://github.com/gavinlyonsrepo/FourteenSegDisplay/blob/master/extra/image/14seg4.jpg)

Overview
--------------------------------------------
* Name: FourteenSegDisplay
* Description: An Arduino library to display data on a 14 segment LED module.
It requires 2 or 3 Daisy chained shift registers.
Library is also designed to work with common anode and common cathode module.
Library includes ASCII font and also supports Hexadecimal, Decimal point, strings.
Optimized low memory footprint. It also provides a function for manually setting
segments to any user defined pattern. 
Also the library will suport seven and 16 segment displays.
* Author: Gavin Lyons.
* Development platform: Tested on a Arduino NANO & UNO.
* Copyright: (C) 2019 G Lyons. See license.md.
* History: See changelog.md in documents.

Table of contents
---------------------------

  * [Overview](#overview)
  * [Install](#install)
  * [Files](#files)
  * [Seven Segment](#seven-segment)
  * [Fourteen Segment](#fourteen-segment)
  * [Sixteen Segment](#sixteen-segment)

Install
-----------------------

The library is included in the official Arduino library manger and the optimum way to install it 
is using the library manager which can be opened by the *manage libraries* option in the Arduino IDE. 
Search "fourteen" in search bar of library manager to find it quickly.

See link below for instruction for this and for the other installation methods too.

[Installing Additional Arduino Libraries guide](https://www.arduino.cc/en/Guide/Libraries)

Files
------------------------

**Files table**

| Segment | Test files | Font file | Header file | Cpp code file |
| --- | --- | --- | --- |  --- | 
| 7 | SevenSegDisplay_TEST.ino | SevenSegDisplayFont.h| SevenSegDisplay.h | SevenSegDisplay.cpp |
| 14 | FourteenSegDisplay_*.ino | FourteenSegDisplayFont.h | FourteenSegDisplay.h | FourteenSegDisplay.cpp |
| 16 |  SixteenSegDisplay_TEST.ino | SixteenSegDisplayFont.h | SixteenSegDisplay.h | SixteenSegDisplay.cpp |


**Library Functions**

The commented functions can be found in library header files *.h.
See these file for more details on functions.
The font is in a separate file *DisplayFont.h.

The *_TEST.ino files contains a set of tests demonstrating library functions.

1. SevenSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common);
2. FourteenSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common, bool model2);
3. SixteenSegDisplay(uint8_t rclk, uint8_t sclk, uint8_t data, bool common, bool nodecpoint);
4. void displayASCII(uint8_t ascii, uint8_t digits);  // 7 and 14 seg only 
5. void displayASCIIwDot(uint8_t ascii, uint8_t digits ); //  7 and 14 seg only 
6. void displayASCII(uint8_t ascii, uint8_t digits , bool dotOn); // 16 seg only
7. void displayHex(uint8_t hex, uint8_t digits ;
8. void displaySeg(uint16_t value, uint8_t digits);
9. void displayString(const char* str, uint8_t startPos); // Not available in Model1 14 seg

![ layout ](https://github.com/gavinlyonsrepo/FourteenSegDisplay/blob/master/extra/image/14seg2.png)


Seven Segment
--------------------

A seven-segment display is a form of electronic display device for displaying decimal numerals.
Seven-segment displays are widely used in digital clocks, electronic meters, basic calculators, 
and other electronic devices that display numerical information.[
The first shift register sets the eight bits of data and the second controls the 
digits. Tested on a 2381AS 3 digit common anode. Will also  work with common cathode
(note change transistor for NPN and emiiter to GND) 
The design supports maximum eight digits, Just add more digits to rest
of shift registers pins in order. D8D7D6D5D4D3D2D1
For purposes of the schematic and software D1
is the Least significant or right most Digit. 

![ 7seg ](https://github.com/gavinlyonsrepo/FourteenSegDisplay/blob/master/extra/image/7seg2.jpg)

**Connections**

| Arduino , SW | IC 1 | IC 2 | 2381AS|
| --- | --- | --- | --- |
| GPIO , SCLK595 | SCLK  | SCLK  |  |
| GPIO , RCLK595 | RCLK  | RCLK  |  |
| GPIO , SER595  | SER   |       |  |
|                | QH'   | SER   |  |
|   | QA |  | a 11 |
|   | QB |  | b 7 |
|   | QC |  | c 4 |
|   | QD |  | d 2 |
|   | QE |  | e 1 |
|   | QF |  | f 10 |
|   | QG |  | g 5 |
|   | QH |  |  DP 3 |
|   |    | QA | D1 8 |
|   |    | QB | D2 9 | 
|   |    | QC | D3 12 |


![ layout ](https://github.com/gavinlyonsrepo/FourteenSegDisplay/blob/master/extra/image/7seg.png)

Fourteen Segment
----------------------

A fourteen-segment display (FSD) sometimes referred to as a Starburst, Alphanumeric or Union Jack display.
is a type of display based on 14 segments that can be turned on or off to produce letters and numerals.
It is an expansion of the more common seven-segment display, having an additional four diagonal and 
two vertical segments with the middle horizontal segment broken in half. 
A seven-segment display suffices for numerals and certain letters, 
but unambiguously rendering the ISO basic Latin alphabet requires more detail. 

An Arduino library to display data on a 14 segment LED module.
It requires two or three daisy chained shift registers.
Tested with 74HC595 shift registers.
The module was tested on was a two digit LDD-F5406RI common cathode module.
Library is also designed to work with common anode(If using common anode the transistors 
will have to switch Digit pin to VCC (not GND as per schematic) to activate.
Library includes ASCII font and also supports Hexadecimal, Decimal point.
Optimized low memory footprint. It also provides a function for manually setting
segments to any user defined pattern.  There are two different designs(models) 
Sketch uses 2516 bytes (8%) of program storage space. Maximum is 30720 bytes.
Global variables use 235 bytes (11%) of dynamic memory, leaving 1813 bytes for local variables. Maximum is 2048 bytes.)
The LDD-F5406RI short-form datasheet is in extra folder(lib should work all types of
LED 14 segment modules just wiring in schematic maybe different, Check your datasheet)
The main example file(FourteenSegDisplay_TEST) covers both models,
Just change the "model2" and "testnumber" at top of file,
to model and test you want run.
The second file (FourteenSegDisplay_ADC),
shows a practical example using Model2 to display a ADC value on display. 
The library was tested on a two digit LDD-F5406RI common  cathode.

**Models Table comparison**

| Model | No of Shift registers | No of GPIO pins | No of digits |
| --- | --- | --- | --- | 
| 1 | 2 | 3+ N (N Number of digits) | 1 to infinity |
| 2 | 3 | 3 | 1 to 8  |

**Model One**

This model uses GPIO to switch on and off digits as a result it uses more 
GPIO pins than model 2. It requires (3+N) Digital GPIO pins, where 
N is number of digits used. So 4 digits requires 7 GPIO + common ground.
This model needs two shift registers.

Use transistors to switch Digits on/off unless using high value of 
current limit resistor: For example 2.2K resistors will ((1.44mA) * 15= 21.6mA )will 
give total current per digit of 21.6mA with all segments on

**Connections**

Note: N is number of digits (eg for eight digits (D8D7D65D4D3D2D1). For purposes of the schematic and software D1
is the Least significant or right most Digit. 
If adding more modules or larger modules simply add another GPIO for each digit. and connect data lines
together(a to a , b to b etc) You can add as  many digits as you want.

| Arduino , SW | IC 1 | IC 2 | LDD-F5406RI |
| --- | --- | --- | --- |
| GPIO , SCLK595 | SCLK  | SCLK  |  |
| GPIO , RCLK595 | RCLK  | RCLK  |  |
| GPIO , SER595  | SER   |       |  |
|                | QH'   | SER   |  |
|   | QA |  | a 12 |
|   | QB |  | b 10 |
|   | QC |  | c 9 |
|   | QD |  | d 7 |
|   | QE |  | e 1 |
|   | QF |  | f 18 |
|   | QG |  | g1 13 |
|   | QH |  |  g2 6 |
|   |    | QA | h 17 |
|   |    | QB | j 15 |
|   |    | QC | k 14 |
|   |    | QD | l 2  |
|   |    | QE | m 4 |
|   |    | QF | n 5 |
|   |    | QG | DP 8 |
| GPIO, D1 | | | Digit 1 11 |
| GPIO, D2 | | | Digit 2 16 |


![ Model 1 sch ](https://github.com/gavinlyonsrepo/FourteenSegDisplay/blob/master/extra/image/14segModel1.png)

**Model Two**

This model uses a third shift register to switch on and off digits as a result it uses just
3 GPIO pins + common ground. The disadvantage is it requires a third shift register and has a maximum of 8 digits.

**Connections**

This model supports a  maximum of 8 digits (eg for eight digits (D8D7D65D4D3D2D1). 
For purposes of the schematic and software D1
is the Least significant or right most Digit. 
The table below can be expanded by 6 more digits if more LED modules added
for digits 3-8. 

| Arduino , SW | IC 1 | IC 2 | IC 3 | LDD-F5406RI | 
| ---  | --- | --- | --- | --- | 
| GPIO , SCLK595 | SCLK  | SCLK | SCLK |  |
| GPIO , RCLK595 | RCLK  | RCLK | RCLK |  |
| GPIO , SER595 | SER  |  |   |   |
|    | QH'  | SER  |  |   |
|    |   |  QH' | SER |   |
|   | QA |    |     | a 12 |
|   | QB |    |     | b 10 |
|   | QC |    |     | c 9 |
|   | QD |    |     | d 7 |
|   | QE |    |     | e 1 |
|   | QF |    |     | f 18 |
|   | QG |    |     | g1 13 |
|   | QH |    |     |  g2 6 |
|   |    | QA |     | h 17 |
|   |    | QB |     | j 15 |
|   |    | QC |     | k 14 |
|   |    | QD |     | l 2  |
|   |    | QE |     | m 4 |
|   |    | QF |     | n 5 |
|   |    | QG |     | DP 8 |
|   |    |    | QA  | Digit1 11 |
|   |    |    | QB  | Digit2 16 |


![ Model 2 sch ](https://github.com/gavinlyonsrepo/FourteenSegDisplay/blob/master/extra/image/14segModel2.png)

![ font ](https://github.com/gavinlyonsrepo/FourteenSegDisplay/blob/master/extra/image/14seg5.jpg)


Sixteen Segment
------------------------------------

A sixteen-segment display (SISD) is a type of display based on 16 segments 
that can be turned on or off to produce a graphic pattern. 
It is an extension of the more common seven-segment display, 
adding four diagonal and two vertical segments and splitting the three horizontal segments in half. 

![ 16seg1 ](https://github.com/gavinlyonsrepo/FourteenSegDisplay/blob/master/extra/image/16seg1.jpg)

This design requires 3 shift registers. 2 shift registers move data word to display
and third to controls digits. The last bit of third register controls decimal point.
As a result this limits maximum display size to seven digits but
If user does not want decmial point support this can be disabled by setting a parameter.
and user can use all 8. 
This model supports a  maximum of 7-8 digits (eg for eight digits (D8D7D65D4D3D2D1). 
For purposes of the schematic and software D1
is the Least significant or right most Digit. This library was tested on a
single digit PSC05-11SURKWA common cathode. This table can be expaned to 7-8
digits.

**Connections**

| Arduino , SW | IC 1 | IC 2 | IC 3 | PSC05-11SURKWA | 
| ---  | --- | --- | --- | --- | 
| GPIO , SCLK595 | SCLK  | SCLK | SCLK |  |
| GPIO , RCLK595 | RCLK  | RCLK | RCLK |  |
| GPIO , SER595 | SER  |  |   |   |
|    | QH'  | SER  |  |   |
|    |   |  QH' | SER |   |
|   | QA |    |     | a 1 |
|   | QB |    |     | b 18 |
|   | QC |    |     | c 16 |
|   | QD |    |     | d 13 |
|   | QE |    |     | e 10 |
|   | QF |    |     | f 9 |
|   | QG |    |     | g 8 |
|   | QH |    |     | h 4 |
|   |    | QA |     | k 3 |
|   |    | QB |     | m 2 |
|   |    | QC |     | n 17 |
|   |    | QD |     | p 15 |
|   |    | QE |     | r 6 |
|   |    | QF |     | s 14 |
|   |    | QG |     | t 7 |
|   |    | QH |     | u 5 |
|   |    |    | QA  | Digit1 11 thru a transistor npn switch|
|   |    |    | QH  | Decimal point 12 |
