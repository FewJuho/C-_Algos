#include <bits/stdc++.h>

class Point {
 public:
  int x_ = 0;
  int y_ = 0;
  int z_ = 0;
};

int ToParent(int i) {
  return (i & (i + 1)) - 1;
}

int ToNext(int i) {
  return i | (i + 1);
}

class FenwickTree {
 private:
  int size_ = 0;
  std::vector<std::vector<std::vector<int>>> tree_;

 public:
  explicit FenwickTree(int& n) {
    size_ = n;
    tree_.resize(size_);
    for (auto& i : tree_) {
      i.resize(size_);
      for (auto& j : i) {
        j.resize(size_);
      }
    }
  }

  int Get(const Point& a) {
    int result = 0;
    for (int i = a.x_; i >= 0; i = ToParent(i)) {
      for (int j = a.y_; j >= 0; j = ToParent(j)) {
        for (int k = a.z_; k >= 0; k = ToParent(k)) {
          result += tree_[i][j][k];
        }
      }
    }
    return result;
  }

  void Add(const Point& a, const int& value) {
    for (int i = a.x_; i < size_; i = ToNext(i)) {
      for (int j = a.y_; j < size_; j = ToNext(j)) {
        for (int k = a.z_; k < size_; k = ToNext(k)) {
          tree_[i][j][k] += value;
        }
      }
    }
  }

  int Sum(const Point& a, const Point& b) {
    Point b_x{a.x_ - 1, b.y_, b.z_};
    Point b_y{b.x_, a.y_ - 1, b.z_};
    Point b_z{b.x_, b.y_, a.z_ - 1};

    Point a_x{a.x_ - 1, a.y_ - 1, b.z_};
    Point a_y{a.x_ - 1, b.y_, a.z_ - 1};
    Point a_z{b.x_, a.y_ - 1, a.z_ - 1};
    Point a_all{a.x_ - 1, a.y_ - 1, a.z_ - 1};

    return Get(b) - Get(b_x) - Get(b_y) - Get(b_z) + Get(a_x) + Get(a_y) + Get(a_z) - Get(a_all);
  }
};

int main() {
  int x, y, z, n, value, command;
  std::cin >> n;
  FenwickTree tree(n);
  while (std::cin >> command) {
    if (command == 1) {
      std::cin >> x >> y >> z >> value;
      Point a{x, y, z};
      tree.Add(a, value);
      continue;
    }
    if (command == 2) {
      std::cin >> x >> y >> z;
      Point a{x, y, z};
      std::cin >> x >> y >> z;
      Point b{x, y, z};
      std::cout << tree.Sum(a, b) << "\n";
      continue;
    }
    break;
  }
  return 0;
}
