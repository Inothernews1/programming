// /r/DailyProgrammer Challenge #2 Easy
// Completed on: 2016-2-1
// By Jonah Sussman

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[256];

int main () {
  char* ptr;
  double force, mass, accel;
  double answer;

  printf("What would you like to find? F, M, or A? ");
  fgets(buffer, 256, stdin);

  if(buffer[0] == 'f' || 'F') {
    printf("M? ");
    fgets(buffer, 256, stdin);
    mass = strtol(buffer, &ptr, 10);

    printf("A? ");
    fgets(buffer, 256, stdin);
    accel = strtol(buffer, &ptr, 10);

    answer = mass * accel;
    printf("F = %g", answer);
  }

  else if(buffer[0] == 'm' || 'M') {
    printf("F? ");
    fgets(buffer, 256, stdin);
    force = strtol(buffer, &ptr, 10);

    printf("A? ");
    fgets(buffer, 256, stdin);
    accel = strtol(buffer, &ptr, 10);

    answer = force / accel;
    printf("M = %g", answer);
  }

  else if(buffer[0] == 'A' || 'a') {
    printf("M? ");
    fgets(buffer, 256, stdin);
    mass = strtol(buffer, &ptr, 10);

    printf("F? ");
    fgets(buffer, 256, stdin);
    accel = strtol(buffer, &ptr, 10);

    answer = force / mass;
    printf("A = %g", answer);
  }

  getchar();

  return 0;
}
