#include <MAX7219Display.h>

// MAX7219Display Example

// 8 digit display connected to these pins
const uint8_t pinCLK = 4;
const uint8_t pinLOAD = 5;
const uint8_t pinDIN = 6;

MAX7219Display myDisplay(pinCLK, pinDIN, pinLOAD, 8);
long num;


void setup()
{
  myDisplay.showNumberDec (12345678L);
  delay (5000);
  myDisplay.showNumberDec (87654321L);
  delay (5000);
  num = 0L;
}

void loop()
{
  myDisplay.showNumberDec (num);
  delay (100);
  if (++num > 99999999L)
    num = 0L;
}

