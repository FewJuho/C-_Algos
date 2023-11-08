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
  int n, m;
  std::cin >> n;
  std::unordered_map<std::string, std::string> map;
  std::unordered_map<std::string, std::string> map_invert;
  std::string key, value;
  for (int i = 0; i < n; ++i) {
    std::cin >> key >> value;
    map.insert(std::make_pair(key, value));
    map_invert.insert(std::make_pair(value, key));
  }
  std::vector<std::string> vector;
  std::cin >> m;
  vector.reserve(m);
  std::string word;
  for (int i = 0; i < m; ++i) {
    std::cin >> word;
    vector.push_back(word);
  }
  for (std::string& i : vector) {
    if (map.find(i) != map.end()) {
      std::cout << map[i] << "\n";
    } else {
      std::cout << map_invert[i] << "\n";
    }
  }
}