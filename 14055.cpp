#include <iostream>
#include <math.h>
using namespace std;

#define max(a,b) (a > b? a : b)

int TreeNodes[35000]; // 2^15 = 32767
int L;  // height of tree
int nodes = 0;

void swap(int* a, int* b) {
  int tmp = *a;
  // cout << "Before swapping:" << *a << " " << *b << endl;  
  *a = *b; *b = tmp;
  // cout << "After swapping:" << *a << " " << *b << endl;  
}

int getMax(int nodeIdx) {
  if (nodeIdx > nodes) return 0;
  return max(getMax(nodeIdx * 2), getMax(nodeIdx * 2 +1)) + TreeNodes[nodeIdx];
}

int main() {
  int key;
  cin >> L;

  while (cin >> key) TreeNodes[++nodes] = key; 
  int leafNodes = pow(2, L-1);
  int swaps = 0;
  
  // Task 2
  int max = getMax(1);

  // Task 1
  for (int i = 0; i < L; i ++){ 
    // cout << "i: " << i << endl;
    for (int j = nodes - leafNodes + 1; j <= nodes; j += pow(2, i)) {
      // cout << "  j: " << j << " Node: " << TreeNodes[j] << endl;
      int d = pow(2, i-1);
      if (TreeNodes[(int)(j+d)] < TreeNodes[j]) {
        swaps++;
        for (int k = 0; k < d; k++) swap(TreeNodes+j+k, TreeNodes+j+d+k);
      }
    }
  }
  // for (int i = nodes - leafNodes; i < nodes; i++) cout << TreeNodes[i] << " ";
  for (int i = nodes - leafNodes + 2; i <= nodes; i++) 
    if (TreeNodes[i] < TreeNodes[i-1]) swaps = -1;
  cout << swaps << endl;
  cout << max ;
  return 0;
}


