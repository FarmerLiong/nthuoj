#include<iostream>
#include"function.h"
using namespace std;
int main(){
    int n;
    string x, y;
    cin >> n;
    while(n--){
        cin >> x >> y;
        String_Calculator a(x), ans;
        ans = a.Subtract(y).Add(y).DividedBy(y);
        // ans = a.Subtract(y);
        ans.output();
    }
}
