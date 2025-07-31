#include <stdlib.h>
#include <stdio.h>

enum NODE_TYPES {
    CHOICE,
    STAR,
    CONCAT,
    LEAF
};

typedef struct Node {
    int type;
    char allowedSymbol[128];
    struct Node* left;
    struct Node* right; //Star is uniary and only uses left, right remains NULL
} Node;

Node* unionNode(Node* l, Node* r);

Node* kleeneNode(Node* l);

Node* concatNode(Node* l, Node* r);

Node* leafNode(char* c);