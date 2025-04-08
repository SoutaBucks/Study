#include <iostream>
#include <vector>

using namespace std;

int P, N, M, T;


int main() {
  cin >> P >> N >> M;
  vector<int> nums(N, 0);

  // 초기 입력 처리
  while(M-- > 0) {
    cin >> T;
    while(T-- > 0) {
      int from, to, noise;
      cin >> from >> to >> noise;
      for(int i = from; i < to; i++)
        nums[i] += noise;
    }
  }
  for(int i = 0; i < N; i++)
    nums[i] += P;


  // 연속합을 구하자
  // 연속 합에서 최소 값
  vector<int> partSum(N, 0);
  int n = nums[0];
  for(int i = 1; i < N; i++) {
    n += nums[i];
    partSum[i] = n;
  }

  /*
  for(auto i : nums)
    cout << i << " ";
  cout << endl;

  for(auto i : partSum)
    cout << i << " ";
*/
  // 연속하는 시간을 찾아야 한다
  int answer = 0;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < i; j++) {
      int delta = partSum[i] - partSum[j];
      if(delta <= 0) continue;
      answer = (delta > answer ? delta : answer);
    }
  }

  cout << answer;
}