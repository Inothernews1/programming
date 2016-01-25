// /r/DailyProgrammer Challenge #5 Easy
// Completed on: 1/24/2016
// By Jonah Sussman

#include <stdio.h>
#include <unistd.h>
#include <string.h>

char buffer[256];

int check () {
  int correct = 0;
  FILE *fp = fopen("e5.ini", "r");

  char userReal[256];

  char passReal[256];

  fscanf(fp, "%s\n%s", userReal, passReal);

  printf("Please enter your username: ");
  char user[10];
  scanf("%s", user);

  printf("Please enter your password: ");
  char pass[10];
  scanf("%s", pass);

  if (!strcmp(user, userReal) && !strcmp(pass, passReal)) {
    correct = 1;
  }

  return correct;
}

int main () {

  printf("Welcome to the Jonah Sussman Social Network!\n");

  while (!check()) {
    printf("WRONG!\n");
  }

  printf("Correct login! Signing in, please wait\n");
  sleep(1);
  printf(".");
  sleep(1);
  printf(".");
  sleep(1);
  printf(".\n");
  sleep(1);
  printf("ERROR! No friends found, logging out now.\n");
  sleep(3);
  return 0;
}
