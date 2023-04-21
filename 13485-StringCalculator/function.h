#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>
using namespace std;

class String_Calculator {
    public:
        String_Calculator(){};
        String_Calculator(const string);
        String_Calculator& Add(const string);
        String_Calculator& Subtract(const string);
        String_Calculator& DividedBy(const string);
        void output() const;

    private:
        string s = "";
}; //end class String_Calculator

#endif // FUNCTION_H
