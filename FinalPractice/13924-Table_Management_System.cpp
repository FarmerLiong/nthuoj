#include <map>
#include <set>
#include <iostream>
using namespace std;

const int N = 2e5+10;

struct Guest {
  int id, arrival, size, duration;
} arr[N];

struct cmp_arrival {
  bool operator()(const Guest& lhs, const Guest& rhs) const {
    return lhs.arrival < rhs.arrival;
  }
};
struct cmp_size {
  bool operator()(const Guest& lhs, const Guest& rhs) const {
    return (lhs.size == rhs.size) ? lhs.arrival > rhs.arrival : lhs.size < rhs.size;
  }
};
typedef pair<int, int> pii;
set<Guest, cmp_arrival> arrivallist;
set<Guest, cmp_size> grouplist;
map<int, int> table_avail;
multiset<pii> table_using;
int res[N];


bool assignTable(int time) {
  if (table_avail.empty() || arrivallist.empty()) return false;
  
  Guest g = *arrivallist.begin();
  auto table = table_avail.lower_bound(g.size);

  if (table == table_avail.end()) {
    int largest_size = (*table_avail.rbegin()).first;
    
    auto it = grouplist.upper_bound(Guest{0, 0, largest_size, 0});
    if (it == grouplist.begin()) return false;
    g = *(--it);

    table = table_avail.lower_bound(g.size);
  }
  int table_size = table->first;
  table_avail[table_size]--;
  if (table_avail[table_size] == 0) table_avail.erase(table_size);
  table_using.insert({time + g.duration, table_size});

  res[g.id] = time;
  arrivallist.erase(g); grouplist.erase(g);
  return true;
}
void releaseTable(int time) {
    while (!table_using.empty() && (*table_using.begin()).first <= time) {
      int release_time = (*table_using.begin()).first;
      table_avail[(*table_using.begin()).second]++;
      table_using.erase(table_using.begin());

      if (!table_using.empty() && (*table_using.begin()).first == release_time) continue;

      while (assignTable(release_time));
    }
}

int main() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    cin >> arr[i].arrival >> arr[i].size >> arr[i].duration;
    arr[i].id = i;
  }
  int ts, tn;
  for (int i = 0; i < M; i++) {
    cin >> ts >> tn;
    table_avail[ts] = tn;
  }
  for (int i = 0; i < N; i++) {
    releaseTable(arr[i].arrival - 1);
    arrivallist.insert(arr[i]); grouplist.insert(arr[i]);
    releaseTable(arr[i].arrival); assignTable(arr[i].arrival);
  }
  if (!arrivallist.empty()) releaseTable(1e9);

  for (int i = 0; i < N; i++) cout << res[i] << endl;
  return 0;
}


