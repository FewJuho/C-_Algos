#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <map>
#include <string>
#include <fstream>

bool Compare(std::pair<int64_t, std::string>& a, std::pair<int64_t, std::string>& b) {
  bool result = false;
  if (a.first > b.first || (a.first == b.first && a.second <= b.second)) {
    result = true;
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string word;
  std::map<std::string, int64_t> map;

  while (std::cin >> word) {
    ++map[word];
  }
  std::vector<std::pair<int64_t, std::string>> vector;
  vector.reserve(map.size());
  auto it = map.begin();
  for (it = map.begin(); it != map.end(); it++) {
    vector.emplace_back(std::make_pair(it->second, it->first));
  }
  std::sort(vector.begin(), vector.end(), Compare);
  for (const auto& i : vector) {
    std::cout << i.second << "\n";
  }
}