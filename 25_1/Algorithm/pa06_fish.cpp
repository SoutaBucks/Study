#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int n;

bool is_sorted(const vector<int>& a) {
  for (int i = 0; i < n; ++i)
    if (a[i] != i + 1)
      return false;
  return true;
}

void flip(vector<int>& arr, int l, int r) {
  while (l < r) {
    swap(arr[l], arr[r]);
    arr[l] *= -1;
    arr[r] *= -1;
    l++, r--;
  }
  if (l == r) arr[l] *= -1;
}

int solve_forward(vector<int> arr) {
  int flips = 0;
  for (int i = 0; i < n && flips < 3; ++i) {
    if (arr[i] == i + 1) continue;
    int j = i;
    while (j < n && abs(arr[j]) != i + 1) j++;
    if (j == n) break;
    flip(arr, i, j);
    flips++;
  }
  return is_sorted(arr) ? flips : 4;
}

int solve_backward(vector<int> arr) {
  int flips = 0;
  for (int i = n - 1; i >= 0 && flips < 3; --i) {
    if (arr[i] == i + 1) continue;
    int j = i;
    while (j >= 0 && abs(arr[j]) != i + 1) j--;
    if (j < 0) break;
    flip(arr, j, i);
    flips++;
  }
  return is_sorted(arr) ? flips : 4;
}

string solve(vector<int> arr) {
  int f1 = solve_forward(arr);
  int f2 = solve_backward(arr);
  int flips = min(f1, f2);

  if (flips == 0 || flips == 1) return "one";
  else if (flips == 2) return "two";
  else return "over";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int t = 0; t < 5; ++t) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
      cin >> arr[i];
    cout << solve(arr) << '\n';
  }
  return 0;
}
