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