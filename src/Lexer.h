#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum TOKEN_TYPES {
    UNION,
    KLEENE,
    LPAREN,
    RPAREN,
    SYMBOL,
    DOT,
    END
};

typedef struct token {
    char symbol;
    uint8_t type;
} token;

typedef struct lexer {
    char* input;
    int position;
} lexer;

lexer* makeLexer(char* regex);

void nextToken(lexer* l, token* t);

void eatToken(lexer* l, token* t);

void destoryLexer(lexer** l);