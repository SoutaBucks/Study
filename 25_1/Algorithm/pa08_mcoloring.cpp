#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> color;
int solution_count = 0;
int node_count = 0;

bool isSafe(int v, int c) {
  for (int i = 0; i < n; ++i) {
    if (graph[v][i] && color[i] == c)
      return false;
  }
  return true;
}

void dfs(int v) {
  if (v == n) {
    solution_count++;
    return;
  }
  for (int c = 1; c <= m; ++c) {
    node_count++;  // 색을 시도할 때마다 증가
    if (isSafe(v, c)) {
      color[v] = c;
      dfs(v + 1);
      color[v] = 0;
    }
  }
}

int main() {
  cin >> n >> m;
  graph.resize(n, vector<int>(n));
  color.resize(n, 0);

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> graph[i][j];

  dfs(0);

  if (solution_count == 0) {
    cout << "no" << endl;
  } else {
    cout << solution_count << endl;
    cout << node_count << endl;
  }
  return 0;
}
