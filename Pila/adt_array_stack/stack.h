#include "item.h"

typedef struct stack *Stack;

void initStack ();
void push (Item);
Item pop ();
int stackIsEmpty ();
void flushStack ();
void printStack ();
