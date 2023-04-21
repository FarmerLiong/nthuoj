using namespace std;
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "function.h"

string* ParseStatement(string statement) { // return the parsed array
    stringstream ss;
    vector<string> v;
    ss << statement;
    while (ss >> statement) v.push_back(statement);
    string* ret = new string[v.size()];
    for (int _ = 0; _ < v.size(); ++_) {
        ret[_] = v[_];
    }
    return ret;
}

int getParseStatementLength(string statement) {
    stringstream ss;
    ss << statement;
    int ret = 0;
    while (ss >> statement) ++ret;
    return ret;
}

int main () {
    Person* narrator = new Person();

    narrator->name = "Pineapple Senpai";
    narrator->age = 21;
    narrator->gender = MALE;
    narrator->personality = "seasick";

    int Q;
    cin >> Q;
    for (int _ = 0; _ < Q; ++_) {
        // input type of the query
        int type;
        cin >> type;
        // get the parsed array
        string statement;
        getline(cin, statement);
        string* arr = ParseStatement(statement);
        // compute the length of the array
        int len = getParseStatementLength(statement);
        switch(type) {
            case 1: 
                narrator = narrator->getRelative(arr, 0, len);
                break;
            case 2: 
                narrator->describe(arr, 0, len);
                break;
            case 3:
                cout << narrator->info() << "\n";
                break;
        }
        delete[] arr;
    }
    return 0;
}
