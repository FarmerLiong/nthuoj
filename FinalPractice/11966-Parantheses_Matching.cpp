#include <map>
#include <stack>
#include <string>
#include <iostream>
#define isLB(c) (c == '{' || c == '[' || c == '(' || c == '<') ? 1 : 0
#define isRB(c) (c == '}' || c == ']' || c == ')' || c == '>') ? 1 : 0
using namespace std;
map<char,char> mp = {{'{', '}'}, {'[', ']'}, {'(', ')'}, {'<', '>'}};

int main() {
  string str;
  int T;
  cin >> T;
  getchar();
  for (int t = 1; t <= T; t++) {
    getline(cin, str);
    stack<char> S;
    bool res = true;
    for (auto& it:str) {
      if (isLB(it)) {
        S.push(it);
      } 
      else if (isRB(it)) {
        if (S.empty()) {
          res = false;
          break;
        } 
        else if (mp[S.top()] == it)
          S.pop();
        else 
          break;
      }
    }
    if (S.empty() && res) cout << "Case " << t << ": Yes\n";
    else cout << "Case " << t << ": No\n";
  }
  return 0;
}