// y my code so disgusting ;-;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
    int idx, table;
    struct _node *next, *prev;     // upwards
} Node;

Node *books[30], *tables[30]; 
char op[30];
int t;

void returnBooks(int base){
    Node *book = books[base]->next, *cur = NULL;
    while(book){
        tables[book->idx]->prev->next = book;
        book->prev = tables[book->idx]->prev;
        tables[book->idx]->prev = book;
        book->table = book->idx;

        cur = book;
        book = book->next;
        cur->next = NULL;
    }
    books[base]->next = NULL;
    tables[books[base]->table]->prev = books[base];
}

void moveOnto(int a, int b){
    if(books[a]->table == books[b]->table) return;
    returnBooks(a);
    returnBooks(b);
    
    int tableMoved = books[b]->table;

    books[a]->prev->next = NULL;
    tables[books[a]->table]->prev = books[a]->prev;
    books[a]->prev = books[b];
    
    books[b]->next = books[a];
    tables[(tableMoved)]->prev = books[a];
    books[a]->table = tableMoved;
}       

void moveOver(int a, int b){
    if(books[a]->table == books[b]->table) return;
    returnBooks(a);

    int tableMoved = books[b]->table;
    books[a]->prev->next = NULL;
    tables[books[a]->table]->prev = books[a]->prev;
    books[a]->prev = tables[tableMoved]->prev;

    tables[tableMoved]->prev->next = books[a];
    tables[tableMoved]->prev = books[a];
    books[a]->table = tableMoved;
}

void pileOnto(int a, int b){
    if(books[a]->table == books[b]->table) return;
    returnBooks(b);

    int tableMoved = books[b]->table;

    books[a]->prev->next = NULL;
    tables[tableMoved]->prev = tables[books[a]->table]->prev;
    tables[books[a]->table]->prev = books[a]->prev;

    books[a]->prev = books[b];
    books[b]->next = books[a];
    
    Node* cur = books[a];
    while(cur){
        cur->table = tableMoved;
        cur = cur->next;
    }
}

void pileOver(int a, int b){
    if(books[a]->table == books[b]->table) return;

    int tableMoved = books[b]->table;
    Node* cur = books[a]->prev;

    cur->next = NULL;
    tables[tableMoved]->prev->next = books[a];
    books[a]->prev = tables[tableMoved]->prev;
    tables[tableMoved]->prev = tables[books[a]->table]->prev; 
    tables[books[a]->table]->prev = cur;

    cur = books[a];
    while(cur){
        cur->table = tableMoved;
        cur = cur->next;
    }
}


void init(){
    Node *dummy = NULL, *newNode = NULL;
    for(int i = 0; i < t; i++){
        dummy = (Node*)malloc(sizeof(Node));
        dummy->idx = -1;

        newNode = (Node*)malloc(sizeof(Node));
        dummy->next = dummy->prev = newNode;
        newNode->idx = newNode->table = dummy->table = i;
        newNode->next = NULL;
        newNode->prev = dummy;
        
        books[i] = newNode;
        tables[i] = dummy;
    }
}

void show(int id){
    Node *book = tables[id]->next, *cur = NULL;
    while(book){
        printf(" %d", book->idx);
        cur = book;
        book = book->next;
        free(cur);
    }
    free(tables[id]);
} 

int main(){
    scanf("%d\n", &t);
    init();
    while(1){
        int from, to;
        scanf("%s", op);
        if(!strcmp(op, "move")){
            scanf(" %d %s %d", &from, op, &to);
            if(from == to) continue;
            if(!strcmp(op, "onto"))     moveOnto(from, to);
            else if(!strcmp(op, "over"))    moveOver(from, to);
        }
        else if(!strcmp(op, "pile")){
            scanf(" %d %s %d", &from, op, &to);
            if(from == to) continue;
            if(!strcmp(op, "onto"))     pileOnto(from, to);
            else if(!strcmp(op, "over"))    pileOver(from, to);
        }
        else if(!strcmp(op, "exit"))
            break;
    }

    for(int i = 0; i < t; i++){
        printf("%d:", i);
        show(i);
        printf("\n");
    }
    return 0;
}
