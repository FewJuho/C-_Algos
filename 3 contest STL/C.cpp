#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m;
  std::cin >> n;
  std::vector<int> vector;
  vector.reserve(n);
  int num;
  for (int i = 0; i < n; ++i) {
    std::cin >> num;
    vector.push_back(num);
  }
  std::cin >> m;
  std::cout << std::count(vector.begin(), vector.end(), m);
}