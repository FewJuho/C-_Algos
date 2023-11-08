#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  double num;
  int64_t n;
  std::cin >> n;
  std::priority_queue<double, std::vector<double>, std::greater<>> queue;

  for (int i = 0; i < n; ++i) {
    std::cin >> num;
    queue.push(num);
  }
  double sum = 0;
  auto size = queue.size();
  for (size_t i = 0; i < size - 1; ++i) {
    double s = 0;
    s += queue.top();
    queue.pop();
    s += queue.top();
    queue.pop();
    sum += s * 0.05;
    queue.push(s);
  }
  std::cout << sum;
}