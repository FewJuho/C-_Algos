#include <bits/stdc++.h>

class SegmentTree {
  int n_;
  std::vector<std::pair<int, int>> tree_;

 public:
  explicit SegmentTree(const std::vector<int>& value) {
    tree_.resize(1 << (static_cast<int>(std::ceil(log2(value.size())) + 1)));
    n_ = tree_.size() / 2;
    size_t num = 0;
    for (auto i = tree_.size() / 2; i < tree_.size(); ++i) {
      if (num < value.size()) {
        tree_[i] = std::make_pair(value[num++], 1);
      }
    }

    for (auto i = tree_.size() - 1; i > 0; i--) {
      if (i % 2 == 0) {
        tree_[i / 2] = MaxValue(tree_[i], tree_[i + 1]);
      }
    }
  }

  std::pair<int, int> MaxValue(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    std::pair<int, int> result = {a.first, a.second + b.second};
    if (a.first > b.first) {
      result = a;
    } else if (a.first < b.first) {
      result = b;
    }
    return result;
  }

  std::pair<int, int> Query(int left, int right) {
    left += (n_ - 1);
    right += (n_ - 1);
    std::pair<int, int> left_answer, right_answer, result;
    while (left <= right) {
      if (left == right) {
        result = tree_[left];
        break;
      }

      if (right % 2 == 0) {
        right_answer = MaxValue(right_answer, tree_.at(right--));
      }

      if (left % 2 == 1) {
        left_answer = MaxValue(left_answer, tree_.at(left++));
      }

      right /= 2;
      left /= 2;
    }
    return MaxValue(MaxValue(left_answer, right_answer), result);
  }
};

int main() {
  int n, k, x, left, right = 0;
  std::vector<int> vector;
  std::cin >> n;
  vector.resize(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> x;
    vector[i] = x;
  }

  SegmentTree tree(vector);

  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    std::cin >> left >> right;
    std::pair<int, int> pair = tree.Query(left, right);
    std::cout << pair.first << " " << pair.second << std::endl;
  }
  return 0;
}