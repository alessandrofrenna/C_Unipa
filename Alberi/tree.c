#include "tree.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

static int level = 0;
static int counter = 0;

struct node {
    struct node *left;
    struct node *right;
    Item data;
};

Tree initTree(){
    Tree root = NULL;
    return root;
}

void insertChild(Tree *root, Item data) {
        if(*root == NULL){
            *root = malloc(sizeof(Tree));

            if(*root) {
                (*root)->data = data;
                (*root)->left = NULL;
                (*root)->right = NULL;
            } else {
                puts("Unable to insert inside tree!");
            }
        } else {
            if((*root)->data > data){
                insertChild(&(*root)->left, data);
            } else if((*root)->data < data){
                insertChild(&(*root)->right, data);
            } else {
                puts("Duplicates are ignored!");
            }
        }
}

void inOrder(const Tree root) {
    if(root) {
        inOrder(root->left);
        printf("%3d", root->data);
        inOrder(root->right);
    }
}

void preOrder(const Tree root) {
    if(root){
        printf("%3d", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(const Tree root) {
    if(root){
        postOrder(root->left);
        postOrder(root->right);
        printf("%3d", root->data);
    }
}

void prettyTree(const Tree root){
    if(root) {
        level++;
        prettyTree(root->right);
        printf(">%*s%5d\n", level*5, "", root->data);
        prettyTree(root->left);
        level--;
    } else puts ("Tree is empty");
}

Tree searchElement(const Tree root, Item element){
    if(!root){
        return NULL;
    }
    counter++;
    if(root){
        if(root->data == element){
            return root;
        }

        if(root->data > element) {
            return searchElement(root->left, element);
        }

        if(root->data < element) {
            return searchElement(root->right, element);
        }
    }

}

Tree minNode(const Tree root){
    if(!root){
        return NULL;
    }

    if(root->left == NULL){
        return root;
    } else {
        return minNode(root->left);
    }
}

Tree maxNode(const Tree root){
    if(!root){
        return NULL;
    }

    if(root->right == NULL){
        return root;
    } else {
        return maxNode(root->right);
    }
}

void displayNode(const Tree const node) {
    if(node) {
        displayValue(node->data);
    }
}

int getCounter(){
    return counter;
}

void deleteNode(Tree *root, Item element){
    if(!*root){
        return;
    }

    Tree temp = NULL;

    if((*root)->data == element){
        if((*root)->left == NULL && (*root)->right == NULL) {
            *root = NULL;
            free(*root);
        } else {
            if((*root)->left == NULL) {
                temp = *root;
                *root = (*root)->right;
                free(temp);
            } else if((*root)->right == NULL){
                temp = *root;
                *root = (*root)->left;
                free(temp);
            } else {
                Tree min = minNode((*root)->right);
                deleteMin(&(*root)->right);
                temp = *root;
                *root = min;
                (*root)->left = temp->left;
                (*root)->right = temp->right;
                free(temp);
            }
        }
    } else if((*root)->data > element){
        deleteNode(&(*root)->left, element);
    } else {
        deleteNode(&(*root)->right, element);
    }

}

void deleteMin(Tree *root){
    if(!*root){
        return;
    }
    Tree temp = NULL;
    if((*root)->left == NULL){
        temp = *root;
        *root = (*root)->right;
        free(temp);
    } else {
        deleteMin(&(*root)->left);
    }
}