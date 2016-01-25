// /r/DailyProgrammer Challenge #1 Easy
// Completed on: 1/24/2016
// By Jonah Sussman

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[256];

int main () {
  char *name = malloc(sizeof(char*));
  char *age = malloc(sizeof(char*));
  char *user = malloc(sizeof(char*));

  printf("What is your name? ");            // Sidenote: The hell? Why was this so
  fgets(buffer, 256, stdin);                // long?! All it is, is just f**king
  strtok(buffer, "\n");                     // input and regurgitation! *Sigh*
  strcpy(name, buffer);
  printf("What is your age? ");
  fgets(buffer, 256, stdin);
  strtok(buffer, "\n");
  strcpy(age, buffer);
  printf("What is your Reddit username? ");
  fgets(buffer, 256, stdin);
  strtok(buffer, "\n");
  strcpy(user, buffer);

  printf("Hey %s! You're %s years old, and your username is %s!\n", name, age, user);

  free(name);
  free(age);
  free(user);

  getchar();

  return 0;
}
