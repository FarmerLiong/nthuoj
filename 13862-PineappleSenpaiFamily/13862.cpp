#include <string>
#include "function.h"

void setParentA(Person* cur) {
    if (cur->parentA) return;
    else {
        cur->parentA = new Person();
        cur->parentA->child = cur;
        if (cur->parentB) {
            cur->parentA->mate = cur->parentB;
            cur->parentB->mate = cur->parentA;
            cur->parentB->child = cur;
        }
    }
}
void setParentB(Person* cur) {
    if (cur->parentB) return;
    else {
        cur->parentB = new Person();
        cur->parentB->child = cur;
        if (cur->parentA) {
            cur->parentB->mate = cur->parentA;
            cur->parentA->mate = cur->parentB;
            cur->parentA->child = cur;
        }
    }
}
void setMate(Person* cur) {
    if (cur->mate) return;
    else {
        cur->mate = new Person();
        cur->mate->mate = cur;
        if (cur->child) {
            cur->mate->child = cur->child;
            if (cur->child->parentA == cur) cur->child->parentB = cur->mate;
            else    cur->child->parentA = cur->mate;
        }
            
    }
}
void setChild(Person* cur) {
    if (cur->child) return;
    else {
        cur->child = new Person();
        cur->child->parentA = cur;
        if (cur->mate) {
            cur->mate->child = cur;
            cur->child->parentB = cur;
        }
    }
}

void Person::describe(string* arr, int now, int len) {
    if (now >= len) return;

    if (arr[now] == "ParentA") {
        setParentA(this);
        this->parentA->describe(arr, now + 1, len);
    } else if (arr[now] == "ParentB") {
        setParentB(this);
        this->parentB->describe(arr, now + 1, len);
    } else if (arr[now] == "Mate") {
        setMate(this);
        this->mate->describe(arr, now + 1, len);
    } else if (arr[now] == "Child") {
        setChild(this);
        this->child->describe(arr, now + 1, len);
    } else if (arr[now] == "Name") {
        this->name = arr[now + 1];
        return;
    } else if (arr[now] == "Age") {
        this->age = stoi(arr[now + 1]);
        return;
    } else if (arr[now] == "Gender") {
        this->gender  = (arr[now + 1] == "MALE") ? MALE : FEMALE;
        return;
    } else if (arr[now] == "Personality") {
        (this->personality == "") ? this->personality = arr[now + 1] :
        this->personality.append(" " + arr[now + 1]);
        return;
    } 
}

Person* Person::getRelative(string* arr, int now, int len) {
    if (now == len) return this;

    if (arr[now] == "ParentA") {
        setParentA(this);
        return this->parentA->getRelative(arr, now + 1, len);
    } else if (arr[now] == "ParentB") {
        setParentB(this);
        return this->parentB->getRelative(arr, now + 1, len);
    } else if (arr[now] == "Mate") {
        setMate(this);
        return this->mate->getRelative(arr, now + 1, len);
    } else if (arr[now] == "Child") {
        setChild(this);
        return this->child->getRelative(arr, now + 1, len);
    }
    else return this;
}