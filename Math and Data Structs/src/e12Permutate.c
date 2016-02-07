// /r/DailyProgrammer Challenge #12 Easy
// Completed on: 2016-2-6
// By Jonah Sussman

#include <stdio.h>
#include <string.h>

char buffer[256];

void swap(char *x, char *y) {
  char temp = *x;
  *x = *y;
  *y = temp;
}

void permutate(char *a, int level, int length) {
  if (level == length) {
    printf("%s\n", a);
  } else {
    for (int branch = level; branch <= length; branch++) {
      swap(&a[level], &a[branch]);
      permutate(a, level + 1, length);
      swap(&a[level], &a[branch]);
    }
  }
}

int main (int argc, char* argv[]) {
  printf("String to permutate> ");
  fgets(buffer, 256, stdin);

  char *str = buffer;
  str[strlen(str) - 1] = '\0';

  permutate(str, 0, strlen(str) - 1);

  getchar();

  return 0;
}
