#include "item.h"
#include <stdio.h>

Item insertValue(){
    Item temp = 0;
    printf("Insert item: ");
    scanf("%d", &temp);
    getchar();
    return temp;
}

void displayValue(const Item item){
    printf("The item is: %d\n", item);
}