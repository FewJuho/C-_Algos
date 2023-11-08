#include <bits/stdc++.h>

int main() {
  int64_t n, x, pos, i, max_sum = -10000000000;
  std::cin >> n;
  std::vector<int64_t> vector;
  vector.resize(n);
  std::vector<int64_t> sums;
  sums.resize(n + 1);
  sums[0] = 0;

  for (int64_t k = 0; k < n; ++k) {
    std::cin >> x;
    vector[k] = x;
  }

  for (int64_t k = 0; k < n; ++k) {
    sums[k + 1] = sums[k] + vector[k];
    if (sums[k + 1] > max_sum) {
      pos = k + 1;
      max_sum = sums[k + 1];
    }
    if (sums[k + 1] < 0) {
      sums[k + 1] = 0;
    }
  }

  for (i = pos; i >= 0; i--) {
    if (sums[i] <= 0) {
      break;
    }
  }

  if (max_sum > 0) {
    std::cout << ++i << ' ' << pos << ' ' << max_sum;
  } else {
    std::cout << pos << ' ' << pos << ' ' << max_sum;
  }
}