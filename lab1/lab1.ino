// Color LCD Shield library
#include <ColorLCDShield.h>

LCDShield lcd;  // Creates an LCDShield, named lcd
int buttons[3] = {3, 4, 5};  // S1 = 3, S2 = 4, S3 = 5
signed char cont = -51;  // Philips medium contrast
boolean b1 = 0;
boolean b2 = 0;
int seconds = 0;
int tenthsecs = 0;

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
  if(seconds >= 30) {
    lcd.clear(WHITE);
    finalDisplay();
    while (digitalRead(buttons[2])) {
      seconds = 0;
      tenthsecs = 0;
    }
  }
  
  // Check for button presses
  boolean isSet = 0;
  while (millis() % 100) {
    if (!isSet) {
      b1 = !digitalRead(buttons[0]);
      b2 = !digitalRead(buttons[1]);
      if(b1&&b2) {
        // do error/nothing
      } else if(b1) {
        isSet = 1;
        increment();
      } else if(b2) {
        isSet = 1;
        decrement();
      }
    }
  }
  // Write value to display
  displayDigitalTime(tenthsecs,seconds);
  
}

void decrement()
{
  if ((tenthsecs == 0) && (seconds == 0))
  {
    tenthsecs=0;
  }
  else if (tenthsecs>0)
  {
    tenthsecs--;
  }
  else if (tenthsecs == 0) {
      seconds--;    // and decrease seconds by 1
      tenthsecs = 9;
  } 
}

void increment()
{
  tenthsecs++;
  if (tenthsecs >= 10)
  {
    tenthsecs = 0;  // If tenthsecs is 10, set it back to 0
    seconds++;    // and increase seconds by 1
  }
}

/*
  displayDigitalTime() takes in values for seconds and tenths of a second 
  It'll print the time passed, in digital format, on the bottom of the screen.
 */
void displayDigitalTime(int stenth, int s)
{
  char timeChar[11] = {
    'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'    };

  /* Gotta turn the values into individual integers */
  timeChar[0] = s/10;
  timeChar[1] = s - (timeChar[0] * 10);
  timeChar[3] = stenth;

  /* once we have each integer separated, we need to turn them
   into displayable characters. Adding 0x30 does this (check an
   ASCII table. We set the colons to 0x0A initially, this will
   turn them into the proper 0x3A.*/
  for (int i=0; i<4; i++) {
    timeChar[i] += 0x30;
  }
  
  timeChar[2] = '.';
  timeChar[4] = ' ';  // add a space between the time and 'sec'
  timeChar[5] = 's';
  timeChar[6] = 'e';
  timeChar[7] = 'c';

  /* add some blank spaces after the time, otherwise it'll display
   unwanted characters */
  timeChar[8] = ' ';
  timeChar[9] = ' ';
  timeChar[10] = ' ';
  timeChar[11] = ' ';

  /* Print the time on the clock */
  lcd.setStr(timeChar, 50, 20, BLUE, WHITE);
  
}

void finalDisplay() 
{
  lcd.setStr("EpiCool", 60, 20, SLATE, WHITE);
  lcd.setCircle(66, 66, 40, BLUE, 3);
  lcd.setLine(52,85,80,95,BLUE);
  lcd.setLine(52,95,80,85,BLUE);
  lcd.setLine(41,90,91,90,BLUE);
  lcd.setLine(66,100,66,60,BLUE); // last was 80
}
