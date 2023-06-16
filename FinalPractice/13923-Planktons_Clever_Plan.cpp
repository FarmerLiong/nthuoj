#include <iostream>
#include <string>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
struct Node{
  pii pos;
  int step;
  Node(pii p, int x): pos(p), step(x) {}
};
int grid[1005][1005];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

int main() {
  int N, M;
  cin >> N >> M;
  pii dest, init;
  for (int i = 1; i <= N; i++) {
    string str;
    cin >> str;
    str = '#' + str + '#';
    for (int j = 0; j <= M + 1; j++) {
      grid[i][j] = (str[j] == '#') ? 1 : 0;
      if(str[j] == '@') dest = {i,j};
      if(str[j] == 'P') init = {i,j};
    }
  }
  for (int i = 0; i < M + 1; i++) grid[0][i] = grid[N+1][i] = 1;

  queue<Node> q;
  q.push({init, 0});
  grid[init.first][init.second] = 1;
  while (!q.empty()) {
    Node n = q.front();
    if (n.pos == dest) break;
    q.pop();
    for (int i = 0; i < 4; i++) {
      int nx = n.pos.first + dx[i];
      int ny = n.pos.second + dy[i];
      if (grid[nx][ny]) continue;;
      q.push({{nx,ny}, n.step + 1});
      grid[nx][ny] = 1;
    }
  }
  if (q.empty()) cout << -1 << endl;
  else cout << q.front().step << endl;
  return 0;
}