#include <stdlib.h>

enum TOKEN_TYPES {
    UNION,
    KLEENE,
    LPAREN,
    RPAREN,
    SYMBOL,
    DOT,
    END,
    ERR
};

typedef struct token {
    char symbol;
    int type;
} token;

typedef struct lexer {
    char* input;
    int position;
} lexer;

lexer* makeLexer(char* regex);

//Look at next token without modification
void nextToken(lexer* l, token* t);

//Look at and consume next token
void eatToken(lexer* l, token* t);

void destoryLexer(lexer** l);