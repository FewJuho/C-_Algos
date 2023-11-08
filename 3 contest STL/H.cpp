#include <bits/stdc++.h>
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::map<std::string, std::map<std::string, int64_t>> map;
  std::string name, item;
  int64_t count_items;
  while (std::cin >> name >> item >> count_items) {
    map[name][item] += count_items;
  }
  for (auto& i : map) {
    std::cout << i.first << ':' << "\n";
    for (auto& k : i.second) {
      std::cout << k.first << ' ' << k.second << "\n";
    }
  }
  return 0;
}