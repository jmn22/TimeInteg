// Color LCD Shield library
#include <ColorLCDShield.h>

LCDShield lcd;  // Creates an LCDShield, named lcd
int buttons[3] = {3, 4, 5};  // S1 = 3, S2 = 4, S3 = 5
signed char cont = -51;  // Philips medium contrast

void setup()
{
  Serial.begin(9600);
  for (int i=0; i<3; i++)
  {
    pinMode(buttons[i], INPUT);  // Set buttons as inputs
    digitalWrite(buttons[i], HIGH);  // Activate internal pull-up
  }
  lcd.init(PHILIPS);  // Initializes lcd, using an PHILIPS driver
  lcd.contrast(cont);  // 40 for a contrast value
  lcd.clear(WHITE);  // Teal startup screen
}

void loop()
{
}
