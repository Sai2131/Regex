#include "NFA.h"

int main(){

    NFA* n = Regex2NFA("a|b");

    printNFA(n);

    return 0;
}

NFA* Regex2NFA(char* regex){
    Node* ast = parse(regex);
    return AST2NFA(ast);
}

NFA* AST2NFA(Node* ast){
    if(ast->type == CHOICE){
        return UnionNFA(AST2NFA(ast->left), AST2NFA(ast->right));
    }
    if(ast->type == CONCAT){
        return ConcatNFA(AST2NFA(ast->left), AST2NFA(ast->right));
    }
    if(ast->type == STAR){
        return KleeneNFA(AST2NFA(ast->left));
    }
    if(ast->type == LEAF){
        return SymbolNFA(ast->sym);
    }

    printf("Error making nfa");
}

NFA* UnionNFA(NFA* A, NFA* B){
    NFA* n = malloc(sizeof(NFA));

    n->numStates = A->numStates + B->numStates + 1;

    n->startStateId = 0;
    n->acceptingStateId = n->numStates-1;

    n->TransitionsMatrix = calloc(n->numStates, sizeof(Transition*));
    for(int i = 0; i<n->numStates; i++){
        n->TransitionsMatrix[i] = calloc(n->numStates, sizeof(Transition*));
    }

    for(int i = 0; i<A->numStates; i++){
        for(int j = 0; j<A->numStates; j++){
            if(A->TransitionsMatrix[i][j] != NULL){
                n->TransitionsMatrix[i][j] = calloc(1, sizeof(Transition));
                n->TransitionsMatrix[i][j]->isEpsilon = A->TransitionsMatrix[i][j]->isEpsilon;
                for(int k = 0; k < 128; k++){
                    n->TransitionsMatrix[i][j]->symbols[k] = A->TransitionsMatrix[i][j]->symbols[k];
                }
            }
        }
    }

    int offset = A->numStates;
    for(int i = 0; i<B->numStates; i++){
        for(int j = 0; j<B->numStates; j++){
            if(B->TransitionsMatrix[i][j] != NULL){
                n->TransitionsMatrix[i+offset][j+offset] = calloc(1, sizeof(Transition));
                n->TransitionsMatrix[i+offset][j+offset]->isEpsilon = B->TransitionsMatrix[i][j]->isEpsilon;
                for(int k = 0; k < 128; k++){
                    n->TransitionsMatrix[i+offset][j+offset]->symbols[k] = B->TransitionsMatrix[i][j]->symbols[k];
                }
            }
        }
    }

    n->TransitionsMatrix[A->acceptingStateId][n->acceptingStateId] = calloc(1, sizeof(Transition));
    n->TransitionsMatrix[A->acceptingStateId][n->acceptingStateId]->isEpsilon = true;

    n->TransitionsMatrix[B->acceptingStateId+offset][n->acceptingStateId] = calloc(1, sizeof(Transition));
    n->TransitionsMatrix[B->acceptingStateId+offset][n->acceptingStateId]->isEpsilon = true;

    n->TransitionsMatrix[n->startStateId][B->startStateId+offset] = calloc(1, sizeof(Transition));
    n->TransitionsMatrix[n->startStateId][B->startStateId+offset]->isEpsilon = true;

    return n;

}

NFA* ConcatNFA(NFA* A, NFA* B){

    NFA* n = malloc(sizeof(NFA));

    n->numStates = A->numStates + B->numStates;

    n->startStateId = 0;
    n->acceptingStateId = n->numStates-1;

    n->TransitionsMatrix = calloc(n->numStates, sizeof(Transition*));
    for(int i = 0; i<n->numStates; i++){
        n->TransitionsMatrix[i] = calloc(n->numStates, sizeof(Transition*));
    }

    for(int i = 0; i<A->numStates; i++){
        for(int j = 0; j<A->numStates; j++){
            if(A->TransitionsMatrix[i][j] != NULL){
                n->TransitionsMatrix[i][j] = calloc(1, sizeof(Transition));
                n->TransitionsMatrix[i][j]->isEpsilon = A->TransitionsMatrix[i][j]->isEpsilon;
                for(int k = 0; k < 128; k++){
                    n->TransitionsMatrix[i][j]->symbols[k] = A->TransitionsMatrix[i][j]->symbols[k];
                }
            }
        }
    }

    int offset = A->numStates;
    for(int i = 0; i<B->numStates; i++){
        for(int j = 0; j<B->numStates; j++){
            if(B->TransitionsMatrix[i][j] != NULL){
                n->TransitionsMatrix[i+offset][j+offset] = calloc(1, sizeof(Transition));
                n->TransitionsMatrix[i+offset][j+offset]->isEpsilon = B->TransitionsMatrix[i][j]->isEpsilon;
                for(int k = 0; k < 128; k++){
                    n->TransitionsMatrix[i+offset][j+offset]->symbols[k] = B->TransitionsMatrix[i][j]->symbols[k];
                }
            }
        }
    }

    n->TransitionsMatrix[A->acceptingStateId][B->startStateId+offset] = calloc(1, sizeof(Transition));
    n->TransitionsMatrix[A->acceptingStateId][B->startStateId+offset]->isEpsilon = true;
    
    return n;
}

NFA* KleeneNFA(NFA* A){

    A->TransitionsMatrix[A->acceptingStateId][A->startStateId] = calloc(1, sizeof(Transition));
    A->TransitionsMatrix[A->acceptingStateId][A->startStateId]->isEpsilon = true;
    return A;
}

NFA* SymbolNFA(char c){
    NFA* n = malloc(sizeof(NFA));

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
    n->TransitionsMatrix[1][2]->symbols[(int)c] = 1;

    n->TransitionsMatrix[2][3] = calloc(1, sizeof(Transition));
    n->TransitionsMatrix[2][3]->isEpsilon = true;

    return n;
}

void printNFA(NFA* n){

    printf("(  )");
    for(int i = 0; i<n->numStates; i++)
        printf("{%2d}", i);
    printf("\n");

    for(int i = 0; i< n->numStates; i++){
        printf("{%2d}", i);
        for(int j = 0; j< n->numStates; j++){
            if(n->TransitionsMatrix[i][j] == NULL){
                printf("[  ]");
            }
            else if(n->TransitionsMatrix[i][j]->isEpsilon){
                printf("[ $]");
            }
            else{
                for(int x = 0; x < 128; x++){
                    if(n->TransitionsMatrix[i][j]->symbols[x] == 1){
                        printf("[%2c]", x);
                    }
                }
            }
        }
        printf("\n");
    }

    printf("Start state %d\n", n->startStateId);
    printf("Accepting state %d\n", n->acceptingStateId);
}
