#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *nextPtr;
};

typedef struct node QueueNode;
typedef QueueNode * QueueNodePtr;

//prototypes:
void enqueue (QueueNodePtr *headPtr, QueueNodePtr *tailPtr, int value);
int dequeue (QueueNodePtr *headPtr, QueueNodePtr *tailPtr);
int queueIsEmpty (const QueueNodePtr const pointer);
void flushQueue (QueueNodePtr *headPtr, QueueNodePtr *tailPtr);
void print_queue (QueueNodePtr pointer);
void instructions ();

int main() {
    QueueNodePtr head = NULL, tail = NULL;
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
                printf("%s", "\nInsert a value to enqueue: ");
                scanf("%d", &value);
                enqueue(&head, &tail, value);
                break;
            case 2:
                result = dequeue(&head, &tail);
                if (result != -1) {
                    printf("\nThe value %d was dequeued out the queue!\n", result);
                }
                break;
            case 3:
                puts("\nPrinting the queue...");
                print_queue(head);
                break;
            case 4:
                puts("\nClearing the queue...");
                flushQueue(&head, &tail);
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

void enqueue (QueueNodePtr *headPtr, QueueNodePtr *tailPtr, int value) {
    QueueNodePtr new;
    new = malloc(sizeof(QueueNode));
    if(new == NULL) {
        puts("I was not able to enqueue the value, try again later.");
    } else {
        new->data = value;
        new->nextPtr = NULL;

        if(queueIsEmpty(*headPtr)) {
            *headPtr = new;
        } else {
            (*tailPtr)->nextPtr = new;
        }

        *tailPtr = new;
    }
}

int dequeue (QueueNodePtr *headPtr, QueueNodePtr *tailPtr) {
    int value;
    QueueNodePtr temp = NULL;
    if(queueIsEmpty(*headPtr)) {
        puts("Error, unable to dequeue from the head of the queue!\nThe queue you gave me is empty!");
        *tailPtr = NULL;
        return -1;
    } else {
        value = (*headPtr)->data;
        temp = *headPtr;
        *headPtr = (*headPtr)->nextPtr;
        
        if(*headPtr == NULL ){
            *tailPtr = NULL;
        }
        free(temp);
        return value;
    }
}

int queueIsEmpty (const QueueNodePtr const pointer) {
    return pointer == NULL;
}

void flushQueue (QueueNodePtr *headPtr, QueueNodePtr *tailPtr) {
    if(queueIsEmpty(*headPtr)) {
        *tailPtr = NULL;
        puts("Nothing to flush!\nThe queue is already empty!");
    } else {
        QueueNodePtr temp = NULL;
        while(*headPtr != NULL) {
            temp = *headPtr;
            *headPtr = (*headPtr)->nextPtr;
            free(temp);
        }
        *tailPtr = NULL;
        puts("The queue was flushed successfully.");
    }
}

void print_queue (QueueNodePtr pointer) {
    if(!queueIsEmpty(pointer)){
        while(pointer != NULL) {
            printf("%d --> ", pointer->data);
            pointer = pointer->nextPtr;
        }
        printf("NULL\n");
    } else {
        puts("Sorry, nothing to display!\nThe queue you gave me is empty.");
    }
}

void instructions () {
    puts("\nWelcome to queue software: ");
    puts("\nSelect an action:");
    puts("1. Enqueue int;");
    puts("2. Dequeue int;");
    puts("3. Print Queue;");
    puts("4. Flush Queue;");
    puts("5. Exit.");
}