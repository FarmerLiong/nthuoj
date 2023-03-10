#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    char letter;
    struct _node *next, *prev;
} node;
node* dummyHead = NULL;
int pos, createdLen;

node* createNode(char input, node** curNode){
    node* head = *curNode;
    node* newNode = (node*)malloc(sizeof(node));
    newNode->letter = input;
    newNode->prev = head;
    if(pos == createdLen){
        newNode->next = dummyHead;
        dummyHead->prev = newNode;
        head->next = newNode;
    }
    else{
        newNode->next = head->next;
        newNode->next->prev = newNode;
        head->next = newNode;
    }
    pos++; createdLen++;
    head = newNode;
    return head;
} 

node* deleteNode(node** curNode){
    node* head = *curNode;

    node* tmp = head;
    head->next->prev = head->prev;
    head->prev->next = head->next;
    head = head->prev;
    free(tmp);

    return head;
}

void printNode(){
    int i = createdLen;
    node* head = NULL;
    if(i) head = dummyHead->next;
    else return;

    while(i--){
        printf("%c", head->letter);
        head = head->next;
        free(head->prev);
    }
    puts("");

}

int main(){
    dummyHead = (node*)malloc(sizeof(node));
    dummyHead->next = dummyHead->prev = dummyHead;

    int T;
    scanf("%d", &T);
    while(T--){
        node* curNode = dummyHead;
        pos = createdLen = 0;
        int len;
        char input;
        scanf("%d", &len);
        
        for(int i = 0; i < len; i++){
            scanf(" %c", &input);
            if(input == 'B'){
                curNode = deleteNode(&curNode);
                pos--; createdLen--;
            }
            else if(input == 'L'){
                pos--;
                curNode = curNode->prev;
            }
            else if(input == 'R'){
                pos++;
                curNode = curNode->next;
            }
            else {
                curNode = createNode(input, &curNode);
            }
        }
        printNode();
    }
    return 0;
}