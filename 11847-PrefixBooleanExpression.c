#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 

typedef struct _node{
    char data;
    struct _node *left, *right;
} BTnode;

int numVar = 0b0000;
int isRightOp = 0, prths = 0;

void printBT(BTnode* root){
    if(root != NULL){
        int havP = 0;
        if(root->left != NULL){
            if(isRightOp && isRightOp != prths){
                havP = 1; prths++;
                putchar('(');
            }
            printBT(root->left);
        }
        putchar(root->data);
        if(root->right != NULL){
            if(root->right->data == '&' || root->right->data == '|'){
                isRightOp += 1;
            }
            printBT(root->right);
            if(havP && prths > 0){
                havP = 0; prths--; isRightOp--;
                putchar(')');
            }
        }

    }
}

void calcBT(BTnode* root){
    
}

BTnode* makeBT(){
    char c; 
    BTnode* root = (BTnode*)malloc(sizeof(BTnode));
    
    c = getchar();
    root->data = c;
    root->left = root->right = NULL;

    if(c >= 'A' && c <= 'D'){
        numVar = numVar | (1 << (c - 'A'));
    }
    else if(c == '&' || c == '|'){
        root->left = makeBT();
        root->right = makeBT();
    }
    else{
        assert(!"undefined c");
    }
    return root;
}

int main(){
    BTnode* root = makeBT();
    printBT(root);
    printf("\n%d", numVar);
    return 0;
}