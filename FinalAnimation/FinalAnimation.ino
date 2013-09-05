#include <ColorLCDShield.h>

LCDShield lcd;  // Creates an LCDShield, named lcd

void setup()
{
  lcd.init(PHILIPS);  // Initializes lcd, using an PHILIPSdriver
  lcd.contrast(-51);  // -51's usually a good contrast value
  lcd.clear(WHITE);  // clear the screen
  
  lcd.setStr("EpiCool", 2, 20, SLATE, WHITE);
  lcd.setCircle(66, 66, 50, BLUE, 3);
  lcd.setLine(52,85,80,95,BLUE);
  lcd.setLine(52,95,80,85,BLUE);
  lcd.setLine(41,90,91,90,BLUE);
  lcd.setLine(66,100,66,80,BLUE);
}

void loop()
{
}

