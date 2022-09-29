#include <cassert>

#define RESULT_SIZE 1024

int search(int arr[], int n, int x, int *result);
void clr(int *arr, int arr_size);

int main() {
  int result[RESULT_SIZE] = {};

  int arr1[] = {1, 2, 3, 1, 4, 5, 1};
  assert(search(arr1, 7, 1, result) == 3);
  clr(result, RESULT_SIZE);

  assert(search(arr1, 7, 10, result) == 0);
  clr(result, RESULT_SIZE);

  int arr2[] = {1, 1, 1, 1, 1};
  assert(search(arr2, 5, 1, result) == 5);

  return 0;
}

int search(int arr[],  // Array itself
           int n,      // Array size
           int x,      // What to search
           int *result // Results array
) {

  // After we have checked the entire `arr`
  if (n == 0) {
    int count = 0;
    for (auto i = 0; i < RESULT_SIZE; ++i) {
      if (result[i] != 0)
        count++;
      else
        return count;
    }
  }

  else if (arr[n - 1] == x) {
    for (auto i = 0; i < RESULT_SIZE; ++i) {
      if (result[i] == 0) {
        result[i] = n - i;
        return search(arr, n - 1, x, result);
      }
    }
    // In case 1024 is not enough
    return -1;
  }

  return search(arr, n - 1, x, result);
}

// Fill array with zeroes (clear it)
void clr(int *arr, int arr_size) {
  for (auto i = 0; i < arr_size; ++i)
    arr[i] = 0;
}
