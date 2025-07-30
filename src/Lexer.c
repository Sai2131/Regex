#include "Lexer.h"

lexer* makeLexer(char* regex){
    lexer* l = malloc(sizeof(lexer));

    if(l == NULL){
        return NULL;
    }

    l->input = regex;
    l->position = 0;
    return l;
}


int eatToken(lexer* l, token *t){
    char nextChar = l->input[l->position];
    l->position++;
    t->symbol = nextChar;
    if(nextChar == '|'){
        t->type = UNION;
        return 1;
    }
    if(nextChar == '.'){
        t->type = DOT;
        return 1;
    }
    if(nextChar == '\\'){
        nextChar = l->input[l->position];
        if(nextChar == '\0'){
            return -1;
        }
        l->position++;
        t->symbol = nextChar;
        t->type = SYMBOL;
        return 1;
    }
    if(nextChar == '*'){
        t->type = KLEENE;
        return 1;
    }
    if(nextChar == '('){
        t->type = LPAREN;
        return 1;
    }
    if(nextChar == ')'){
        t->type = RPAREN;
        return 1;
    }
    if(nextChar == '\0'){
        t->type = END;
        l->position--;
        return 1;
    }

    t->type = SYMBOL;
    return 1;
}

int nextToken(lexer* l, token* t){
    char nextChar = l->input[l->position];
    t->symbol = nextChar;
    if(nextChar == '|'){
        t->type = UNION;
        return 1;
    }
    if(nextChar == '.'){
        t->type = DOT;
        return 1;
    }
    if(nextChar == '\\'){
        nextChar = l->input[l->position+1];
        if(nextChar == '\0'){
            return -1;
        }
        t->symbol = nextChar;
        t->type = SYMBOL;
        return 1;
    }
    if(nextChar == '*'){
        t->type = KLEENE;
        return 1;
    }
    if(nextChar == '('){
        t->type = LPAREN;
        return 1;
    }
    if(nextChar == ')'){
        t->type = RPAREN;
        return 1;
    }
    if(nextChar == '\0'){
        t->type = END;
        return 1;
    }

    t->type = SYMBOL;
    return 1;
}

void destoryLexer(lexer** l){
    free(*l);
    *l = NULL;
}
