#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_char(lexer *l) {
  if (l->read_position >= (int)strlen(l->input)) {
    l->ch = 0;
  } else {
    l->ch = l->input[l->read_position];
  }

  l->position = l->read_position;
  l->read_position += 1;
}

lexer *new_lexer(char *input) {
  lexer *l = malloc(sizeof(lexer));
  l->input = input;
  l->position = 0;
  l->read_position = 0;
  l->ch = 0;
  read_char(l);
  return l;
}

token *new_token(token_type type, char *ch) {
  token *t = malloc(sizeof(token));
  t->type = type;
  t->literal = ch;
  return t;
}

bool is_letter(unsigned char ch) {
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

bool is_digit(unsigned char ch) { return '0' <= ch && ch <= '9'; }

char *read_identifier(lexer *l) {
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

char *read_number(lexer *l) {
  int start = l->position;

  while (is_digit(l->ch)) {
    read_char(l);
  }

  char *number = malloc(l->position - start + 1);
  strncpy(number, l->input + start, l->position);

  return number;
}

void skip_whitespace(lexer *l) {
  while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
    read_char(l);
  }
}

token *next_token(lexer *l) {
  token *t;

  skip_whitespace(l);

  char ch[2];
  ch[0] = l->ch;
  ch[1] = '\0';

  switch (l->ch) {
  case '=':
    t = new_token(ASSIGN, ch);
    break;

  case ';':
    t = new_token(SEMICOLON, ch);
    break;

  case '(':
    t = new_token(LPAREN, ch);
    break;

  case ')':
    t = new_token(RPAREN, ch);
    break;

  case ',':
    t = new_token(COMMA, ch);
    break;

  case '+':
    t = new_token(PLUS, ch);
    break;

  case '{':
    t = new_token(LBRACE, ch);
    break;

  case '}':
    t = new_token(RBRACE, ch);
    break;

  case 0:
    t = new_token(END_OF_FILE, "");
    break;

  default:
    if (is_letter(l->ch)) {
      char *identifier = read_identifier(l);
      return new_token(lookup_ident(identifier), identifier);
    } else if (is_digit(l->ch)) {
      char *num = read_number(l);
      return new_token(INT, num);
    } else {
      t = new_token(ILLEGAL, ch);
    }
  }

  read_char(l);
  return t;
}
