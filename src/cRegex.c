#include "../include/cRegex.h"
#include "NFA.h"

typedef struct regex {
    int matched;
    int numGroups;
    int* groupStart;
    int* groupLen;
    NFA* nfa;
} regex;

int quickFullMatch(char* regExpr, char* str){
    Parse p;
    p.err = 0;
    p.regex = regExpr;

    NFA* n = Regex2NFA(&p);
    if(n == NULL){
        return -1;
    }

    int match = Acceptance(n, str);
    destoryNFA(&n);
    return match;
}

int quickFirstMatch(char* regExpr, char* str){

    int len = strlen(regExpr);
    char wrappedString[len + 5];
    wrappedString[0] = '.';
    wrappedString[1] = '*';
    memcpy(wrappedString + 2, regExpr, len);
    wrappedString[len+2] = '.';
    wrappedString[len+3] = '*';
    wrappedString[len+4] = '\0';

    Parse p;
    p.err = 0;
    p.regex = wrappedString;

    NFA* n = Regex2NFA(&p);
    if(n == NULL){
        return -1;
    }

    int match = Acceptance(n, str);
    destoryNFA(&n);
    return match;
}