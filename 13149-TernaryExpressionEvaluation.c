#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int id;
    struct _node *left, *right;
} Node;

char val[3002];
Node* root;

Node* buildBT();
Node* makeNode(int);
int eval(Node*);

int main(){
    int t;
    root = buildBT();
    scanf("%d", &t);
    while(t--){
        scanf("%s", val + 1);
        printf("%d\n", eval(root));
    }
    return 0;
}

int eval(Node* head){
    if(!head->left || !head->right) return (val[head->id] - '0');
    return (val[head->id] - '0') ? eval(head->left) : eval(head->right);
}

Node* makeNode(int ID){
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = ID;
    node->left = node->right = NULL;
    return node;    
}

Node* buildBT(){
    int i;
    char c;
    Node* node = NULL;
    if(scanf("%d", &i) == 1){
        c = getchar();
        node = makeNode(i);
        if(c == '?'){
            node->left = buildBT();
            node->right = buildBT();
        }
    }
    return node;
}