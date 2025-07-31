#include <stdlib.h>
#include <string.h>

enum TOKEN_TYPES {
    UNION,
    KLEENE,
    QUANTIFIER,
    LPAREN,
    RPAREN,
    SYMBOL,
    END,
    ERR
};

typedef struct token {
    char allowedSymbol[128];
    int type;
    int quantifierMin;
    int quantifierMax;
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