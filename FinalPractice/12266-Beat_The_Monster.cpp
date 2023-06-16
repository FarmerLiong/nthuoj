#include <iostream>
#include <queue>
using namespace std;

bool visited[32][512][512];
struct State {
  int lv, php, mhp; 
  int steps;
  State(int L, int HP, int MHP, int STEPS = 0) : lv(L), php(HP), mhp(MHP), steps(STEPS) {}
};

int main() {
  int L, HP, MHP, MDMG;
  int dmg[32], hl[32];
  cin >> L >> HP >> MHP >> MDMG;
  for (int i = 1; i <= L; i++) cin >> dmg[i] >> hl[i];
  queue<State> q;
  q.push({1, HP, MHP});

  while (!q.empty()) {
    State cur = q.front();
    if (cur.mhp <= 0) break;
    q.pop();

    if (cur.php > MDMG || dmg[cur.lv] >= cur.mhp) {
      State tmp(cur.lv, cur.php - MDMG, max(cur.mhp - dmg[cur.lv], 0), cur.steps+1);
      if (tmp.php < 0) tmp.php = 0;
      if (!visited[tmp.lv][tmp.php][tmp.mhp]) {
        visited[tmp.lv][tmp.php][tmp.mhp] = true;
        q.push(tmp);
      }
        // cout << "(" << tmp.lv << ", " << tmp.php << ", " << tmp.mhp << ")\n";
    } 
    if (cur.php > MDMG && hl[cur.lv] > MDMG) {
      State tmp(cur.lv, min(cur.php + hl[cur.lv], HP) - MDMG, cur.mhp, cur.steps+1);
      if (!visited[tmp.lv][tmp.php][tmp.mhp]) {
        visited[tmp.lv][tmp.php][tmp.mhp] = true;
        q.push(tmp);
      }
        // cout << "(" << tmp.lv << ", " << tmp.php << ", " << tmp.mhp << ")\n";
    }
    if (cur.lv < L && cur.php > MDMG) {
      State tmp(cur.lv+1, cur.php - MDMG, cur.mhp, cur.steps+1);
      if (!visited[tmp.lv][tmp.php][tmp.mhp]) {
        visited[tmp.lv][tmp.php][tmp.mhp] = true;
        q.push(tmp);
      }
        // cout << "(" << tmp.lv << ", " << tmp.php << ", " << tmp.mhp << ")\n";
    }
  }
  if (q.empty()) cout << -1 << endl;
  else cout << q.front().steps << endl;
  return 0;
}