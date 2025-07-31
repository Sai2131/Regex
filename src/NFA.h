#include <string.h>
#include <stdlib.h>
#include "Parser.h"

typedef struct Transition {
    int symbols[128];
    int isEpsilon;
} Transition;

typedef struct NFA {
    int numStates;
    
    //2D matrix where NULL means no edge, otherwise the ith row and jth col correspond to the ith state connected to jth state
    Transition*** TransitionsMatrix;
    int startStateId;

    int acceptingStateId; 
} NFA;

//Convert a regular expression to NFA
NFA* Regex2NFA(Parse* p);

//Check if NFA accepts a string
int Acceptance(NFA* A, char* input);

//Helpers to convert regex to NFA
NFA* UnionNFA(NFA* A, NFA* B);

NFA* ConcatNFA(NFA* A, NFA* B);

NFA* KleeneNFA(NFA* A);

NFA* SymbolNFA(Node* ast);

NFA* AST2NFA(Node* ast);

void destoryNFA(NFA** n);

void printNFA(NFA* n);