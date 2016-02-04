// /r/DailyProgrammer Challenge #9 Easy
// Completed on: 2016-2-3
// By Jonah Sussman

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[256];

int compFunc (const void *a, const void *b) { // TODO Learn how the hell this works
  return (*(int*)a - *(int*)b);
}

int main (int argc, char* argv[]) {
  printf("> ");
  fgets(buffer, 256, stdin);

  int *list = malloc(sizeof(int*));
  char *a;
  char *ptr;
  int i;

  a = strtok(buffer, " \n");

  for (i = 0; a != NULL; i++) {
    list[i] = strtol(a, &ptr, 10);

    a = strtok(NULL, " \n");
  }

  qsort(list, i, sizeof(int), compFunc);      // TODO Also learn how this works

  for (int n = 0; n < i; n++) {
    printf("%i ", list[n]);
  }

  getchar();
  return 0;
}
