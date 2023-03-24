#include <stdio.h>
#include <stdlib.h>
#define isAS(c) ((c == '+' || c == '-') ? 1 : 0)
#define isMD(c) ((c == '*' || c == '/') ? 1 : 0)
#define isSM(c) ((c == '-' || c == '*') ? 1 : 0)
#define isD(c)  ((c == '/') ? 1 : 0)
#define isOP(c) ((c == '+' || c == '-' || c == '*' || c == '/') ? 1 : 0)

typedef struct _node{
    char data;
    struct _node *left, *right;
} BTnode;

BTnode* root;

BTnode* createNode(char c){
    BTnode* node = (BTnode*)malloc(sizeof(BTnode));
    node->data = c;
    node->left = node->right = NULL;
    return node;
}

BTnode* createBT(){
    char c;
    BTnode* node;

    if(scanf(" %c", &c) == 1){
        node = createNode(c);
        if(isOP(c)){
            node->left = createBT();
            node->right = createBT();
        }
    }
    return node;
}

void printInfix(BTnode* root){
    if(root != NULL){
        if(root->left){
            if(isMD(root->data) && isAS(root->left->data)){
                putchar('(');
                printInfix(root->left);
                putchar(')');
            }
            else printInfix(root->left);
        }
        printf("%c", root->data);
        if(root->right){
            if((isSM(root->data) && isAS(root->right->data))
            || (isD(root->data) && isOP(root->right->data))){
                putchar('(');
                printInfix(root->right);
                putchar(')');
            }
            else printInfix(root->right);
        }
    }
}

void freeBT(BTnode* root){
    if(root != NULL){
        freeBT(root->left);
        freeBT(root->right);
        free(root);
    }
}

int main(){
    root = createBT();
    printInfix(root);
    puts("");
    freeBT(root);
    return 0;
}