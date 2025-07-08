#include "AST.h"

Node* unionNode(Node* l, Node* r){
    Node* n = malloc(sizeof(Node));
    n->sym = '|';
    n->left = l;
    n->right = r;
    n->type = CHOICE;
    return n;
}

Node* kleeneNode(Node* l){
    Node* n = malloc(sizeof(Node));
    n->sym = '*';
    n->left = l;
    n->right = NULL;
    n->type = STAR;
    return n;
}

Node* concatNode(Node* l, Node* r){
    Node* n = malloc(sizeof(Node));
    n->sym = '+';
    n->left = l;
    n->right = r;
    n->type = CONCAT;
    return n;
}

Node* leafNode(char c){
    Node* n = malloc(sizeof(Node));
    n->sym = c;
    n->left = NULL;
    n->right = NULL;
    n->type = LEAF;
    return n;
}

void postOrderPrinter(Node* n){
    if(n->left != NULL)
        postOrderPrinter(n->left);
    if(n->right != NULL)
        postOrderPrinter(n->right);
    
    printf("sym: %c\n", n->sym);
}