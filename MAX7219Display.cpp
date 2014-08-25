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

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
}

#include <MAX7219Display.h>
#include <Arduino.h>

// MAX7219 Registers
#define MAX7219_NOP   0x00
#define MAX7219_DIG0  0x01
#define MAX7219_DIG1  0x02
#define MAX7219_DIG2  0x03
#define MAX7219_DIG3  0x04
#define MAX7219_DIG4  0x05
#define MAX7219_DIG5  0x06
#define MAX7219_DIG6  0x07
#define MAX7219_DIG7  0x08
#define MAX7219_MODE  0x09
#define MAX7219_INT   0x0A
#define MAX7219_LIM   0x0B
#define MAX7219_SHUT  0x0C
#define MAX7219_TEST  0x0F

static const uint8_t digitToSegment[] = {
     // XABCDEFG
      0b01111110,    // 0
      0b00110000,    // 1
      0b01101101,    // 2
      0b01111001,    // 3
      0b00110011,    // 4
      0b01011011,    // 5
      0b01011111,    // 6
      0b01110000,    // 7
      0b01111111,    // 8
      0b01111011     // 9
};

MAX7219Display::MAX7219Display(uint8_t pinCLK, uint8_t pinDIN, 
                uint8_t pinLOAD, uint8_t nDig)
{
    // Save the pin numbers
    m_pinCLK = pinCLK;
    m_pinDIN = pinDIN;
    m_pinLOAD = pinLOAD;
    
    // Set the pin direction and default value
    pinMode (m_pinLOAD, OUTPUT);
    pinMode (m_pinDIN, OUTPUT);
    pinMode (m_pinCLK, OUTPUT);
    digitalWrite (m_pinLOAD, HIGH);
    digitalWrite (m_pinDIN, LOW);
    digitalWrite (m_pinCLK, LOW);
    
    // Save configuration
    if ((nDig > 0) && (nDig < 9))
        m_nDig = nDig;
    else
        m_nDig = 8;
    
    // Configure the controler
    write7219 (MAX7219_SHUT, 0x00);
    write7219 (MAX7219_TEST, 0x00);
    write7219 (MAX7219_MODE, 0x00);
    write7219 (MAX7219_INT, 0x0F);
    write7219 (MAX7219_LIM, m_nDig-1);
    for (uint8_t i = 0; i < 8; i++)
        write7219 (MAX7219_DIG0 + i, 0);
    write7219 (MAX7219_SHUT, 0x01);
}

void MAX7219Display::setBrightness(uint8_t brightness)
{
    if (brightness > 15)
        brightness = 15;
	write7219 (MAX7219_INT, brightness);
}

void MAX7219Display::setSegments(const uint8_t segments[], uint8_t length, uint8_t pos)
{
    // Sanity check
    if (pos >= m_nDig)
        pos = m_nDig-1;
    if ((pos+length) > m_nDig)
        length = m_nDig - pos;
    
    // write the values
    for (uint8_t i = 0; i < length; i++)
        write7219 (MAX7219_DIG0 + pos + i, segments[i]);
}
 
void MAX7219Display::showNumberDec(long num, bool leading_zero, uint8_t length, uint8_t pos)
{
    uint8_t prim;
    uint8_t aux[8];
	bool showZero = leading_zero;
    uint8_t i;

    // Sanity check
    if (pos >= m_nDig)
        pos = m_nDig-1;
    if ((pos+length) > m_nDig)
        length = m_nDig - pos;
    
    // Take care of negative numbers
    prim = MAX7219_DIG7 - pos;
    if (num < 0)
    {
        num = -num;
        write7219 (prim, SEG_G);
        prim--;
        length--;
    }

    // Generate digits
    for (i = 0; i < length; i++)
    {
        aux[i] = (uint8_t)(num % 10L);
        num = num / 10L;
    }        
    
    // Write the digits
	for(i = 0; i < length; i++) 
    {
        uint8_t dig = aux[length - i - 1];
        if (!showZero && (dig == 0) && (i != (length-1)))
        {
            write7219 (prim - i, 0);
        }
        else
        {
            if (dig != 0)
                showZero = true;
            write7219 (prim - i, digitToSegment[dig]);
        }
	}
	
}

void MAX7219Display::write7219 (uint8_t addr, uint8_t data)
{
  digitalWrite (m_pinLOAD, LOW);
  shiftOut (m_pinDIN, m_pinCLK, MSBFIRST, addr);
  shiftOut (m_pinDIN, m_pinCLK, MSBFIRST, data);
  digitalWrite (m_pinLOAD, HIGH);
}
