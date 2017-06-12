#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
    int data;
    struct node * next;
};

typedef struct node List;
typedef List * ListPtr;

void listAdd(ListPtr *head, int element);
void emptyList(ListPtr *head);
void printList(const ListPtr head);
void printBackList(const ListPtr const head);
ListPtr mergeLists(ListPtr *first, ListPtr *second);
void invertList(ListPtr *ptr);
ListPtr mergeOptimus(ListPtr first, ListPtr second);

int main() {
    ListPtr head = NULL, second = NULL;
    
    listAdd(&head, 1);
    listAdd(&head, 3);
    listAdd(&head, 6);
    listAdd(&second, 2);
    listAdd(&second, 4);
    listAdd(&second, 5);
    
    puts("First List:");
    printList(head);
    puts("Second List:");
    printList(second);
    
    puts("Merged Lists:");
    ListPtr merged = NULL;
    merged = mergeOptimus(head, second);
    printList(merged);
    
    puts("First List after merge:");
    printList(head);
    puts("Second List after merge:");
    printList(second);
    
    emptyList(&head);
    emptyList(&second);
    emptyList(&merged);
}

void listAdd(ListPtr *head, int element) {
    ListPtr new = NULL;
    
    new = malloc(sizeof(List));
    
    if(!new){
        return;
    } else {
        new->data = element;
        new->next = NULL;
        
        ListPtr prec = NULL, curr = *head;

        while(curr && element > curr->data){
            prec = curr;
            curr = curr->next;
        }

        if(!prec){
            new->next = *head;
            *head = new;
        } else {
            prec->next = new;
            new->next = curr;
        }
    }
    
}

void emptyList(ListPtr *head) {
    if(!*head){
        return;
    }
    
    ListPtr temp = *head;
    *head = (*head)->next;
    free(temp);
    emptyList(&*head);
}

void printList(const ListPtr head) {
    if(!head){
        return;
    } else {
        if(head->next) {
            printf("%d -> ", head->data);
        } else {
            printf("%d -> NULL\n\n", head->data);
        }
        printList(head->next);
    }
}

void printBackList(const ListPtr const head) {
    if(!head){
        return;
    } else {
        printBackList(head->next);
        printf("-> %d ", head->data);
    }
    puts("");
}

ListPtr mergeLists(ListPtr *first, ListPtr *second) {
    ListPtr tempList = NULL, list1 = *first, list2 = *second, third = NULL;
    
    tempList = malloc(sizeof(List));
    
    tempList->next = NULL;
    
    third = tempList;
    
    if(!tempList){
        emptyList(&third);
        return NULL;
    }
    
    while(list1 && list2){
        if(list1->data <= list2->data) {
            tempList->data = list1->data;
            list1 = list1->next;
        } else {
            tempList->data = list2->data;
            list2 = list2->next;
        }
        
        tempList->next = malloc(sizeof(List));
        
        if(!tempList->next){
            emptyList(&third);
            return NULL;
        }
        
        tempList = tempList->next;
        tempList->next = NULL;
    }
    
    if(list1 == NULL) {
        tempList->data = list2->data;
        while(list2 = list2->next) {
            tempList->next = malloc(sizeof(List));
            if(!tempList->next) {
                emptyList(&third);
                return NULL;
            }
            tempList = tempList->next;
            tempList->data = list2->data;
            tempList->next = NULL;
        }
    } else {
        tempList->data = list1->data;
        while(list1 = list1->next) {
            tempList->next = malloc(sizeof(List));
            if(!tempList->next) {
                emptyList(&third);
                return NULL;
            }
            tempList = tempList->next;
            tempList->data = list1->data;
            tempList->next = NULL;
        }
    }
    return third;
    
}

void invertList(ListPtr *ptr) {
    if(!*ptr){
        return;
    }
    ListPtr prec = NULL, curr = NULL;
    
    while(*ptr) {
        curr = *ptr;
        *ptr = (*ptr)->next;
        curr->next = prec;
        prec = curr;
    }
    
    *ptr = prec;
    
}

ListPtr mergeOptimus(ListPtr first, ListPtr second) {
    List third;
    ListPtr tempPtr = &third;
    
    while(first && second) {
        if(first->data <= second->data) {
            tempPtr->next = first;
            tempPtr = first;
            first = first->next;
        } else {
            tempPtr->next = second;
            tempPtr = second;
            second = second->next;
        }
    }
    
    tempPtr->next = (first == NULL) ? second : first;
    return third.next;
    
}