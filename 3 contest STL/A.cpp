#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

struct T {
  int count = 0;
  int penalty = 0;
  int pos = 0;
};
bool Compare(T& a, T& b) {
  bool result = false;
  if ((a.count > b.count) || (a.count == b.count && a.penalty < b.penalty) ||
      (a.count == b.count && a.penalty == b.penalty && a.pos < b.pos)) {
    result = true;
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n;
  std::cin >> n;
  std::vector<T> vector;
  vector.reserve(n);
  T team;
  for (int i = 0; i < n; ++i) {
    team.pos = i + 1;
    std::cin >> team.count >> team.penalty;
    vector.emplace_back(team);
  }
  std::sort(vector.begin(), vector.end(), Compare);
  for (auto&& i : vector) {
    std::cout << i.pos << "\n";
  }
}