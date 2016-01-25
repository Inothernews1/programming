// /r/DailyProgrammer Challenge #3 Easy
// Completed on: 1/24/2016
// By Jonah Sussman

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[]) {
  if (argc == 1) {
    printf("Error! Not all parameters given!\n");
    printf("Format is: Chiper.exe int \"string\"\n");
    printf("Press ENTER to quit...");
    getchar();
    return 0;
  }

  int offset = atoi (argv[1]) % 26;
  char* phrase = argv[2];
  char output[strlen (phrase)];

  for (int i; phrase[i] != '\0'; i++) {
    if (phrase[i] == ' ') {
      output[i] = ' ';
      continue;
    }

    if (phrase[i] >= 'a' && phrase[i] <= 'z' && phrase[i] + offset <= 'z') {
      output[i] = phrase[i] + offset;
    }
    else if (phrase[i] >= 'A' && phrase[i] <= 'Z' && phrase[i] + offset <= 'Z') {
      output[i] = phrase[i] + offset;
    }
    else {
      output[i] = phrase[i] + offset - 26;
    }

  }

  printf("%s\n", output);
  return 0;
}
