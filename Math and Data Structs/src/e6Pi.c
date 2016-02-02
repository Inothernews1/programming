// /r/DailyProgrammer Challenge #6 Easy
// Completed on: 2016-2-1
// By Jonah Sussman

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char* argv[]) {
  if (argc == 1) {
    printf("Error! No arguments given...\n");
    printf("The correct format is: e6Pi int\n");
    printf("Press ENTER to quit...");
    getchar();

    return 0;
  }

  char *ptr;
  int itt = strtol(argv[1], &ptr, 10);
  double piResult = 3;
  double a, b, c;

  for (int i = 0; i < itt; i++) {
    a = 2.0 * (i + 1.0);
    b = 2.0 * (i + 1.0) + 1.0;
    c = 2.0 * (i + 1.0) + 2.0;

    if (i % 2) {
      printf("%g\n", (-4.0 / (a * b * c)));
      piResult += (-4.0 / (a * b * c));
    } else {
      printf("%g\n", (4.0 / (a * b * c)));
      piResult += (4.0 / (a * b * c));
    }

  }

  printf("%g", piResult);
  getchar();

  return 0;
}

// Note: This doesn't _quite_ meet the Challenges requirments, but I don't
// understand calculus fully enough yet to do John Machin's arctan series.
