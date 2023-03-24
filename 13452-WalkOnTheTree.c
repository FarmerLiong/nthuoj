#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int parent, left, right;
}BTnode;

int start, end;
BTnode* list;

int find(int cur, int prev){
    if(!cur) return 0;
    
    if(cur == start) return 1;

    if(list[cur].left != prev && find(list[cur].left, cur)){
        printf("P");
        return 1;
    }
    if(list[cur].right != prev && find(list[cur].right, cur)){
        printf("P");
        return 1;

    }
    if(list[cur].parent != prev && find(list[cur].parent, cur)){
        if(list[list[cur].parent].left == cur) printf("L");
        else printf("R");
        return 1;
    }
    return 0;
}

int main(){
    int N, Q, _left, _right;
    scanf("%d", &N);
    list = (BTnode*)malloc(sizeof(BTnode) * (N+1));
    list[1].parent = list[1].left = list[1].right = 0;

    for(int i = 1; i <= N; i++){
        scanf("%d %d", &_left, &_right);
        list[i].left = _left; list[i].right = _right;
        list[_left].parent = list[_right].parent = i;
    }

    scanf("%d", &Q);
    for(int i = 0; i < Q; i++){
        scanf("%d %d", &start, &end);
        find(end, 0);
        puts("");
    }
    return 0;
}