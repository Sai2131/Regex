#include "regex.h"


bool matches(char* reg, char* str){
    
    NFA* n = Regex2NFA(reg);
    return Acceptance(n, str);
}