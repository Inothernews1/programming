// /r/ DailyProgrammer Challenge #4 Easy
// Completed on: 1/24/2016

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main (int argc, char* argv[]) {
  char *ptr;
  int passNum;
  int passLength;

  if (argc == 1) {
    char temp[256];

    printf("How many passwords? ");
    fgets(temp, 256, stdin);

    passNum = strtol(temp, &ptr, 10);

    printf("Length of passwords? ");
    fgets(temp, 256, stdin);

    passLength = strtol(temp, &ptr, 10);
  }
  else {
    passNum = strtol(argv[1], &ptr, 10);
    passLength = strtol(argv[2], &ptr, 10);
  }

  char pass[passNum][passLength];
  char* passLet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  time_t t;

  srand((unsigned) time(&t));

  for (int i = 0; i < passNum; i++) {
    memset(pass[i], 'a', passLength);

    for (int n = 0; n < passLength; n++) {
      pass[i][n] = passLet[rand() % 62];

    }

    pass[i][passLength] = '\0';

    printf("%s\n", pass[i]);
  }

  return 0;
}
