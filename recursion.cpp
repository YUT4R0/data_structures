#include <iostream>
using namespace std;

void printArr(int arr[], int LEN) {
  if (LEN >= 0) {
    printArr(arr, LEN - 1);
    cout << arr[LEN] << ", ";
  }
}

int *bubbleSort(int arr[], int LEN) {
  int i, j, temp;
  for (i = LEN; i > 0; i--) {
    for (j = 0; j < i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  return arr;
}

void binSearch(int key, int arr[], int LEN, int start, int end) {
  int mid = (start + end) / 2;
  if (arr[mid] == key)
    cout << "item na pos " << mid << endl;
  else if (key < arr[mid])
    binSearch(key, arr, LEN, start, mid - 1);
  else if (key > arr[mid])
    binSearch(key, arr, LEN, mid + 1, end);
}

int recursiveSum(int arr[], int start, int end) {
  if (start == end)
    return arr[start];
  else {
    int mid = (start + end) / 2;
    return recursiveSum(arr, start, mid) + recursiveSum(arr, mid + 1, end);
  }
}

int main() {
  const int LEN = 10;
  int arr[LEN] = {10, 22, 34, 46, 75, 68, 97, 9008, 29, 5};
  bubbleSort(arr, LEN);
  printArr(arr, LEN - 1);
  int key;
  cout << endl << "set key: ";
  cin >> key;
  int start = 0;
  int end = LEN - 1;
  binSearch(key, arr, LEN, start, end);
  int sum = recursiveSum(arr, start, end);
  cout << "sum: " << sum << endl;
  return 0;
}