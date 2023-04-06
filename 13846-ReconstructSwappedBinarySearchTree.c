#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int idx;
    struct _node *left, *right;
} Node;

Node* root;
int N, val[100001];

void printPostfix(Node*);
Node* makeNode(int);
Node* buildBT(int, int);

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++)  scanf("%d", &val[i]);
    root = buildBT(0, N);
    printPostfix(root);
    return 0;
}

void printPostfix(Node* head){
    if(head){
        printPostfix(head->left);
        printPostfix(head->right);
        printf("%d%c", head->idx, " \n"[head == root]);
    }
    free(head);
}

Node* makeNode(int id){
    Node* node = (Node*)malloc(sizeof(Node));
    node->idx = id;
    node->left = node->right = NULL;
    return node;
}

Node* buildBT(int pos, int end){
    Node* node = NULL;
    if(pos >= end) return node;
    node = makeNode(val[pos++]);
    int leftidx = 0, rightidx = 0;

    if(val[pos] > node->idx){
        leftidx = pos;
        for(int i = pos; i < end; i++){
            if(val[i] <= node->idx){
                rightidx = i;
                break;
            }
        }
        if(leftidx >= rightidx) return node;
        node->left = buildBT(rightidx, end);
        node->right = buildBT(leftidx, rightidx);
    }
    else{
        leftidx = pos;
        for(int i = pos; i < end; i++){
            if(val[i] > node->idx){
                rightidx = i;
                break;
            }
        }
        if(leftidx >= rightidx) return node;
        node->right = buildBT(rightidx, end);
        node->left = buildBT(leftidx, rightidx);
    }
    return node;    
}