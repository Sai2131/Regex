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

void eatToken(lexer* l, token *t){
    char nextChar = l->input[l->position];
    l->position++;

    memset(t->allowedSymbol, 0, sizeof t->allowedSymbol);
    t->quantifierMax = t->quantifierMin = -1;
    t->type = ERR;

    if(nextChar == '|'){
        t->type = UNION;
        return;
    }
    if(nextChar == '.'){
        for(int i = 0; i<128; i++){
            t->allowedSymbol[i] = 1;
        }
        t->type = SYMBOL;
        return;
    }
    if(nextChar == '\\'){
        nextChar = l->input[l->position];
        if(nextChar == '\0'){
            t->type = ERR;
            t->allowedSymbol['\0'] = 1;
            return;
        }
        l->position++;
        t->allowedSymbol[(int)nextChar] = 1;
        t->type = SYMBOL;
        return;
    }
    if(nextChar == '*'){
        t->type = KLEENE;
        t->quantifierMax = INT32_MAX;
        t->quantifierMin = 0;
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
    if(nextChar == '['){
        //Need to fix later, really bad solution for now
        t->type = SYMBOL;
        while(1){
            nextChar = l->input[l->position];
            if(nextChar == ']'){
                break;
            }
            if(nextChar == '-'){
                if( l->input[l->position-1] != '-' &&
                    l->input[l->position-1] != '[' && 
                    l->input[l->position+1] != '-' &&
                    l->input[l->position+1] != ']'  ){
                    for(char c = l->input[l->position-1]; c <= l->input[l->position+1]; c++){
                        t->allowedSymbol[(int)c] = 1;
                    }
                }
            }
            else{
                t->allowedSymbol[(int)nextChar] = 1;
            }
            l->position++;
        }
        l->position++;
        return;
    }

    t->type = SYMBOL;
    t->allowedSymbol[(int)nextChar] = 1;
    return;
}

void nextToken(lexer* l, token* t){
    char nextChar = l->input[l->position];

    memset(t->allowedSymbol, 0, sizeof t->allowedSymbol);
    t->quantifierMax = t->quantifierMin = -1;
    t->type = ERR;

    if(nextChar == '|'){
        t->type = UNION;
        return;
    }
    if(nextChar == '.'){
        for(int i = 0; i<128; i++){
            t->allowedSymbol[i] = 1;
        }
        t->type = SYMBOL;
        return;
    }
    if(nextChar == '\\'){
        nextChar = l->input[l->position+1];
        if(nextChar == '\0'){
            t->type = ERR;
            t->allowedSymbol['\0'] = 1;
            return;
        }
        t->allowedSymbol[(int)nextChar] = 1;
        t->type = SYMBOL;
        return;
    }
    if(nextChar == '*'){
        t->type = KLEENE;
        t->quantifierMax = INT32_MAX;
        t->quantifierMin = 0;
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
    if(nextChar == '['){
        t->type = SYMBOL;
        return;
    }

    t->type = SYMBOL;
    t->allowedSymbol[(int)nextChar] = 1;
    return;
}

void destoryLexer(lexer** l){
    free(*l);
    *l = NULL;
}
