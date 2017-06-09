#include "item.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void instructions ();

int main() {
    initStack();
    int choice;
    instructions();

    do {
        printf("%s", "\nMake a choice (1-5): ");
        scanf("%d", &choice);
        getchar();
        
        Item value;
        int result;
        
        switch(choice) {
            case 1:
                insertItem(&value);
                push(value);
                break;
            case 2:
                result = pop();
                if (result != -1) {
                    printf("\nThe value %d was popped out the stack!\n", result);
                }
                break;
            case 3:
                puts("\nPrinting the stack...");
                printStack();
                break;
            case 4:
                puts("\nClearing the stack trace...");
                flushStack();
                break;
            case 5: 
                system("clear");
                puts("\nThank you for using me!\nAborting execution.\n");
                return 0;
            default: puts("Wrong choice was made, retry!\n");
                break;
        }
    } while (choice != 5);
    
    return 0;
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