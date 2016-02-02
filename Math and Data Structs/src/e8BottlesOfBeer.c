// /r/DailyProgrammer Challenge #8 Easy
// Completed on: 2016-2-1
// By Jonah Sussman

#include <stdio.h>
#include <unistd.h>

int main (int argc, char* argv[]) {

  for (int i = 99; i > 1; i--) {
    printf("%i bottles of beer on the wall!\n", i);
    printf("%i bottles of beer! Take one down, pass it around!\n", i);
    printf("%i bottles of beer on the wall!\n", (i - 1));
  }

  printf("1 bottle of beer on the wall!\n");
  printf("1 bottle of beer! Take one down, pass it around!\n");
  printf("No more bottles of beer on the wall!\n");

  getchar();

  return 0;
}
