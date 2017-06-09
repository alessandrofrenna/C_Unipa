#include "item.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int main () {
    Item array[9] = {7, 14, 13, 16, 10, 12, 5, 6, 4};
    Tree broot = initTree();

    
    for (int i = 0; i < 9; i++){
        insertChild(&broot, array[i]);
    }

    puts("Pretty Tree:");
    puts("");
    puts("");
    prettyTree(broot);
    puts("");
    puts("Search for the element: 11");
    Tree result = NULL;
    result = searchElement(broot, 11);
    if(result) {
        puts("It was found!");
        printf("Found after %d %s!\n",getCounter(), getCounter() == 1? "try": "tries");
    } else {
        puts("Not found");
        printf("Not found after %d tries!\n", getCounter());
    }

    Tree min = minNode(broot);
    if(min) {
        printf("The minimum node was found. It is: ");
        displayNode(min);
    } else {
        puts("No minimum node found");
    }

    Tree max = maxNode(broot);
    if(max) {
        printf("The maximum node was found.");
        displayNode(max);
    } else {
        puts("No maximum node found");
    }  

    puts("\nDeleting the root of the tree");
    puts("Deleting the element 4 of the tree");
    puts("Deleting the element 12 of the tree");
    puts("Deleting the element 5 of the tree");
    puts("Deleting the element 14 of the tree");
    puts("Deleting the element 10 of the tree");
    puts("Deleting the element 13 of the tree");
    puts("Deleting the element 16 of the tree");
    puts("Deleting the element 6 of the tree");
    deleteNode(&broot, 7);
    
    deleteNode(&broot, 4);

    deleteNode(&broot, 12);
    deleteNode(&broot, 5);
    deleteNode(&broot, 14);   
    deleteNode(&broot, 10);
    deleteNode(&broot, 13);
    deleteNode(&broot, 16); 
    deleteNode(&broot, 6);          
    puts("\nRearrengerd Tree: ");
    prettyTree(broot);
    puts("");
    
}