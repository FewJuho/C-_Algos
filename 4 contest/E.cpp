#include <bits/stdc++.h>
class FenwickTree {
 public:
  std::vector<int64_t> tree;

  int64_t Parent(int64_t i) const {
    return i - (i & (-i));
  }

  int64_t Next(int64_t i) const {
    return i + (i & (-i));
  }

  explicit FenwickTree(int64_t n) : tree(n + 1, 0) {
  }

  int64_t Sum(int64_t i) const {
    int64_t sum = 0;
    ++i;
    while (i > 0) {
      sum += tree[i];
      i = Parent(i);
    }
    return sum;
  }

  void Build(int64_t i, int64_t value) {
    ++i;
    while (i < static_cast<int64_t>(tree.size())) {
      tree[i] += value;
      i = Next(i);
    }
  }

  void Update(int64_t i, int64_t value) {
    ++i;
    value -= (Sum(i - 1) - Sum(i - 2));
    while (i < static_cast<int64_t>(tree.size())) {
      tree[i] += value;
      i = Next(i);
    }
  }
};

int main() {
  std::vector<int64_t> vec;
  int64_t n, m, x;
  std::cin >> n;
  vec.reserve(n);

  for (int64_t i = 0; i < n; i++) {
    std::cin >> x;
    vec[i] = x;
  }
  FenwickTree tree(n);
  for (int64_t i = 0; i < n; i++) {
    tree.Build(i, vec[i]);
  }

  char command;
  std::cin >> m;
  for (int k = 0; k < m; ++k) {
    std::cin >> command;
    switch (command) {
      case ('s'):
        int64_t l, r;
        std::cin >> l >> r;
        std::cout << tree.Sum(r - 1) - tree.Sum(l - 2) << ' ';
        break;
      case ('u'):
        int64_t i, v;
        std::cin >> i >> v;
        tree.Update(i - 1, v);
        vec[i - 1] = v;
    }
  }
}