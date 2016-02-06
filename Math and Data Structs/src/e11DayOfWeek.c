// /r/DailyProgrammer Challenge #11 Easy
// Completed on: 2016-2-6
// By Jonah Sussman

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char buffer[256];

char* intToDay (int w) {
    switch (w) {
      case 0:
        return "Sunday";
        break;
      case 1:
        return "Monday";
        break;
      case 2:
        return "Tuesday";
        break;
      case 3:
        return "Wednesday";
        break;
      case 4:
        return "Thursday";
        break;
      case 5:
        return "Friday";
        break;
      case 6:
        return "Saturday";
        break;
      default:
        return "ERROR";
        break;
    }
}

int main (int argc, char* argv[]) {
  char *ptr;
  float y, c, d, m ;
  int w = 0;

  while ((d > 31) || (d < 1)) {
    printf("Enter a valid day number> ");
    fgets(buffer, 256, stdin);

    d = strtol(buffer, &ptr, 10);
  }

  while ((m > 12) || (m < 1)) {
    printf("Enter a valid month number> ");
    fgets(buffer, 256, stdin);

    m = (((strtol(buffer, &ptr, 10) - 3) + 12) % 12) + 1;
  }

  while (strlen(buffer) != 5) {
    printf("Enter a valid year> ");
    fgets(buffer, 256, stdin);
  }

  c = (buffer[0] - '0') * 10;
  c += buffer[1] - '0';

  y = (buffer[strlen(buffer) - 3] - '0') * 10;
  y += buffer[strlen(buffer) - 2] - '0';

  if (m == 11 || m == 12) {
    if (y == 0) {
      c -= 1;
      y = 99;
    } else {
      y -= 1;
    }
  }

  w = (int)((d + floor(2.6 * m - 0.2) + y + floor(y / 4.0) + floor(c / 4.0) - (2 * c)) + 7) % 7;

  printf("That day is %s.\n", intToDay(w));
  getchar();

  return 0;
}
