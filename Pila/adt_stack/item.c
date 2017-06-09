#include "item.h"
#include <stdio.h>

void insertItem (Item *value) {
    printf("Insert a int value: ");
    scanf("%d", value);
}

void displayItem (const Item value) {
    printf("The value that was set is %d\n", value);
}