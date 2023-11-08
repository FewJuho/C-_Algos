#include <bits/stdc++.h>

int main() {
  int64_t n, x;
  std::cin >> n;
  std::vector<int64_t> vector;
  vector.resize(n);
  for (int64_t k = 0; k < n; ++k) {
    std::cin >> x;
    vector[k] = x;
  }
  std::vector<int64_t> sums;
  sums.resize(n + 1);
  sums[0] = 0;
  sums[1] = vector[0];
  for (int64_t i = 1; i < n; ++i) {
    sums[i + 1] = sums[i] + vector[i];
  }
  int64_t k, l, r;
  std::cin >> k;
  for (int64_t i = 0; i < k; ++i) {
    std::cin >> l >> r;
    std::cout << sums[r] - sums[l - 1] << ' ';
  }
}