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
} TokenType;

typedef struct Token {
  TokenType type;
  char *literal;
} Token;

TokenType lookup_ident(char *ident);
