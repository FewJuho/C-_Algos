#include <bits/stdc++.h>

class Node {
 public:
  int64_t key_;
  int64_t priority_;
  int64_t tmp_sum_ = key_;
  Node* parent_ = nullptr;
  Node* left_child_ = nullptr;
  Node* right_child_ = nullptr;
};

int64_t MakeRandom() {
  return (rand() % 10000000);
}

class CartesianTree {
 public:
  Node* root_ = nullptr;

  void Add(int64_t key) {
    if (!Find(root_, key)) {
      auto new_node = new Node{key, MakeRandom()};
      std::pair<Node*, Node*> insert_node = Split(root_, key);
      root_ = Merge(Merge(insert_node.first, new_node), insert_node.second);
    }
  }

  int64_t Sum(int64_t left_child, int64_t right_child) {
    auto left = Split(root_, left_child);
    auto right = Split(left.second, right_child);
    auto result = TmpSums(right.first);
    root_ = Merge(Merge(left.first, right.first), right.second);
    return result;
  }

  Node* Merge(Node* left, Node* right) {
    if (left == nullptr) {
      return right;
    }

    if (right == nullptr) {
      return left;
    }

    if (left->priority_ >= right->priority_) {
      left->right_child_ = Merge(left->right_child_, right);
      left->right_child_->parent_ = left;
      return FixNode(left);
    }

    right->left_child_ = Merge(left, right->left_child_);
    right->left_child_->parent_ = right;
    return FixNode(right);
  }

  Node* FixNode(Node* node) {
    if (node == nullptr) {
      return node;
    }
    auto new_result = node->key_ + TmpSums(node->left_child_) + TmpSums(node->right_child_);
    node->tmp_sum_ = new_result;
    return node;
  }

  int64_t TmpSums(Node* node) {
    if (node != nullptr) {
      return node->tmp_sum_;
    }
    return 0;
  }

  bool Find(Node* root, int64_t key) {
    if (root == nullptr) {
      return false;
    }
    if (root->key_ == key) {
      return true;
    }

    if (key < root->key_) {
      return Find(root->left_child_, key);
    }
    return Find(root->right_child_, key);
  }

  std::pair<Node*, Node*> Split(Node* root, int64_t key) {
    if (root == nullptr) {
      return std::pair(nullptr, nullptr);
    }

    if (key > root->key_) {
      auto split_node = Split(root->right_child_, key);
      root->right_child_ = split_node.first;
      if (split_node.first != nullptr) {
        split_node.first->parent_ = root;
      }
      return std::pair(FixNode(root), split_node.second);
    }

    auto split_node = Split(root->left_child_, key);
    root->left_child_ = split_node.second;
    if (split_node.second != nullptr) {
      split_node.second->parent_ = root;
    }
    return std::pair(split_node.first, FixNode(root));
  }

  void DeleteTree(Node* root) {
    if (root != nullptr) {
      DeleteTree(root->left_child_);
      DeleteTree(root->right_child_);
      delete root;
    }
  }

  ~CartesianTree() {
    DeleteTree(root_);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  CartesianTree tree;

  int64_t command, key, left_child, right_child;
  char req;
  std::cin >> command;
  for (auto i = 0; i < command; ++i) {
    std::cin >> req;
    switch (req) {
      case '?':
        std::cin >> left_child >> right_child;
        std::cout << tree.Sum(left_child, right_child + 1) << "\n";
        break;
      case '+':
        std::cin >> key;
        tree.Add(key);
        break;
    }
  }
}