#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <unordered_map>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int16_t command;
  int64_t n, money;
  std::cin >> n;
  std::unordered_map<std::string, int64_t> map;
  std::string name;
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> command;
    if (command == 1) {
      std::cin >> name >> money;
      map[name] += money;
    } else {
      std::cin >> name;
      if (map.find(name) != map.end()) {
        std::cout << map[name] << "\n";
      } else {
        std::cout << "ERROR"
                  << "\n";
      }
    }
  }
}