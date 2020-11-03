#include "token.h"
#include <stdbool.h>

typedef struct lexer {
  char *input;
  int position;
  int read_position;
  unsigned char ch; // current char
} lexer;

bool is_letter(unsigned char ch);

lexer *new_lexer(char *input);

token *next_token(lexer *l);
