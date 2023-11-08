#include <bits/stdc++.h>

struct Node {
  int value_ = 0;
  int min_ = value_;
  int max_ = value_;
  int tmp_sum_ = value_;
};

class SegmentTree {
 public:
  std::vector<Node> tree_;

  explicit SegmentTree(const std::vector<Node>& value) {
    tree_.resize((1 << static_cast<int>(ceil(log2(value.size())) + 1)));
    size_t id = 0;

    for (auto i = tree_.size() / 2; i < tree_.size(); ++i) {
      if (id < value.size()) {
        tree_[i].value_ = value[id++].value_;
      }
      if (i == tree_.size() / 2) {
        tree_[i].min_ = 1;
        tree_[i].max_ = 2;
        continue;
      }
      tree_[i].min_ = tree_[i - 1].min_ + 1;
      tree_[i].max_ = tree_[i - 1].max_ + 1;
    }

    for (auto i = tree_.size() - 1; i > 0; i--) {
      if (i % 2 == 0) {
        tree_[i / 2].value_ = std::max(tree_[i].value_, tree_[i + 1].value_);
        tree_[i / 2].max_ = tree_[i + 1].max_;
        tree_[i / 2].min_ = tree_[i].min_;
      }
    }
  }

  void FixNode(const int& key) {
    int to_sum = tree_[key].tmp_sum_;
    tree_[key].tmp_sum_ = 0;
    tree_[key].value_ += to_sum;
    if (tree_[key].max_ != tree_[key].min_ + 1) {
      tree_[key * 2].tmp_sum_ += to_sum;
      tree_[key * 2 + 1].tmp_sum_ += to_sum;
    }
  }

  int Sum(const int& left, const int& right, const int& key) {
    FixNode(key);
    if (tree_[key].max_ <= left || tree_[key].min_ >= right) {
      return 0;
    }
    if (tree_[key].min_ >= left && tree_[key].max_ <= right) {
      return tree_[key].value_ + tree_[key].tmp_sum_;
    }
    return std::max(Sum(left, right, 2 * key), Sum(left, right, 2 * key + 1));
  }

  void Update(const int& left, const int& right, int& value, int node) {
    FixNode(node);

    if (tree_[node].max_ <= left || tree_[node].min_ >= right) {
      return;
    }
    if (left <= tree_[node].min_ && tree_[node].max_ <= right) {
      tree_[node].tmp_sum_ += value;
      return;
    }

    Update(left, right, value, 2 * node);
    Update(left, right, value, 2 * node + 1);
    auto sum_first = tree_[node * 2].value_ + tree_[node * 2].tmp_sum_;
    auto sum_second = tree_[node * 2 + 1].value_ + tree_[node * 2 + 1].tmp_sum_;
    tree_[node].value_ = std::max(sum_first, sum_second);
  }
};

int main() {
  int n, m, add;
  std::vector<Node> vector;
  std::cin >> n;
  vector.reserve(n + 1);
  for (auto i = 0; i < n; ++i) {
    std::cin >> add;
    Node new_node{add, 0};
    vector.push_back(new_node);
  }
  SegmentTree tree(vector);

  char command;
  std::cin >> m;
  int left, right;
  for (int i = 0; i < m; ++i) {
    std::cin >> command;
    if (command == 'm') {
      std::cin >> left >> right;
      std::cout << tree.Sum(left, right + 1, 1) << '\n';
      continue;
    }
    if (command == 'a') {
      std::cin >> left >> right >> add;
      tree.Update(left, right + 1, add, 1);
      continue;
    }
  }
}