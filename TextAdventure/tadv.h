#ifndef tadv_h
#define tadv_h
#include <stdarg.h>

enum {NODE_LINK, NODE_END, NODE_BENIGN};

enum {NFUNC_PLUS, NFUNC_MINUS};

typedef struct node {
  int type;
  char *text;
  int optNum;
  char *options[16];
  struct node *choices[16];
} node;

typedef struct link {
  int optNum;
  char *options[16];
  struct node *choices[16];
} link;

char* spit (node *n);
node* nodeMake (char* gotText, int argNum, ...);
void nodeLink (node* gotNode, link* gotLink);
void nodeDisplay (node* gotNode);
node* nodeChange (node* gotN, int gotInt);
link* linkMake (int argNum, va_list valist);

#endif
