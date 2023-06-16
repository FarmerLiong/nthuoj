#include <cmath>
#include <queue>
#include <iostream>

#define MAX_MOVE 80
const int goalRow[] = {-1, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
const int goalCol[] = {-1, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
class State {
  public:
    int puzzle[4][4];
    int h;      // heuristic value
    int curMoves, prevDir;
    int ex,ey;  // position of empty tile
    // constructor
    State(int puzzle[4][4], int ex, int ey);
    // copy constructor
    State(const State& s);
    // Calculate Heuristic
    void setHeuristic();
    // update the state of puzzle
    void update(int i, int nx, int ny);
    // overload operator (sort elements in priority queue)
    bool operator<(const State& rhs) const;
};

using namespace std;
int main() {
  int puzzle[4][4], ex, ey;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      cin >> puzzle[i][j];
      if (puzzle[i][j] == 0) {ex = i; ey = j;}
    }
  State s(puzzle, ex, ey);
  priority_queue<State> pq;
  pq.push(s);

  const int dx[] = {1, -1, 0, 0};
  const int dy[] = {0, 0, 1, -1};

  while (!pq.empty()) {
    State curState = pq.top();

    if (curState.h == 0) {
      cout << curState.curMoves << endl;
      break;
    }
    pq.pop();
    if (curState.h + curState.curMoves > MAX_MOVE) 
      continue;
    
    for (int i = 0; i < 4; i++) {
      int nx = curState.ex + dx[i];
      int ny = curState.ey + dy[i];
      if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) 
        continue;
      if (i == (curState.prevDir^1)) // 0^1 = 1, 1^1 = 0, 2^1 = 3, 3^1 = 2
        continue;
      State nextState = curState;
      nextState.update(i, nx, ny);
      pq.push(nextState);
    }
  }

  if (pq.empty())
    cout << -1 << endl;
  return 0;
}

State::State(int puzzle[4][4], int ex, int ey) : h(), curMoves(0), prevDir(-1), ex(ex), ey(ey) {
  for (int i = 0; i < 4; i++) 
    for (int j = 0; j < 4; j++) 
      this->puzzle[i][j] = puzzle[i][j];
  setHeuristic();
}
State::State(const State& s) : h(s.h), curMoves(s.curMoves), prevDir(s.prevDir), ex(s.ex), ey(s.ey) {
  for (int i = 0; i < 4; i++) 
    for (int j = 0; j < 4; j++) 
      this->puzzle[i][j] = s.puzzle[i][j];
}
void State::update(int i, int nx, int ny) {
  prevDir = i;

  swap(puzzle[ex][ey], puzzle[nx][ny]);
  ex = nx; ey = ny;
  curMoves++;

  setHeuristic();
}
void State::setHeuristic() {
  int th = 0, tile;
  for (int i = 0; i < 4; i++) 
    for (int j = 0; j < 4; j++) {
      tile = puzzle[i][j];
      if (tile) {
        int goalR = goalRow[tile];
        int goalC = goalCol[tile];
        th += abs(goalR - i) + abs(goalC - j);

        if (i == goalR) {
          for (int k = j; k < 4; k++) {
            if (puzzle[i][k] && goalRow[puzzle[i][k]] == i && tile > puzzle[i][k])
              th += 2;
          }
        }
        if (j == goalC) {
          for (int k = i; k < 4; k++) {
            if (puzzle[k][j] && goalCol[puzzle[k][j]] == j && tile > puzzle[k][j])
              th += 2;
          }
        }
      }
      this->h = th;
    }
}
bool State::operator<(const State& rhs) const {
  // true for less priority
  return this->curMoves + this->h > rhs.curMoves + rhs.h; 
}