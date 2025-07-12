#include <stdbool.h>
#include "Parser.h"

typedef struct Transition {
    uint8_t symbols[128];
    bool isEpsilon;
} Transition;

//NFA represented an adj matrix
typedef struct NFA {
    int numStates;
    
    //2D matrix where NULL means no edge, otherwise the ith row and jth col correspond to the ith state connected to jth state
    Transition*** TransitionsMatrix;
    int startStateId;

    int acceptingStateId; //This is a little different from an NFA as there will only be one accepting state
} NFA;

//Convert a regular expression to NFA
NFA* Regex2NFA(char* regex);

//Check if NFA accepts a string
bool Acceptance(NFA* A, char* input);

//Helpers to convert regex to NFA
NFA* UnionNFA(NFA* A, NFA* B);

NFA* ConcatNFA(NFA* A, NFA* B);

NFA* KleeneNFA(NFA* A);

NFA* SymbolNFA(char c);

NFA* AST2NFA(Node* ast);

void printNFA(NFA* n);

void destoryNFA(NFA** n);