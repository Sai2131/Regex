#include "Lexer.h"
#define MAXLEN 1024

lexer* makeLexer(char* regex){

    if(strlen(regex) > MAXLEN){
        return NULL;
    }

    lexer* l = malloc(sizeof(lexer));
    l->input = regex;
    l->position = 0;
    return l;
}

void eatToken(lexer* l, token *t){
    char nextChar = l->input[l->position];
    l->position++;
    t->symbol = nextChar;
    if(nextChar == '|'){
        t->type = UNION;
        return;
    }
    if(nextChar == '.'){
        t->type = DOT;
        return;
    }
    if(nextChar == '\\'){
        nextChar = l->input[l->position];
        l->position++;
        t->symbol = nextChar;
        t->type = SYMBOL;
        return;
    }
    if(nextChar == '*'){
        t->type = KLEENE;
        return;
    }
    if(nextChar == '('){
        t->type = LPAREN;
        return;
    }
    if(nextChar == ')'){
        t->type = RPAREN;
        return;
    }
    if(nextChar == '\0'){
        t->type = END;
        l->position--;
        return;
    }

    t->type = SYMBOL;
    return;
}

void nextToken(lexer* l, token* t){
    char nextChar = l->input[l->position];
    t->symbol = nextChar;
    if(nextChar == '|'){
        t->type = UNION;
        return;
    }
    if(nextChar == '.'){
        t->type = DOT;
        return;
    }
    if(nextChar == '\\'){
        nextChar = l->input[l->position+1];
        t->symbol = nextChar;
        t->type = SYMBOL;
        return;
    }
    if(nextChar == '*'){
        t->type = KLEENE;
        return;
    }
    if(nextChar == '('){
        t->type = LPAREN;
        return;
    }
    if(nextChar == ')'){
        t->type = RPAREN;
        return;
    }
    if(nextChar == '\0'){
        t->type = END;
        return;
    }

    t->type = SYMBOL;
    return;
}

void destoryLexer(lexer** l){
    free(*l);
    *l = NULL;
}
