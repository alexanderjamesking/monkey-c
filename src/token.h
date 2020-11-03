#include <string.h>

typedef enum {
  ILLEGAL,
  END_OF_FILE,

  // identifiers and literals
  IDENT,
  INT,

  // operators
  ASSIGN, // =
  PLUS,   // +

  // delimiters
  COMMA,     // ,
  SEMICOLON, // ;

  LPAREN, // (
  RPAREN, // )
  LBRACE, // {
  RBRACE, // }

  // keywords
  FUNCTION,
  LET
} token_type;

typedef struct token {
  token_type type;
  char *literal;
} token;

token_type lookup_ident(char *ident);
