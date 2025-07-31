#include "Lexer.h"
#include "AST.h"

typedef struct Parse{
    char* regex;
    int err;
}Parse;

Node* parse(Parse* p);