#include "AST.h"

Node* unionNode(Node* l, Node* r){
    Node* n = malloc(sizeof(Node));
    n->left = l;
    n->right = r;
    n->type = CHOICE;
    return n;
}

Node* kleeneNode(Node* l){
    Node* n = malloc(sizeof(Node));
    n->left = l;
    n->right = NULL;
    n->type = STAR;
    return n;
}

Node* concatNode(Node* l, Node* r){
    Node* n = malloc(sizeof(Node));
    n->left = l;
    n->right = r;
    n->type = CONCAT;
    return n;
}

Node* leafNode(char* c){
    Node* n = malloc(sizeof(Node));
    for(int i = 0; i < 128; i++){
        n->allowedSymbol[i] = c[i];
    }
    n->left = NULL;
    n->right = NULL;
    n->type = LEAF;
    return n;
}
