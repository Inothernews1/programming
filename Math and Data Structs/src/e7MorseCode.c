// /r/DailyProgrammer Challenge #7 Easy
// Completed on:
// By Jonah Sussman

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

char buffer[256];

struct morseLetter {
  char dahDit [6];
  char letter;
};

struct morseLetter morse[] = {
  {".-",   'A'},  {"-...", 'B'},
  {"-.-.", 'C'},  {"-..",  'D'},
  {".",    'E'},  {"..-.", 'F'},
  {"--.",  'G'},  {"....", 'H'},
  {"..",   'I'},  {".---", 'J'},
  {"-.-",  'K'},  {".-..", 'L'},
  {"--",   'M'},  {"-.",   'N'},
  {"---",  'O'},  {".--.", 'P'},
  {"--.-", 'Q'},  {".-.",  'R'},
  {"...",  'S'},  {"-",    'T'},
  {"..-",  'U'},  {"...-", 'V'},
  {".--",  'W'},  {"-..-", 'X'},
  {"-.--", 'Y'},  {"--..", 'Z'},
  {"/",    ' '}
};

char retChar (char* b) {
  for (int i = 0; i < 27; i++) {
    if (!(strcmp(morse[i].dahDit, b))) {
      return morse[i].letter;
    }
  }

  return '?';
}

char* retCode (char b) {
  for (int i = 0; i < 27; i++) {
    if (b == morse[i].letter) {
      for (int n = 0; n < 6; n++) {
        if (morse[i].dahDit[n] == '\0') {
          break;
        } else if (morse[i].dahDit[n] == '/') {
          Sleep(700);
        } else if (morse[i].dahDit[n] == '.') {
          Beep(523,200);
          Sleep(200);
        } else if (morse[i].dahDit[n] == '-') {
          Beep(523,450);
          Sleep(200);
        }
      }

      Sleep(200);
      return morse[i].dahDit;
    }
  }

  return "?";
}

void decodeChar (char* buffer) {
  char *a;
  a = strtok(buffer, " \n");

  while (a != NULL) {
    putchar(retChar(a));

    a = strtok(NULL, " \n");
  }
}

void encodeChar (char* buffer) {
  for (int i = 0; i < strlen(buffer) - 1; i++) {
    printf("%s ", retCode(buffer[i]));
  }
}

int main (int argc, char* argv[]) {
  printf("> ");
  fgets(buffer, 256, stdin);

  if (buffer[0] == '-' || buffer[0] == '.' || buffer[0] == '/') {
    decodeChar(buffer);
  } else {
    encodeChar(buffer);
  }

  getchar();

  return 0;
}
