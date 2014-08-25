//  Author: dqsoft.blogspot@gmail.com
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef __MAX7219DISPLAY__
#define __MAX7219DISPLAY__

#include <inttypes.h>

class MAX7219Display {

public:
    
  // Constants to control the display segments
  //
  //      A
  //     ---
  //  F |   | B
  //     -G-
  //  E |   | C
  //     ---    . DP
  //      D

  static const uint8_t SEG_G = 0x01;
  static const uint8_t SEG_F = 0x02;
  static const uint8_t SEG_E = 0x04;
  static const uint8_t SEG_D = 0x08;
  static const uint8_t SEG_C = 0x10;
  static const uint8_t SEG_B = 0x20;
  static const uint8_t SEG_A = 0x40;
  static const uint8_t DP    = 0x80;    // Decimal Point

  //! Initialize a MAX7219Display object
  //!
  //! @param pinCLK  - The number of the digital pin connected to the clock pin of the module
  //! @param pinDIN  - The number of the digital pin connected to the DIN pin of the module
  //! @param pinLoad - The number of the digital pin connected to the LOAD pin of the module
  //! @param nDig    - Number of digits

  MAX7219Display(uint8_t pinCLK, uint8_t pinDIN, uint8_t pinLOAD, uint8_t nDig);
  
  //! Sets the brightness of the display.
  //!
  //! @param brightness A number from 0 (lowes brightness) to 15 (highest brightness)
  void setBrightness(uint8_t brightness);
  
  //! Display arbitrary data on the display
  //!
  //! This function receives raw segment values as input and displays them. 
  //! The segment data is given as a byte array, each byte corresponding 
  //! to a single digit. See SEG_x defines for bit assignments
  //! The function may either set the entire display or any desirable part on 
  //! its own. The first digit is given by the @ref pos argument. The @ref 
  //! length argument is the number of digits to be set. Other digits are not 
  //! affected.
  //!
  //! @param segments An array of size @ref length containing the raw segment values
  //! @param length The number of digits to be modified
  //! @param pos The position from which to start the modification (0 - leftmost, 3 - rightmost)
  void setSegments(const uint8_t segments[], uint8_t length = 8, uint8_t pos = 0);
  
  //! Displays a decimal number
  //!
  //! Displays the given argument as a decimal number
  //!
  //! @param num The number to be shown
  //! @param leading_zero When true, leading zeros are displayed. 
  //!        Otherwise unnecessary digits are blank
  //! @param length The number of digits to set.
  //! @param pos The position of the least significant digit (0 = rightmost)
  void showNumberDec(long num, bool leading_zero = false, uint8_t length = 8, uint8_t pos = 0);
  
protected:
   void write7219 (uint8_t addr, uint8_t data);
   
private:
	uint8_t m_pinCLK;
	uint8_t m_pinDIN;
	uint8_t m_pinLOAD;
	uint8_t m_nDig;
};

#endif // __MAX7219DISPLAY__
