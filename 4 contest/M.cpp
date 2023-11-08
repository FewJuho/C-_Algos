#include <vector>
#include <string>
#include <cmath>
#include <iostream>

unsigned int a, b, cur = 0;
unsigned int NextRand() {
  cur = cur * a + b;
  return cur >> 8;
}

void Update(std::vector<int64_t> &sum, const int &left, const int &right, const int64_t &add) {
  sum[left] = sum[left] + add;
  sum[right] = sum[right] - add;
}

void Build(std::vector<int64_t> &sum, std::vector<unsigned int> &pref_sum) {
  int size = sum.size() - 1;
  for (int i = 0; i < size; i++) {
    pref_sum[i + 1] = pref_sum[i] + sum[i];
  }
  sum[0] = 0;
  for (int i = 0; i < size; ++i) {
    sum[i + 1] = sum[i] + pref_sum[i + 1];
  }
}

int main() {
  std::vector<int64_t> tmp(pow(2, 24) + 1, 0);
  std::vector<unsigned int> second_tmp(pow(2, 24) + 1, 0);

  int add_iterations = 0, l = 0, r = 0, query = 0, add = 0;
  int64_t sum = 0, mod = pow(2ll, 32);

  std::cin >> add_iterations >> query >> a >> b;
  for (int i = 0; i < add_iterations; ++i) {
    add = NextRand();
    l = NextRand();
    r = NextRand();
    if (l > r) {
      std::swap(l, r);
    }
    Update(tmp, l, r + 1, add);
  }

  Build(tmp, second_tmp);

  for (int i = 0; i < query; ++i) {
    l = NextRand();
    r = NextRand();
    if (l > r) {
      std::swap(l, r);
    }
    sum += tmp[r + 1] - tmp[l];
    sum %= mod;
  }
  std::cout << sum << std::endl;
  return 0;
}