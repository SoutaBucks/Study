// 파일명: pa05_palin.cpp
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

const int INF = 2e9;
const int MAX = 100001;

int dp[MAX];
bool palindrome[MAX];

void solve_single(const string& s) {
  int n = s.size();
  vector<vector<bool>> is_pal(n, vector<bool>(n, false));

  // 길이 1 회문
  for (int i = 0; i < n; ++i)
    is_pal[i][i] = true;

  // 길이 2 회문
  for (int i = 0; i < n - 1; ++i)
    if (s[i] == s[i + 1])
      is_pal[i][i + 1] = true;

  // 길이 3 이상
  for (int len = 3; len <= n; ++len) {
    for (int i = 0; i + len - 1 < n; ++i) {
      int j = i + len - 1;
      if (s[i] == s[j] && is_pal[i + 1][j - 1])
        is_pal[i][j] = true;
    }
  }

  // 최소 절단 수 계산
  dp[0] = 0; // 0개의 문자일 때 절단수는 0
  for (int i = 1; i <= n; ++i) {
    dp[i] = INF;
    for (int j = 0; j < i; ++j) {
      if (is_pal[j][i - 1]) {
        dp[i] = min(dp[i], dp[j] + 1);
      }
    }
  }

  cout << dp[n] - 1 << '\n'; // 절단 수 = 조각 수 - 1
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  while (N--) {
    string s;
    cin >> s;
    solve_single(s);
  }

  return 0;
}
