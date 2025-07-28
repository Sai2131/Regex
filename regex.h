#include "NFA.h"

typedef struct regex {
    bool matched;
    int numGroups;
    int* groupStart;
    int* groupLen;
    NFA* nfa;
} regex;

regex* compile(char* regExpr);

void firstMatch(regex* r, char* str);

void fullMatch(regex* r, char* str);

void freeRegex(regex** r);

bool quickFullMatch(char* regExpr, char* str);

bool quickFirstMatch(char* regExpr, char* str);

