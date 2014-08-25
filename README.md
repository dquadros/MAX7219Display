MAX7219Display
==============
Arduino library for multiple digit 7 segment display controlled by a
MAX7219 LED driver.

Description
-----------
This is an Arduino library for using multiple digit 7 segment display
modules based on a MAX7219 chip, such as
http://www.dx.com/p/8-segment-led-display-board-module-for-arduino-147814

Hardware Connection
-------------------
The MAX71219 uses three communication signals: CLK, LOAD and DIN, plus
power connections (+5V and ground). The three signals can be connected to 
any Arduino digital i/o pin (including the ones marked as "analog"). If
multiples displays are to be controlled, different pins must be used for
each display,

Installation
------------
The library is installed as any Arduino library, by copying the files 
into a directory on the library search path of the Arduino IDE.

Usage
-----
The library provides a single class named MAX7219Display.

The constructor requires the pins connected to the module, the number
of digits and the starting mode (BDC or SEGMENT).

An instance of this class provides the following functions:

* setBrightness: for setting the brightness of the display
* setSegments: for displaying arbitrary data on the display
* howNumberDec: for displaying a decimal number on the display

Please refer to MAX7219Display.h for more information. An example is 
included, demonstarting the operation of most of the functions.

Credits
-------

This library offers the same methods as the TM1637Display library
from avishorp, and borrows from its comments (but not much from
its code). 

avishorp library can be found at https://github.com/avishorp/TM1637
