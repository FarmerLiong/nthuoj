#include <stdio.h>
#include <stdlib.h>
typedef struct _Node{
    int number, age;
    struct _Node* prev;
    struct _Node* next;
}Node;

Node* head;
Node* ageList[500001];  //Array of Node ptr

int cmp(const void* A, const void* B){
    Node* a = *(Node**)A; 
    Node* b = *(Node**)B;

    if(a->age != b->age) return (a->age - b->age); 
    else return (a->number - b->number); 
}

Node* createList(int n){    //circular doubly linked list
    Node* nodeList = (Node*)malloc(sizeof(Node) * n); 

    for(int i = 0; i < n; i++){
        scanf("%d", &nodeList[i].age);
        nodeList[i].number = i + 1;

        ageList[i] = &nodeList[i];

        nodeList[i].next = (i == n-1 ? &nodeList[0] : &nodeList[i+1]);
        nodeList[i].prev = (i == 0 ? &nodeList[n-1] : &nodeList[i-1]);
    }

    qsort(ageList, n, sizeof(Node*), cmp);

    return nodeList;
}

Node* solve(int n, int m){
    char dir;
    int idthAge, posCnt;    

    for(int i = 0; i < m; i++){
        scanf("%d %d %c", &idthAge, &posCnt, &dir);
        posCnt %= (n-1);     // n-1 steps back to origin
        if(!posCnt) continue;
        // if(dir == 'L')  posCnt = n - 1 - posCnt;    //one dir // TLE...
        
        Node* cur = ageList[idthAge - 1];
        Node* target = cur;
        target->prev->next = target->next;
        target->next->prev = target->prev;

        if(dir == 'R'){
            while(posCnt--) cur = cur->next;
            target->next = cur->next;
            target->prev = cur;
            cur->next->prev = target;
            cur->next = target;
        }
        else{
            while(posCnt--) cur = cur->prev;
            target->prev = cur->prev;
            target->next = cur;
            cur->prev->next = target;
            cur->prev = target;
        }
    }
    return ageList[0];
}


int main(){

    int n, k;

    scanf("%d%d", &n, &k);
    head = createList(n);
    Node *p = solve(n, k);  // solve(n,k)
    for(int i = 0; i < n; i ++){
        printf("%d [%d]\n", p -> age, p -> number);
        p = p -> next;
    }
    printf("\n");
    return 0;
}

