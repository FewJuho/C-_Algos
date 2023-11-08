#include <iostream>
#include <memory>
#include <random>

struct Treaps {
  int keys = 0;
  int priority = 0;
  int size = 1;
  int min = 1000000000;
  bool push = false;
  bool reverse = false;
  std::shared_ptr<Treaps> right = nullptr;
  std::shared_ptr<Treaps> left = nullptr;
};

struct Pair {
  std::shared_ptr<Treaps> first;
  std::shared_ptr<Treaps> second;
};

class Treap {
 private:
  std::shared_ptr<Treaps> treap_;
  std::random_device dev_;
  std::mt19937 random_;
  std::uniform_int_distribution<std::mt19937::result_type> distr_;

 public:
  Treap() {
    treap_ = nullptr;
    random_ = std::mt19937(dev_());
    distr_ = std::uniform_int_distribution<std::mt19937::result_type>(0, 1000000);
  }
  Pair Split(std::shared_ptr<Treaps> &tree, int key) {
    if (tree == nullptr) {
      return {nullptr, nullptr};
    }
    Push(tree);
    int pos = tree->left ? tree->left->size : 0;
    if (pos < key) {
      Pair trees = Split(tree->right, key - pos - 1);
      tree->right = trees.first;
      Update(tree);
      return {tree, trees.second};
    }
    Pair trees = Split(tree->left, key);
    tree->left = trees.second;
    Update(tree);
    return {trees.first, tree};
  }
  std::shared_ptr<Treaps> Merge(std::shared_ptr<Treaps> &first, std::shared_ptr<Treaps> &second) {
    if (first == nullptr && second == nullptr) {
      return nullptr;
    }
    Push(first);
    Push(second);
    if (first == nullptr) {
      Update(second);
      return second;
    }
    if (second == nullptr) {
      Update(first);
      return first;
    }
    if (first->priority < second->priority) {
      first->right = Merge(first->right, second);
      Update(first);
      return first;
    }
    second->left = Merge(first, second->left);
    Update(second);
    return second;
  }
  void Update(const std::shared_ptr<Treaps> &node) {
    if (node == nullptr) {
      return;
    }
    int left_node_size = node->left ? node->left->size : 0;
    int right_node_size = node->right ? node->right->size : 0;
    int left_min = node->left ? node->left->min : 1000000000;
    int right_min = node->right ? node->right->min : 1000000000;
    node->size = left_node_size + right_node_size + 1;
    node->min = std::min(node->keys, std::min(left_min, right_min));
  }
  void Push(const std::shared_ptr<Treaps> &node) {
    if (node == nullptr || !node->reverse) {
      return;
    }
    if (node->left != nullptr) {
      node->left->reverse = node->left->reverse ^ node->reverse;
    }
    if (node->right != nullptr) {
      node->right->reverse = node->right->reverse ^ node->reverse;
    }
    node->reverse = false;
    std::swap(node->left, node->right);
  }
  void Insert(int position, int key) {
    Treaps node;
    node.keys = key;
    node.priority = distr_(random_);
    auto treap_node = std::make_shared<Treaps>(node);
    Pair tree = Split(treap_, position);
    std::shared_ptr<Treaps> merged_trees = Merge(tree.first, treap_node);
    treap_ = Merge(merged_trees, tree.second);
  }
  int RMQ(int l, int r) {
    Pair trees = Split(treap_, l - 1);
    Pair second_trees = Split(trees.second, r - l + 1);
    int min = 0;
    if (second_trees.first != nullptr) {
      min = second_trees.first->min;
    }
    std::shared_ptr<Treaps> merged_trees = Merge(second_trees.first, second_trees.second);
    treap_ = Merge(trees.first, merged_trees);
    return min;
  }
  void Reverse(int l, int r) {
    Pair trees = Split(treap_, l - 1);
    Pair second_trees = Split(trees.second, r - l + 1);
    if (second_trees.first != nullptr) {
      second_trees.first->reverse = !second_trees.first->reverse;
    }
    std::shared_ptr<Treaps> merged_trees = Merge(second_trees.first, second_trees.second);
    treap_ = Merge(trees.first, merged_trees);
  }
};

int main() {
  int tmp = 0;
  int n = 0, m = 0, l = 0, r = 0;
  int ind = 0;
  Treap treap;
  std::cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    std::cin >> ind;
    treap.Insert(i, ind);
  }
  for (int i = 0; i < m; ++i) {
    std::cin >> tmp >> l >> r;
    if (tmp == 1) {
      treap.Reverse(l, r);
    } else {
      std::cout << treap.RMQ(l, r) << "\n";
    }
  }
  return 0;
}