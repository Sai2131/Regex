#include "regex.h"

bool quickFullMatch(char* regExpr, char* str){
    NFA* n = Regex2NFA(regExpr);
    bool match = Acceptance(n, str);
    destoryNFA(&n);
    return match;
}