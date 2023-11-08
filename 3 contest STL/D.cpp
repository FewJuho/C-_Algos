#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::vector<std::vector<int>> map;
  int count = 0, it = 0, oper = 0, u = 0, v = 0;
  std::cin >> count >> it;
  map.resize(count + 1);

  for (int i = 0; i < it; ++i) {
    std::cin >> oper;
    if (oper == 1) {
      std::cin >> u >> v;
      map[u].push_back(v);
      map[v].push_back(u);
    } else {
      std::cin >> u;
      for (size_t k = 0; k < map[u].size(); ++k) {
        std::cout << map[u][k] << " ";
      }
      std::cout << "\n";
    }
  }
  return 0;
}