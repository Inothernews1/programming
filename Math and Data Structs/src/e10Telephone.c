// /r/DailyProgrammer Challenge #10 Easy
// Completed on: 2016-2-5
// By Jonah Sussman

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[256];
const char *invalid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ:/";
int digitFlag = 0;

int checkPhone (int n, char *a) {
  char *b = a;

  while(*b) {
    if (strchr(invalid, *b)) {
      return 0;
    }

    b++;
  }

  if ((n == 0) && (!(strlen(a) == 3) && !(strlen(a) == 10))) {
    return 0;
  } else if (((n == 1) && (!(strlen(a) == 3) && !(strlen(a) == 4))) || digitFlag) {
    return 0;
  } else if (((n == 2) && !(strlen(a) == 4)) || digitFlag) {
    return 0;
  } else if (n > 2) {
    return 0;
  }

  if (((n == 1) && (strlen(a) == 4)) || ((n == 0) && (strlen(a) == 10))) {
    digitFlag = 1;
  }

  return 1;
}

int main (int argc, char* argv[]) {
  printf("Enter a valid phone number> ");
  fgets(buffer, 256, stdin);

  char *a;

  a = strtok(buffer, " ().-\n");

  for (int i = 0; a != NULL; i++) {
    if (!checkPhone(i, a)) {
      printf("ERROR: Not a valid phone number, you pizza chit.");
      getchar();

      return 0;
    }

    a = strtok(NULL, " ().-\n");
  }

  printf("This is a valid phone number, but you're still a pizza chit.");
  getchar();
  return 0;
}
