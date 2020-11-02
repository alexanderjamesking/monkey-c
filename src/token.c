#include "token.h"
#include <string.h>

TokenType lookup_ident(char *ident) {
  if (strcmp(ident, "fn") == 0)
    return FUNCTION;
  else if (strcmp(ident, "let") == 0)
    return LET;

  /*
        "true":   TRUE,
        "false":  FALSE,
        "if":     IF,
        "else":   ELSE,
        "return": RETURN,
   */

  return IDENT;
}
