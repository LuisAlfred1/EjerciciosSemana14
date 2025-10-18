#ifndef AST_H
#define AST_H

typedef struct Node {
    char *val;
    struct Node *left;
    struct Node *right;
} Node;

Node* mknode(const char *v, Node* l, Node* r);
void printTree(Node* n, int indent);

#endif
