// Color LCD Shield library
#include <ColorLCDShield.h>

LCDShield lcd;  // Creates an LCDShield, named lcd
int buttons[3] = {3, 4, 5};  // S1 = 3, S2 = 4, S3 = 5
signed char cont = -51;  // Philips medium contrast
boolean b1 = 0;  // Status of button 1 (0 = unpressed, 1 = pressed)
boolean b2 = 0;  // Status of button 2 (0 = unpressed, 1 = pressed)
int seconds = 0;  // Seconds counter
int tenthsecs = 0;  // tenths of seconds counter

/* setup() initializes the Arduino and the LCD shield with the 
   preset values from the field variables above.  
 */
void setup()
{
  Serial.begin(9600);
  for (int i=0; i<3; i++)
  {
    pinMode(buttons[i], INPUT);  // Set buttons as inputs
    digitalWrite(buttons[i], HIGH);  // Activate internal pull-up
  }
  lcd.init(PHILIPS);  // Initializes lcd, using an PHILIPS driver
  lcd.contrast(cont);  
  lcd.clear(WHITE); 
}

void loop()
{
  /* If max time achieved, do shindig */
  if(seconds >= 30) {
    lcd.clear(WHITE);
    finalDisplay();
    // wait until the reset button is pressed before resuming
    while (digitalRead(buttons[2])) {
      seconds = 0;
      tenthsecs = 0;
    }
    lcd.clear(WHITE);
  }
  
  /* Check for button presses */
  boolean isSet = 0;
  while (millis() % 100) { // create a 0.1s chunk of time in a while loop
    if (!isSet) {  // if an outcome has not been determined
      // read buttons (inverted because pull-up)
      b2 = !digitalRead(buttons[0]);
      b1 = !digitalRead(buttons[1]);
      if(b1&&b2) {
        // do nothing
      } else if(b1) {
        isSet = 1;
        increment();
      } else if(b2) {
        isSet = 1;
        decrement();
      }
    }
  }
  /* Write value to display */
  displayDigitalTime(tenthsecs,seconds);
  
}

/* decrement() 
   decreases the value of the counter (tenthsecs 
   and seconds) by one tenth of a second. It has limits at 
   00.0s and 30.0s.
 */
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

/* increment() 
   increases the value of the counter (tenthsecs 
   and seconds) by one tenth of a second.  It has limits at 
   00.0s and 30.0s.
 */
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
  displayDigitalTime() takes in values for seconds and tenths 
  of a second and prints the time passed, in digital format,
  on the LCD screen.
 */
void displayDigitalTime(int stenth, int s)
{
  // initialize character array
  char timeChar[11] = {
    'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'    };

  // Turn integer values into individual decimal place integers
  timeChar[0] = s/10;
  timeChar[1] = s - (timeChar[0] * 10);
  timeChar[3] = stenth;

  /* once we have each integer separated, we need to turn them
   into displayable characters. Adding 0x30 does this (cool 
   ASCII trick) */
  for (int i=0; i<4; i++) {
    timeChar[i] += 0x30;
  }
  
  timeChar[2] = '.';  // set '.' as the delimiter between seconds and tenths of seconds
  timeChar[4] = ' ';  // add a space between the time and 'sec'
  timeChar[5] = 's';
  timeChar[6] = 'e';
  timeChar[7] = 'c';

  /* add some blank spaces after the time, otherwise it'll display
   unwanted characters - THIS CAUSES PROBLEMS
  timeChar[8] = ' ';
  timeChar[9] = ' ';
  timeChar[10] = ' ';
  timeChar[11] = ' ';
  */

  /* Print the time on the clock */
  lcd.setStr(timeChar, 50, 20, BLUE, WHITE);
  
}

/* finalDisplay() prints the EpiCool logo on the screen */
void finalDisplay() 
{
  lcd.setStr("EpiCool", 60, 10, SLATE, WHITE);
  lcd.setCircle(66, 66, 40, BLUE, 3);
  lcd.setLine(52,85,80,95,BLUE);
  lcd.setLine(52,95,80,85,BLUE);
  lcd.setLine(41,90,91,90,BLUE);
  lcd.setLine(66,100,66,80,BLUE);
}
