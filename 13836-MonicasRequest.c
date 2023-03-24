#include <stdlib.h>
#include <stdio.h>
typedef struct _node {
    int value;
    struct _node *left;
    struct _node *right;
} Node;

Node* root;
int *preorder, *inorder, *postorder;
int pos;

// create a new node
Node *create_node(int value){
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}
// free the memory
void destroy(Node *root){
    if(root != NULL){
        destroy(root->left);
        destroy(root->right);
        free(root);
    }
}
// verify whether the postorder is match with the input
int verify(Node *root){

    if(root->left != NULL && !verify(root->left))  return 0;
    if(root->right != NULL && !verify(root->right)) return 0;
    if(root->value != postorder[pos++]) return 0;
    return 1;
}

// build the tree using recursive
Node *build(int rootIdx, int inorder_start, int inorder_end){

    Node* root = create_node(preorder[pos++]);

    for(int i = inorder_start; i < rootIdx; i++){
        if(inorder[i] == preorder[pos]){
            root->left = build(i, inorder_start, rootIdx);
            break;
        }
    }

    for(int i = rootIdx + 1; i < inorder_end; i++){
        if(inorder[i] == preorder[pos]){
            root->right = build(i, rootIdx + 1, inorder_end);
            break;
        }
    }

    return root;
}

int main(){
    int N, Q, rootIdx;
    scanf("%d", &N);
    preorder = (int*)malloc(sizeof(int) * (N+1));
    postorder = (int*)malloc(sizeof(int) * (N+1));
    inorder = (int*)malloc(sizeof(int) * (N+1));
    for(int i = 0; i < N; i++) scanf("%d", &preorder[i]);
    for(int i = 0; i < N; i++) scanf("%d", &postorder[i]);

    scanf("%d", &Q);
    for(int i = 0; i < Q; i++){
        pos = 0;
        for(int j = 0; j < N; j++){
            scanf("%d", &inorder[j]);
            if(inorder[j] == preorder[0]) rootIdx = j;
        }
        root = build(rootIdx, 0, N);
        pos = 0;    
        if(verify(root)) printf("Yes\n");
        else printf("No\n");
        destroy(root);
    }
}