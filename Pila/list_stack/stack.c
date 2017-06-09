#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *nextPtr;
};

typedef struct node StackNode;
typedef StackNode *StackNodePtr;


//prototype:
void push (StackNodePtr *pointer, int value);
int pop (StackNodePtr *pointer);
int stackIsEmpty (StackNodePtr const pointer);
void flushStack (StackNodePtr *pointer); 
void print_stack (StackNodePtr pointer);
void instructions();

int main() {
    StackNodePtr head = NULL;
    int choice;
    instructions();

    do {
        printf("%s", "\nMake a choice (1-5): ");
        scanf("%d", &choice);
        getchar();
        
        int value;
        int result;
        
        switch(choice) {
            case 1:
                printf("%s", "\nInsert a value to push: ");
                scanf("%d", &value);
                push(&head, value);
                break;
            case 2:
                result = pop(&head);
                if (result != -1) {
                    printf("\nThe value %d was popped out the stack!\n", result);
                }
                break;
            case 3:
                puts("\nPrinting the stack...");
                print_stack(head);
                break;
            case 4:
                puts("\nClearing the stack trace...");
                flushStack(&head);
                break;
            case 5: 
                system("clear");
                puts("\nThank you for using me!\nAborting execution.\n");
                return 0;
            default: puts("Wrong choice was made, retry!\n\n");
                break;
        }
    } while (choice != 5);
    
    return 0;
}

void push (StackNodePtr *pointer, int value) {
    StackNodePtr new;
    new = malloc(sizeof(StackNode));
    if(new == NULL) {
        puts("I was not able to push the value, try again later.");
    } else {
        new->data = value;
        new->nextPtr = *pointer;
        *pointer = new;  
    }
}

int pop (StackNodePtr *pointer) {
    StackNodePtr temp = NULL;
    int value;

    if(stackIsEmpty(*pointer)) {
        puts("Error, unable to pop from the head of the stack!\nThe stack you gave me is empty.");
        return -1;
    } else {
        temp = *pointer;
        value = (*pointer)->data;
        *pointer = (*pointer)->nextPtr;
        free(temp);
        return value;
    }
}

int stackIsEmpty (const StackNodePtr const pointer) {
    return pointer == NULL;
}

void flushStack (StackNodePtr *pointer) {
    if(stackIsEmpty(*pointer)){
        puts("Nothing to flush!\nThe stack is already empty.");
    } else {
        StackNodePtr temp = NULL;

        while(*pointer != NULL) {
            temp = *pointer;
            *pointer = (*pointer)->nextPtr;
            free(temp);
        }
        puts("The stack was flushed successfully.");
    }
}

void print_stack (StackNodePtr pointer) {
    if(!stackIsEmpty(pointer)) {
        while (pointer != NULL) {
            printf("%d --> ", pointer->data);
            pointer = pointer->nextPtr;
        }
        printf("NULL");
        puts("");
    } else {
        puts("Sorry, nothing to display!\nThe stack you gave me is empty.");
    }
}

void instructions () {
    puts("\nWelcome to stack software: ");
    puts("\nSelect an action:");
    puts("1. Push int;");
    puts("2. Pop  int;");
    puts("3. Print Stack;");
    puts("4. Flush Stack;");
    puts("5. Exit.");
}
