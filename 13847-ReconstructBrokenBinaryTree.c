#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node{
    int id, level;
    struct _node *left, *right;
} Node;

Node* root;
int N, *pairs, *pos, *inorder;

void printPrefix(Node*);
Node* makeNode(int);
Node* buildBT(int);
int main(){
    scanf("%d", &N);
    int a, b, rootid;
    int numPairs = (N-1)/2;
    inorder = (int*)malloc(sizeof(int) * (N + 1));
    pos = (int*)malloc(sizeof(int) * (N + 1));
    pairs = (int*)malloc(sizeof(int) * (N + 1));
    memset(pairs, 0, sizeof(int) * (N + 1));
    
    for(int i = 0; i < N; i++){
        scanf("%d", &a);
        pos[a] = i;
        inorder[i] = a;
    }
    for(int i = 0; i < numPairs; i++){
        scanf("%d%d", &a, &b);
        pairs[a] = b; pairs[b] = a;
    }
    for(int i = 0; i < N; i++){
        if(!pairs[inorder[i]]){
            rootid = inorder[i];
            break;
        }
    }
    root = buildBT(rootid);
    printPrefix(root);
    return 0;
}

void printPrefix(Node* head){
    if(head){
        printf("%d%c", head->id, " \n"[head->id == inorder[N-1]]);
        printPrefix(head->left);
        printPrefix(head->right);
    }
    free(head);
}

Node* makeNode(int ID){
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = ID;
    node->left = node->right = NULL;
    return node;
}

Node* buildBT(int rootid){
    Node* node = NULL;
    node = makeNode(rootid);
    if(!pos[rootid] || pos[rootid] == N-1) return node;
    
    int a, b;
    a = inorder[pos[rootid] - 1]; 
    b = pairs[a];
    if(!pairs[b] && !b) return node;

    if(pos[b] > pos[rootid]){
        pairs[a] = pairs[b] = 0;
        node->left = buildBT(a);
        node->right = buildBT(b);
    }
    else{
        a = inorder[pos[rootid] + 1];
        b = pairs[a];
        pairs[a] = pairs[b] = 0;
        node->left = buildBT(b);
        node->right = buildBT(a);
    }
    return node;
}