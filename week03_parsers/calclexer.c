//NO NECESSARY
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM 256
#define YYEOF 399

double yylval;

int yylex(void) {
  int c = getchar();
  while (c == ' ' || c == '\t')
    c = getchar();

  if (c == '.' || isdigit(c)) {
    ungetc(c, stdin);
    if (scanf("%lf", &yylval) != 1)// se leyó incorrectamente
      abort();
    return NUM;
  } else if (c == EOF)
    return YYEOF;
  else
    return c;
}