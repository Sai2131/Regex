#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum NODE_TYPES {
    CHOICE,
    STAR,
    CONCAT,
    LEAF
};

typedef struct Node {
    uint8_t type;
    char sym;
    struct Node* left;
    struct Node* right; //Kleene will only use left, right should always be set to null
} Node;

Node* unionNode(Node* l, Node* r);

Node* kleeneNode(Node* l);

Node* concatNode(Node* l, Node* r);

Node* leafNode(char c);

void postOrderPrinter(Node* n);

void inOrderPrinter(Node* n);
