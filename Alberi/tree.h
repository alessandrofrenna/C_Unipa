#include "item.h"
typedef struct node *Tree;

Tree initTree();
void insertChild(Tree *, Item);
void inOrder(const Tree);
void preOrder(const Tree);
void postOrder(const Tree);
void prettyTree(const Tree);
Tree searchElement(const Tree, Item);
Tree minNode(const Tree);
Tree maxNode(const Tree);
void displayNode(const Tree const);
int getCounter();
void deleteNode(Tree *, Item);
void deleteMin(Tree *);