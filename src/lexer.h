#include "token.h"
#include <stdbool.h>

typedef struct Lexer {
  char *input;
  int position;
  int readPosition;
  unsigned char ch; // current char
} Lexer;

bool is_letter(unsigned char ch);

Lexer *new_lexer(char *input);

Token *next_token(Lexer *l);
