all: test

test: target token-test lexer-test

target:
	mkdir -p target

token-test:
	c99 src/token.test.c src/token.c -l criterion -o target/token-test; ./target/token-test

lexer-test:
	c99 src/lexer.test.c src/lexer.c src/token.c -l criterion -o target/lexer-test; ./target/lexer-test
