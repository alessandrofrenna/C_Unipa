#include "item.h"
#include <stdio.h>

void insertItem (Item *value) {
    printf("Insert a int value: ");
    scanf("%d", value);
}

void displayItem (Item value) {
    printf("%d", value);
}