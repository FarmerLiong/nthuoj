#include <stdio.h>
#include <stdlib.h>
#define OR -1
#define AND -2

typedef struct _node{
    int val, tokentype;
    struct _node *left, *right, *parent;
} Node;

Node* vars[100001];   //stores the pointers pointing to the tree nodes
Node* root = NULL;
char input[200001];

Node* makeNode(int);
Node* buildBT(Node*);
int calcBT(Node*);

int main(){
    int t, N, M, flip;
    scanf("%d", &t);
    while(t--){
        scanf("%d%d\n", &N, &M);
        root = buildBT(root);
        while(M--){
            scanf("%d", &flip);
            printf("%d\n", calcBT(vars[flip]));
        }
    }
    return 0;
}

int calcBT(Node* cur){
    int res = 0;
    while(cur){
        if(cur->tokentype > 0){
            cur->val = (cur->val ? 0 : 1);
            cur = cur->parent;
        }
        else{
            res = (cur->tokentype == OR) ? 
                (cur->left->val | cur->right->val) : (cur->left->val & cur->right->val);
            if(res == cur->val) return root->val;
            else{
                cur->val = res;
                cur = cur->parent;
            }
        }
    }
    return root->val;
}

Node* makeNode(int id){
    Node* node = (Node*)malloc(sizeof(Node));
    node->tokentype = id;
    node->val = 0;
    node->left = node->right = NULL;

    return vars[id] = node;
}

Node* buildBT(Node* head){
    char c;
    int id;
    static int pos = 0;
    Node* node = NULL;
    if(scanf(" %c", &c) == 1){
        if(c == '|')    node = makeNode(OR);
        else if(c == '&')   node = makeNode(AND);
        else if(c == '['){
            scanf("%d]", &id);
            node = makeNode(id);
        }

        if(c == '|' || c == '&'){
            node->left = buildBT(node);
            node->right = buildBT(node);
        }
        node->parent = head;
    }
    return node;
}