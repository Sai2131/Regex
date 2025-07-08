#include <stdbool.h>

struct State {
    bool isAccepting;
    int id;
};
typedef struct Node Node;

struct Transitions {
    char* symbols;
    bool isEpsilon;
};
typedef struct Transitions Transitions;

//NFA represented an adj matrix
struct NFA {
    //Array of states with index == id
    State* states;
    
    //2D matrix where NULL means no edge, otherwise the ith row and jth col correspond to the ith state connected to jth state
    Transitions** TransitionsMatrix;
    int startStateId;
};
typedef struct NFA NFA;

//Convert a regular expression to NFA
NFA* Regex2NFA(char* regex);

//Check if NFA accepts a string
bool Acceptance(NFA* A, char* input);

//Helpers to convert regex to NFA
NFA* UnionNFA(NFA* A, NFA* B);

NFA* ConcatNFA(NFA* A, NFA* B);

NFA* KleeneNFA(NFA* A);