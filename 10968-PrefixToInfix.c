#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

int isRightOp = 0, prths = 0;

void constructTree(Node** head);
void freeTree(Node *root);
void printInfix(Node *root){
    if(root != NULL){
        int havP = 0;
        if(root->left != NULL){
            if(isRightOp && isRightOp != prths){
                havP = 1; prths++;
                putchar('(');
            }
            printInfix(root->left);
        }
        putchar(root->data);
        if(root->right != NULL){
            if(root->right->data == '&' || root->right->data == '|'){
                isRightOp += 1;
            }
            printInfix(root->right);
            if(havP && prths > 0){
                havP = 0; prths--; isRightOp--;
                putchar(')');
            }
        }
    }
}

void constructTree(Node** head){
    char c;

    if((*head)==NULL){
        (*head) = (Node *)malloc(sizeof(Node));
		c = getchar();

		(*head)->data = c;

        (*head)->left = (*head)->right = NULL;

        if((*head)->left == NULL && ((*head)->data=='&' || (*head)->data=='|'))
            constructTree( &(*head)->left);
        if((*head)->right == NULL && ((*head)->data=='&' || (*head)->data=='|'))
            constructTree( &(*head)->right);
    }
}

void freeTree(Node *root){
    if (root!=NULL){
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(void){
    int n;
    scanf("%d", &n);// the number of test cases

    while(n>0){
        getchar();
        Node *root=NULL;
        constructTree(&root);// construct syntax tree
        printInfix(root);// you have to implement this function
        printf("\n");
        freeTree(root);
        --n;
    }

    return 0;
}
