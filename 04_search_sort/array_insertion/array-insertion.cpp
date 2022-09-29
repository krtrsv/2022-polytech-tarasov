#include <cassert>

int *insert(int arr[], int n, int x, int p);

int main() {
  // NOTE: aN - array
  //       rN - result

  // `insert` example
  int a0[10] =          {0, 1, 2, 3,      4, 5, 6, 7, 8, 9};
  int expected_r0[11] = {0, 1, 2, 3, 100, 4, 5, 6, 7, 8, 9};

  auto r0 = insert(a0, 10, 100, 4);
  for (auto i = 0; i < 11; ++i)
    assert(r0[i] == expected_r0[i]);

  return 0;
}

int *insert(int arr[], int n, int x, int p) {
  for (auto i = n; i > p; i--)
    arr[i] = arr[i - 1];

  arr[p] = x;
  return arr;
}
