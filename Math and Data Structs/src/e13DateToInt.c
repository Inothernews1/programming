// /r/DailyProgrammer Challenge #13 Easy
// Completed on: 2016-2-10
// By Jonah Sussman

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[256];

int main (int argc, char* argv[]) {
  int dayNum = 0;
  int dayInt, month;
  char *ptr;

  printf("Month> ");
  fgets(buffer, 256, stdin);

  month = strtol(buffer, &ptr, 10);;

  printf("Day> ");
  fgets(buffer, 256, stdin);

  dayInt = strtol(buffer, &ptr, 10);

  // Should be a switch but fudge it...

  if (dayInt > 0) {
    if (month == 1) {
      dayNum += 0;

    } else if (month == 2 && dayInt < 29)  {
      dayNum += 31;

    } else if (month == 3 && dayInt < 31)     {
      dayNum += 59;

    } else if (month == 4 && dayInt < 31)     {
      dayNum += 90;

    } else if (month == 5 && dayInt < 32)       {
      dayNum += 120;

    } else if (month == 6 && dayInt < 31)      {
      dayNum += 151;

    } else if (month == 7 && dayInt < 32)      {
      dayNum += 181;

    } else if (month == 8 && dayInt < 32)    {
      dayNum += 212;

    } else if (month == 9 && dayInt < 31) {
      dayNum += 243;

    } else if (month == 10 && dayInt < 32)   {
      dayNum += 273;

    } else if (month == 11 && dayInt < 31)  {
      dayNum += 304;

    } else if (month == 12 && dayInt < 32)  {
      dayNum += 334;

    } else {
      dayNum = -dayInt - 1;
    }
  }

  dayNum += dayInt;

  printf("That day is %i", dayNum);
  getchar();

  return 0;
}
