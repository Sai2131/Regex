#include "../include/cRegex.h"
#include "NFA.h"

typedef struct regex {
    bool matched;
    int numGroups;
    int* groupStart;
    int* groupLen;
    NFA* nfa;
} regex;

int quickFullMatch(char* regExpr, char* str){
    NFA* n = Regex2NFA(regExpr);
    bool match = Acceptance(n, str);
    destoryNFA(&n);
    return match;
}