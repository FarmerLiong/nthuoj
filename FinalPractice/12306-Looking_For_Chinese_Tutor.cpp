#include <map>
#include <string>
#include <iostream>
using namespace std;

map<string, string> pokemon = {
  {"Wa" , "Waninoko"},
  {"Mi" , "Milotic"},
  {"Ma" , "Magikarp"},
  {"Va" , "Vaporeon"},
  {"Sh" , "Sharpedo"},
  {"Tapu" , "Tapu Fini"},
  {"Em" , "Empoleon"},
  {"La" , "Lapras"},
  {"Pi" , "Pikachu"},
  {"Pe" , "Pikachu"},
  {"Me" , "Mega Gyarados"},
};

int main() {
  string name, school, prefix;
  int T;
  cin >> T;
  while(T--) {
    cin >> name >> school;
    bool found = false;
    prefix = name.substr(0, 2);
    if (pokemon.find(prefix) != pokemon.end())  found = true;
    else {
      prefix = name.substr(0, 4);
      if (prefix == "Tapu") found = true;
    }
    if (found) cout << name + " the " + school + " " + pokemon[prefix] << endl;
    else cout << name + " is looking for a Chinese tutor, too!\n";
  }
  return 0;
}