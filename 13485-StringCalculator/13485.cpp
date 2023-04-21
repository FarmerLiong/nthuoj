#include <iostream>
#include <string>
#include "function.h"
using namespace std;

String_Calculator::String_Calculator(const string str) {
    s = str;
}

String_Calculator& String_Calculator::Add(const string str) {
    s += str;
    return *this;
}
String_Calculator& String_Calculator::Subtract(const string str) {
    size_t pos = s.find(str);
    if (pos != string::npos) {
        s.erase(pos, str.length());
    } else s = "error";
    return *this;
}
String_Calculator& String_Calculator::DividedBy(const string str) {
    size_t pos = s.find(str);
    int count = 0;
    while (pos != string::npos) {
        count++;
        // cout << pos << endl;
        pos = s.find(str, pos + 1);
        // remain = remain + found
    }
    s = to_string(count);

    return *this;
}
void String_Calculator::output() const {
    cout << s << endl;
}