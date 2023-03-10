#include<stdio.h>
#include<stdlib.h>
typedef struct _Node{
    int size;
    int* data;
    struct _Node* next;
} Node;

Node* ReadOneList(){
    Node* list = (Node*)malloc(sizeof(Node));
    scanf("%d: ", &(list->size));
    list->data = (int*)malloc(sizeof(int) * (list->size + 1));
    list->next = NULL;
    for(int i = 0; i < list->size; i++){
        scanf("%d", &list->data[i]);
    }
    return list;
}


void PrintList(Node* head){
    Node* curNode, *tmp = NULL;
    curNode = head->next;

    while(curNode != NULL){
        tmp = curNode;
        for(int i = 0; i < curNode->size; i++){
            printf("%d%c", curNode->data[i], " \n"[i == curNode->size - 1]);
        }
        curNode = curNode->next;
        free(tmp);
    }
    free(curNode);
    
}
void Merge(Node* head, int y, int x){
    if(x == y) return;
    Node *deckX, *deckY, *curNode;
    deckX = deckY = NULL;
    curNode = head; 

    int numTrav = x > y ? x : y; 
    for(int i = 0; i <= numTrav; i++){
        if(i == x)
            deckX = curNode;
        if(i == y - 1){
            deckY = curNode->next;
            curNode->next = curNode->next->next;
            i++;
        }
        curNode = curNode->next;
    }

    int tmpSize = deckX->size + deckY->size;
    int* tmpData = (int*)malloc(sizeof(int) * (tmpSize+1));
    for(int i = 0; i < tmpSize; i++){
        tmpData[i] = i < deckX->size ? deckX->data[i] : deckY->data[i-deckX->size];
    }
    free(deckX->data);
    free(deckY->data); free(deckY);
    deckX->data = tmpData;
    deckX->size = tmpSize;
}

void Cut(Node* head, int x, int cutNum){
    Node *deck = NULL, *curNode = head;
    Node* newDeck = (Node*)malloc(sizeof(Node));
    
    for(int i = 0; i <= x; i++){
        if(i == x) deck = curNode;
        curNode = curNode->next;
    }
    
    int* remainData = (int*)malloc(sizeof(int)* (cutNum + 1));
    int* newData = (int*)malloc(sizeof(int)* (deck->size - cutNum + 1));

    for(int i = 0; i < deck->size; i++){
        if(i < cutNum){
            remainData[i] = deck->data[i];
        }
        else{
            newData[i-cutNum] = deck->data[i];
        }
    }
    newDeck->data = newData;
    free(deck->data); 
    deck->data = remainData;
    newDeck->size = deck->size - cutNum;
    deck->size = cutNum;
    newDeck->next = deck->next;
    deck->next = newDeck;
}

int main(){
    Node* dummy_head;
    Node* tail;

    dummy_head = (Node*) malloc( sizeof(Node) );
    dummy_head->data = NULL;
    dummy_head->size = -1;

    tail = dummy_head;

    int N, M;
    scanf("%d %d", &N, &M);
    for(int i=0; i<N; i++){
        tail->next = ReadOneList();
        tail = tail->next;   
    }
    char act[10];
    int x, y;
    for(int i=0; i<M; i++){
        scanf("%s %d %d", act, &x, &y);
        if( act[0] == 'M' ){
            Merge(dummy_head, x, y);
        }
        else{
            Cut(dummy_head, x, y);
        }
    }
    PrintList(dummy_head);
    return 0;
}
