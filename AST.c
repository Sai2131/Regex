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

Node* leafNodeDot(char c){
    Node* n = malloc(sizeof(Node));
    n->sym = c;
    n->left = NULL;
    n->right = NULL;
    n->type = ALL;
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

void postOrderTraversal(Node* n){
    if(n->left != NULL)
        postOrderTraversal(n->left);
    if(n->right != NULL)
        postOrderTraversal(n->right);
    
    printf("%c", n->sym);
}

void postOrderPrinter(Node* n){
    printf("AST (Post Order):");
    postOrderTraversal(n);
    printf("\n");
}

void inOrderTraversal(Node* n){
    if(n->left != NULL)
        inOrderTraversal(n->left);

    printf("%c", n->sym);

    if(n->right != NULL)
        inOrderTraversal(n->right);
}

void inOrderPrinter(Node* n){
    printf("AST (In Order):");
    inOrderTraversal(n);
    printf("\n");
}

