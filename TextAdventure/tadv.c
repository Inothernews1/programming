#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "tadv.h"

char* spit (node *gotN) {
  return gotN->text;
}

node* nodeMake (char* gotText, int argNum, ...) {
  node* gotN = malloc(sizeof(node));
  gotN->type = NODE_LINK;
  gotN->text = gotText;

  va_list valist;
  va_start(valist, argNum);
  link* gotLink = linkMake(argNum, valist);
  va_end(valist);

  nodeLink(gotN, gotLink);
  return gotN;
}

void nodeLink (node *gotN, link* gotLink) {
  gotN->optNum = gotLink->optNum;

  for (int i = 0; i < gotN->optNum; i++) {
    gotN->options[i] = gotLink->options[i];
    gotN->choices[i] = gotLink->choices[i];
  }
}

void nodeDisplay (node *gotN) {
  printf("%s\n", spit(gotN));

  if (gotN->type != NODE_END) {
    for (int i = 0; i < gotN->optNum; i++) {
      printf("%i: %s\n", i + 1, gotN->options[i]);
    }
  }
}

node* nodeChange (node *gotN, int gotInt) {
  return gotN->choices[gotInt - 1];
}

link* linkMake (int argNum, va_list valist) {
  link* gotLink = malloc(sizeof(link));
  int i;

  for (i = 0; i < argNum; i++) {
    gotLink->options[i] = va_arg(valist, char*);
    gotLink->choices[i] = va_arg(valist, node*);
  }

  gotLink->optNum = i;

  return gotLink;
}
