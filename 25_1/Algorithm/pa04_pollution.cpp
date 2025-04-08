#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, c1, c2;
int board[21][21] = {0,};

void initialInput() {
  cin >> N >> c1 >> c2;

  int start, end, weight;
  for (int i = 0; i < N - 1; i++) {
    cin >> start >> end >> weight;
    board[start][end] = weight;
    board[end][start] = weight;
  }
}

/*
 * Bfs를 2번 돌려서 풀자
 * 각각 배열에 해당 위치까지 걸리는 최단 거리를 저장하자
 * 마지막에 각 출발점에서의 최단 거리를 비교하면서 <정점, 최단 거리>로 저장
 * 이후 정렬하면 끝
 * */

struct cmp {
    bool operator()(pair<int, int> a, pair<int, int> b) {
      if (a.second == b.second)
        return a.first > b.first;
      return a.second > b.second;
    }
};

vector<int> bfs(int start) {

  priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
  vector<int> dist(N+1, 987654321);
  pq.push(make_pair(start, 0));
  dist[start] = 0;

  while (!pq.empty()) {
    pair<int, int> now = pq.top();
    pq.pop();

    for (int i = 1; i <= N; i++) {
      if (board[now.first][i] == 0) continue;

      if (dist[i] > now.second + board[now.first][i]) {
        dist[i] = now.second + board[now.first][i];
        pq.push(make_pair(i, dist[i]));
      }
    }
  }

  return dist;
}

void solve() {
  vector<int> dist1 = bfs(c1);
  vector<int> dist2 = bfs(c2);

  vector<pair<int, int>> answer;
  for(int i = 1; i <= N; i++) {
    if(i == c1 || i == c2) continue;
    int minValue = min(dist1[i], dist2[i]);
    answer.push_back(make_pair(minValue, i));
  }

  sort(answer.begin(), answer.end());

  for(int i = 0; i < answer.size(); i++)
    cout << answer[i].second << endl;
}

int main() {
  initialInput();
  solve();

  return 0;
}