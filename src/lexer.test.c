#include "lexer.h"
#include <criterion/criterion.h>

// repeat 10 {make lexer-test}

Test(lexer, is_letter_test) {
  cr_assert(is_letter('a'));
  cr_assert_not(is_letter(' '));
}

Test(lexer, lexer_hello_test) {
  char *input = "let five = 5;";

  // char codes
  // l 108
  // e 101
  // t 116

  // f 102
  // i 105
  // v 118
  // e 101

  Lexer *l = new_lexer(input);
  Token *first = next_token(l);

  cr_assert_eq(first->type, LET);
  cr_assert_str_eq(first->literal, "let");

  Token *second = next_token(l);
  cr_assert_eq(second->type, IDENT);
  cr_assert_str_eq(second->literal, "five");

  free(first);
  free(second);
  free(l);
}
