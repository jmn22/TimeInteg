// Color LCD Shield library
#include <ColorLCDShield.h>

LCDShield lcd;  // Creates an LCDShield, named lcd
int buttons[3] = {3, 4, 5};  // S1 = 3, S2 = 4, S3 = 5
signed char cont = -51;  // Philips medium contrast
boolean b1 = 0;
boolean b2 = 0;
int timeStart = 0;
int timeCount = 0;

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
  // display current time
  
  // If max time achieved, do shindig
  if(timeCount > 30000) {
    while (1) {
      // Do shindig 
    }
  }
  
  // Check for button presses
  boolean isSet = 0;
  while (millis() % 100) {
    if !(isSet) {
      b1 = digitalRead(buttons[0]);
      b2 = digitalRead(buttons[1]);
      if(b1&&b2) {
        // do error/nothing
      } else if(b1) {
        isSet = 1;
        // incrememnt
      } else if(b2) {
        isSet = 1;
        // decrement
      }
    }
  }
  // Write value to display
  
}
