#include "token.h"
#include <criterion/criterion.h>

Test(tokenizer, lookup_ident_test) {
  cr_assert_eq(FUNCTION, lookup_ident("fn"));
  cr_assert_eq(LET, lookup_ident("let"));

  cr_assert_eq(IDENT, lookup_ident("unknown"));
}
