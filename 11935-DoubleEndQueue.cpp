#include <bits/stdc++.h>
#include <iostream>
#include <cstddef>
using namespace std;

class _node{
    public:
        int data;
        _node* next,*prev;
        _node(int d=0){data = d; next=prev=NULL;}

};
class _dequeue{
    protected:
        _node* Begin,*End;

    public:
        _dequeue(){
            Begin = new _node(0);
            End = new _node(0);
            Begin->next=End;
            End->prev=Begin;
        }
        bool Empty(){
            if(Begin==NULL || Begin->next==End) return true;
            return false;
        }
        virtual void push(const _node) = 0;
        virtual void pop() = 0;
        virtual _node* get_data() = 0;
};

class _stack : public _dequeue{
    public:
        _stack():_dequeue(){}
        void push(const _node N);
        void pop();
        _node* get_data();
};
class _queue : public _dequeue{
    public:
        _queue():_dequeue(){}
        void push(const _node N);
        void pop();
        _node* get_data();
};

int main(){
    _stack stk;
    _queue que;
    string inst;
    string cont;
    int data;
    _node* ptr;
    while(cin>>cont){
        if(cont=="stack"){
            //stack
            cin>>inst;
            if(inst=="push"){
                cin>>data;
                stk.push(data);
            }
            else if(inst=="pop"){
                stk.pop();
            }
            else if(inst=="top"){
                ptr = stk.get_data();
                if(ptr!=NULL)
                    cout<<stk.get_data()->data<<"\n";
            }
        }
        else if(cont=="queue"){
            //stack
            cin>>inst;
            if(inst=="push"){
                cin>>data;
                que.push(data);
            }
            else if(inst=="pop"){
                que.pop();
            }
            else if(inst=="front"){
                ptr = que.get_data();
                if(ptr!=NULL)
                    cout<<que.get_data()->data<<"\n";
            }
        }
        else{
            break;
        }
    }

}

void _stack::push(const _node N) {
    _node* newNode = new _node(N.data);
    if (this->Empty()) {
        Begin->next = newNode;
        newNode->prev = Begin;
    } else {
        End->prev->next = newNode;
        newNode->prev = End->prev;
    }
    newNode->next = End;
    End->prev = newNode;
}
void _stack::pop() {
    if (this->Empty()) return;
    End->prev = End->prev->prev;
    delete [] End->prev->next;
    End->prev->next = End;
}
_node* _stack::get_data() {
    if (!this->Empty()) return End->prev;
    return NULL;
}
void _queue::push(const _node N) {
    _node* newNode = new _node(N.data);
    if (this->Empty()) {
        Begin->next = newNode;
        newNode->prev = Begin;
    } else {
        End->prev->next = newNode;
        newNode->prev = End->prev;
    }
    newNode->next = End;
    End->prev = newNode;
}
void _queue::pop() {
    if (this->Empty()) return;
    Begin->next = Begin->next->next;
    delete [] Begin->next->prev;
    Begin->next->prev = Begin;
}
_node* _queue::get_data() {
    if (!this->Empty()) return Begin->next;
    return NULL;
}