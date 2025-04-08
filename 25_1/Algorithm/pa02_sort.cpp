#include <iostream>
#include <vector>

using namespace std;

int sortWay, k, N;
vector<int> nums;

void showNums() {
  for (auto i: nums)
    cout << i << endl;
}

int insertionSort() {
  int result = 0;

  for (int j = 1; j < N; j++) {
    int key = nums[j];
    int i = j - 1;
    while (i >= 0 && nums[i] > key) {
      nums[i + 1] = nums[i];
      i--;
      result++;
    }
    nums[i + 1] = key;
    if (i >= 0)
      result++;

    if (j == k)
      return result;
  }

  //showNums();
  return result;
}

void selectionSort() {
  int temp, minIndex;

  for (int j = 0; j < N - 1; j++) {
    minIndex = j;
    for (int i = j + 1; i < N; i++) {
      if (nums[minIndex] > nums[i])
        minIndex = i;
    }
    temp = nums[j];
    nums[j] = nums[minIndex];
    nums[minIndex] = temp;

    // pass일 때의 경우 반환
    if (j == k - 1)
      showNums();
  }

}

void heapify(int n, int i) {
  int minValue = i; // 루트를 최소값으로 가정
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  // 왼쪽 자식이 루트보다 작으면 최소값 변경
  if (left < n && nums[left] < nums[minValue])
    minValue = left;

  // 오른쪽 자식이 최소값보다 작으면 최소값 변경
  if (right < n && nums[right] < nums[minValue])
    minValue = right;

  // 최소값이 루트가 아니라면 교환 후 재귀 호출
  if (minValue != i) {
    swap(nums[i], nums[minValue]);
    heapify(n, minValue);
  }
}

void heapSort(int n) {
  for(int i = n / 2 - 1; i >= 0; i--)
    heapify(n, i);

  for(int i = n - 1; i >= n - k; i--) {
    swap(nums[0], nums[i]);
    heapify(i, 0);
  }

  for(int i = 0; i < N - k; i++)
    cout << nums[i] << endl;
}

/*// 힙 정렬 함수
void heapSort(int n) {
  // 최소 힙 구축
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(n, i);

  // k번째 정렬 후 상태 출력
  if (k == 0) {
    for (int i = 0; i < n; i++)
      cout << nums[i] << endl;
    return;
  }

  // 힙에서 하나씩 원소 추출
  for (int i = n - 1; i >= N - k; i--) {
    swap(nums[0], nums[i]);  // 루트(최소값)와 마지막 원소 교환
    heapify(i, 0);    // 힙을 재정렬

    // k번째 정렬 후 상태 출력
    if (i == n - k) {
      for (int j = 0; j < n - k; j++)
        cout << nums[j] << endl;
      return;
    }
  }
}*/

void quickSort(int start, int end, int &count) {
  if (start > end) return;

  if(start == end) {
    count++;
    if(count == k)
      showNums();
    return;
  }

  int pivot = start;
  int i = pivot + 1, j = end;

  while (i <= j) {
    while (i <= end && nums[i] <= nums[pivot])
      i++;
    while (j > start && nums[j] >= nums[pivot])
      j--;

    if (i > j)
      swap(nums[pivot], nums[j]);
    else
      swap(nums[i], nums[j]);
  }
  count++;

  if(count == k) {
    showNums();
    return;
  }
  quickSort(start, j - 1, count);
  quickSort(j + 1, end, count);
}

int main() {
  cin >> sortWay >> k;
  cin >> N;

  for (int i = 0; i < N; i++) {
    int n;
    cin >> n;
    nums.push_back(n);
  }

  switch (sortWay) {
    case 1:
      cout << insertionSort();
      break;
    case 2:
      selectionSort();
      break;
    case 3:
      heapSort(N);
      break;
    case 4:
      int count = 0;
      quickSort(0, N - 1, count);
      break;
  }
}
