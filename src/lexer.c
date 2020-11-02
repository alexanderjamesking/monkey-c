#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_char(Lexer *l) {
  if (l->readPosition >= (int)strlen(l->input)) {
    l->ch = 0;
  } else {
    l->ch = l->input[l->readPosition];
  }

  l->position = l->readPosition;
  l->readPosition += 1;
}

Lexer *new_lexer(char *input) {
  Lexer *l = malloc(sizeof(Lexer));
  l->input = input;
  // important to initialize this otherwise it will randomly blow up
  l->readPosition = 0;
  read_char(l);
  return l;
}

Token *new_token(TokenType tokenType, char *ch) {
  Token *t = malloc(sizeof(Token));
  t->type = tokenType;
  t->literal = ch;
  return t;
}

bool is_letter(unsigned char ch) {
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

bool is_digit(unsigned char ch) { return '0' <= ch && ch <= '9'; }

char *read_identifier(Lexer *l) {
  int start = l->position;

  while (is_letter(l->ch)) {
    read_char(l);
  }

  char *identifier = malloc(l->position - start + 1);

  int n = l->position - start;
  char *src = l->input + start;
  strncpy(identifier, src, n);

  return identifier;
}

char *read_number(Lexer *l) {
  int start = l->position;

  while (is_digit(l->ch)) {
    read_char(l);
  }

  char *number = malloc(l->position - start + 1);
  strncpy(number, l->input + start, l->position);

  return number;
}

void skip_whitespace(Lexer *l) {
  while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
    read_char(l);
  }
}

Token *next_token(Lexer *l) {
  Token *token;

  skip_whitespace(l);

  char ch[2];
  ch[0] = l->ch;
  ch[1] = '\0';

  switch (l->ch) {
  case '=':
    token = new_token(ASSIGN, ch);
    break;

  case ';':
    token = new_token(SEMICOLON, ch);
    break;

  case '(':
    token = new_token(LPAREN, ch);
    break;

  case ')':
    token = new_token(RPAREN, ch);
    break;

  case ',':
    token = new_token(COMMA, ch);
    break;

  case '+':
    token = new_token(PLUS, ch);
    break;

  case '{':
    token = new_token(LBRACE, ch);
    break;

  case '}':
    token = new_token(RBRACE, ch);
    break;

  case 0:
    token = new_token(END_OF_FILE, "");
    break;

  default:
    if (is_letter(l->ch)) {
      char *identifier = read_identifier(l);
      return new_token(lookup_ident(identifier), identifier);
    } else if (is_digit(l->ch)) {
      char *num = read_number(l);
      return new_token(INT, num);
    } else {
      token = new_token(ILLEGAL, ch);
    }
  }

  read_char(l);
  return token;
}
