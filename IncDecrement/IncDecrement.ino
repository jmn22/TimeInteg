void decrement()
{
  tenthsecs--;
  if (tenthsecs == 0)
  {
    tenthsecs = 9;  // If tenthsecs is 10, set it back to 0
    seconds--;    // and increase seconds by 1
  }
  /* Once each tenth of a second, we'll redisplay the time elapsed */
  displayDigitalTime(tenthsecs,seconds);
}

void increment()
{
  tenthsecs++;
  if (tenthsecs >= 10)
  {
    tenthsecs = 0;  // If tenthsecs is 10, set it back to 0
    seconds++;    // and increase seconds by 1
  }
  /* Once each tenth of a second, we'll redisplay the time elapsed */
  displayDigitalTime(tenthsecs,seconds);
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
  timeChar[2] = '.';
  timeChar[3] = stenth;

  /* once we have each integer separated, we need to turn them
   into displayable characters. Adding 0x30 does this (check an
   ASCII table. We set the colons to 0x0A initially, this will
   turn them into the proper 0x3A.*/
  for (int i=0; i<4; i++)
    timeChar[i] += 0x30;

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

