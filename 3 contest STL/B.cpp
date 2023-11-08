#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

bool Compare(std::array<int64_t, 3>& a, std::array<int64_t, 3>& b) {
  bool result = false;
  if (a[1] < b[1]) {
    result = true;
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n, m;
  std::cin >> n;
  std::vector<int64_t> vector;
  vector.reserve(n);
  int64_t num;
  for (int i = 0; i < n; ++i) {
    std::cin >> num;
    vector.push_back(num);
  }
  std::cin >> m;
  std::vector<int64_t> targets;
  vector.reserve(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> num;
    targets.push_back(num);
  }
  for (auto&& i : targets) {
    std::cout << std::upper_bound(vector.begin(), vector.end(), i) - std::lower_bound(vector.begin(), vector.end(), i)
              << "\n";
  }
}