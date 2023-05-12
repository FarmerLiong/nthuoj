#include "function.h"
using namespace std;

List_stack::List_stack()
    : head(NULL), tail(NULL) {
} 

List_stack::~List_stack() {
    while (tail->nextPtr != NULL)
    {
        tail = tail->nextPtr;
        delete [] tail->prevPtr;
    } delete [] tail;
    
}

void List_stack::push(const int &n) {
    ListNode* node = new ListNode(n);
    if (head == NULL) {
        tail = head = node;
        tail->prevPtr = NULL;
    } else {
        head->nextPtr = node;
        node->prevPtr = head;
        head = head->nextPtr;
    }
}   

void List_stack::pop() {
    if (head == NULL) return;
    else {
        if (head->prevPtr){
            head = head->prevPtr;
            delete [] head->nextPtr;
            head->nextPtr = NULL;
        } else {
            delete [] head;
            head = NULL;
        }
    }
}   

void List_stack::print() {
    if (head == NULL) {
        return;
    } else {
        for (ListNode* tmp = head; tmp != NULL; tmp = tmp->prevPtr) {
            if (tmp->prevPtr == NULL) cout << tmp->data;
            else cout << tmp->data << " ";
        }
    }
}   