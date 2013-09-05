// Color LCD Shield library
#include <ColorLCDShield.h>

LCDShield lcd;  // Creates an LCDShield, named lcd
int buttons[3] = {3, 4, 5};  // S1 = 3, S2 = 4, S3 = 5
signed char cont = -51;  // Philips medium contrast

void setup()
{
  lcd.init(PHILIPS);  // Initializes lcd, using an PHILIPS driver
  lcd.contrast(cont);  // 40 for a contrast value
  lcd.clear(TEAL);  // Teal startup screen
}

void loop()
{
}
