#include "stack.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

static Item *stack;
static size_t numbers;
static size_t MAXN = 2;

static void resize (size_t newSize);

void initStack () {
    stack = malloc(MAXN * sizeof(Item));
}

void push (Item value) {
    if(stack == NULL) {
        initStack();
    }
    if(numbers >= MAXN) {
        resize(MAXN = MAXN*2);
    }
    stack[numbers++] = value;
}

Item pop () {
    if(stack != NULL && !stackIsEmpty()){
        if(numbers > 0) {
            if((numbers < MAXN/8) && (numbers > 4)) {
                resize(MAXN = MAXN/2);
            }
            return stack[--numbers];
        }
    } else {
        puts("Error, unable to pop from the head of the stack!\nThe stack you gave me is empty.");
        return  -1;
    }
}

int stackIsEmpty () {
    return numbers == 0;
}

void flushStack () {
    if(stack == NULL && stackIsEmpty()) {
        puts("Nothing to flush!\nThe stack is already empty.");
    } else {
        numbers = 0;
        resize(numbers);
        free(stack);
    }
}

void printStack () {
    
    if(stack != NULL && !stackIsEmpty()) {
        for(size_t temp = numbers - 1 ; temp > 0; temp--){
            displayItem(stack[temp]);
            printf("-->");
        }
            
        printf(" %d --> NULL\n", stack[0]);
    } else {
        puts("Sorry, nothing to display!\nThe stack you gave me is empty.");
    }
}

static void resize (size_t newSize) {
    stack = realloc(stack, newSize*sizeof(Item));
}