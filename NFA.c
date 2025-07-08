#include "NFA.h"

NFA* Regex2NFA(char* regex){
    Node* ast = parse(regex);
}

NFA* AST2NFA(Node* ast){
    if(ast->type == CHOICE){
        return UnionNFA(AST2NFA(ast->left), AST2NFA(ast->right));
    }
    if(ast->type == CONCAT){
        return ConcatNFA(AST2NFA(ast->left), AST2NFA(ast->right));
    }
    if(ast->type == STAR){
        return KleeneNFA(ast->left);
    }
    if(ast->type == LEAF){
        return SymbolNFA(ast->sym);
    }

    printf("Error making nfa");
}

NFA* KleeneNFA(NFA* A){
    A->TransitionsMatrix[A->acceptingStateId][A->startStateId]->isEpsilon = true;
    return A;
}

NFA* SymbolNFA(char c){
    NFA* n = malloc(sizeof(n));

    n->numStates = 4;

    n->startStateId = 0;
    n->acceptingStateId = 3;

    n->TransitionsMatrix = calloc(4, sizeof(Transition*));
    for(int i = 0; i<4; i++){
        n->TransitionsMatrix[i] = calloc(4, sizeof(Transition*));
    }

    n->TransitionsMatrix[0][1] = calloc(1, sizeof(Transition));
    n->TransitionsMatrix[0][1]->isEpsilon = true;

    n->TransitionsMatrix[1][2] = calloc(1, sizeof(Transition));
    n->TransitionsMatrix[1][2]->isEpsilon = false;
    n->TransitionsMatrix[1][2]->symbols[c] = 1;

    n->TransitionsMatrix[2][3] = calloc(1, sizeof(Transition));
    n->TransitionsMatrix[2][3]->isEpsilon = true;

    return n;
}