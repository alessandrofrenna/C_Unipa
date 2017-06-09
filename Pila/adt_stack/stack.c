#include "stack.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

struct stack {
    Item data;
    struct stack *nextPtr;
};

static Stack top;

void initStack () {
    top = NULL;
}

void push (Item value) {
    Stack new;
    new = malloc(sizeof(new));
    if(new == NULL) {
        puts("I was not able to push the value, try again later.");
    } else {
        new->data = value;
        new->nextPtr = top;
        top = new;  
    }
}

Item pop () {
    if(stackIsEmpty()) {
        puts("Error, unable to pop from the head of the stack!\nThe stack you gave me is empty.");
        return -1;
    } else {
        Stack temp = top;
        Item value = top->data;
        top = top->nextPtr;
        free(temp);
        return value;
    }
}

int stackIsEmpty () {
    return top == NULL;
}

void flushStack () {
    if(stackIsEmpty()){
        puts("Nothing to flush!\nThe stack is already empty.");
    } else {
        Stack temp = NULL;

        while(top != NULL) {
            temp = top;
            top = top->nextPtr;
            free(temp);
        }
        puts("The stack was flushed successfully.");
    }
}

void printStack () {
    Stack temp = top;
    if(!stackIsEmpty()) {
        while (temp != NULL) {
            printf("%d --> ", temp->data);
            temp = temp->nextPtr;
        }
        printf("NULL");
        puts("");
    } else {
        puts("Sorry, nothing to display!\nThe stack you gave me is empty.");
    }
}