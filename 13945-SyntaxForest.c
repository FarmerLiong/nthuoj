#include <stdio.h>
#include <stdlib.h>
#define isOP(c) ((c == '+' || c == '-' || c == '*' || c == '/' || c == '@') ? 1 : 0)
#define isfunc(c) ((c >= 'a' && c <= 'z')? 1 : 0)

typedef struct _node{
    char data;
    struct _node *left, *right;
} BTNode;

BTNode* funcHead[27];
char funcExpr[27][205];

long long input[5];    //[0] = 'input of X' ...
long long N, Q, pos;
long long Mod(long long num){
    num %= 998244353;
    if(num < 0) num += 998244353;
    return num;
}
BTNode* createNode(char c){
    BTNode* node = (BTNode*)malloc(sizeof(BTNode));
    node->data = c;
    node->left = node->right = NULL;
    return node;
}

BTNode* createBT(long long idx){
    BTNode* root = NULL;
    char c;
    c = funcExpr[idx][pos++];
    if(isOP(c)){
        root = createNode(c);
        root->left = createBT(idx);
        root->right = createBT(idx);
    }
    else{
        root = createNode(c);
    }
    return root;
}

BTNode* freeBT(BTNode* root){
    if(root != NULL){
        freeBT(root->left);
        freeBT(root->right);
        free(root);
    }
}
long long calcBT(BTNode* root, long long X){  // id op id
    char op = root->data;
    if(op == '+')   return Mod(calcBT(root->left, X) + calcBT(root->right, X));
    else if(op == '-')   return Mod(calcBT(root->left, X) - calcBT(root->right, X));
    else if(op == '*')   return Mod(calcBT(root->left, X) * calcBT(root->right, X));
    else if(op == '/')   return Mod(calcBT(root->left, X) / calcBT(root->right, X));
    else if(op == '@'){
        char f = root->left->data, g = root->right->data;
        if(isfunc(f)){
            return Mod(calcBT(funcHead[f-'a'], Mod(calcBT(root->right, X))));
        }
        else return Mod(calcBT(funcHead[g-'a'], Mod(calcBT(root->left, X))));
    }
    else{
        if(op == 'X') return Mod(X);
        else return Mod(input[op-'A' +1]);
    }
}

int main(){
    char funcName;
    scanf("%d %d", &N, &Q);
    for(int i = 0; i < N; i++){
        scanf(" %c",  &funcName);
        scanf("%s", funcExpr[funcName-'a']);
        pos = 0;
        funcHead[funcName - 'a'] = createBT(funcName - 'a');
    }
    for(int i = 0; i < Q; i++){
        scanf(" %c",  &funcName);
        for(int j = 0; j < 5; j++)  scanf("%lld", &input[j]);
        printf("%lld\n", calcBT(funcHead[funcName - 'a'], Mod(input[0])));
    }
    
    for(int i = 0; i < 27; i++) if(funcHead[i]) freeBT(funcHead[i]);
    free(*funcHead);
    return 0;
}