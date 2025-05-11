#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <tuple>
#include <set>
#include <algorithm>

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const int COST = 3;

struct Node {
    int x, y;
    int g; // 출발점에서 현재 지점까지의 맨해튼 거리
    int f; // 평가 함수 값
    bool operator>(const Node &other) const {
      return f > other.f;
    }
};

int manhattan(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

int euclidean(int x1, int y1, int x2, int y2) {
  return (int)sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
  int m, n;
  cin >> m >> n;
  vector<vector<int>> grid(m, vector<int>(n, 1));

  int zero_cnt;
  cin >> zero_cnt;
  for (int i = 0; i < zero_cnt; ++i) {
    int z, x, y;
    cin >> z >> x >> y;
    grid[x][y] = 0;
  }

  string s_tag;
  int sx, sy;
  cin >> s_tag >> sx >> sy;

  string t_tag;
  int tx, ty;
  cin >> t_tag >> tx >> ty;

  string ob_tag;
  int ob_cnt;
  cin >> ob_tag >> ob_cnt;
  for (int i = 0; i < ob_cnt; ++i) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int lx = min(x1, x2), hx = max(x1, x2);
    int ly = min(y1, y2), hy = max(y1, y2);
    for (int x = lx; x <= hx; ++x) {
      for (int y = ly; y <= hy; ++y) {
        grid[x][y] = 0;
      }
    }
  }

  priority_queue<Node, vector<Node>, greater<Node>> pq;
  pq.push({sx, sy, 0, 0});
  vector<vector<bool>> visited(m, vector<bool>(n, false));

  while (!pq.empty()) {
    Node cur = pq.top(); pq.pop();
    if (visited[cur.x][cur.y]) continue;
    visited[cur.x][cur.y] = true;

    if (cur.x == tx && cur.y == ty) {
      cout << cur.f << endl;
      return 0;
    }

    for (int d = 0; d < 4; ++d) {
      int nx = cur.x + dx[d];
      int ny = cur.y + dy[d];
      if (nx >= 0 && ny >= 0 && nx < m && ny < n && grid[nx][ny] && !visited[nx][ny]) {
        int ng = cur.g + COST;
        int h = euclidean(nx, ny, tx, ty);
        int f = ng + h;
        pq.push({nx, ny, ng, f});
      }
    }
  }

  // 도달 불가능한 경우
  cout << -1 << endl;
  return 0;
}
