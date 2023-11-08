#include <bits/stdc++.h>

class Node {
 public:
  int64_t key_;
  int64_t priority_;
  int64_t tmp_sum_ = 1;
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

  explicit CartesianTree(int n) {
    int new_priority;
    Node* current_node;
    Node* last_node = nullptr;

    for (int i = 0; i < n; ++i) {
      new_priority = MakeRandom();
      auto new_node = new Node{i + 1, new_priority};
      current_node = last_node;

      while (current_node != nullptr && current_node->priority_ > new_priority) {
        current_node = current_node->parent_;
      }

      if (current_node == nullptr) {
        new_node->left_child_ = root_;
        if (root_ != nullptr) {
          root_->parent_ = new_node;
        }
        root_ = new_node;
        FixNode(root_);
        last_node = new_node;
        continue;
      }
      new_node->left_child_ = current_node->right_child_;
      if (current_node->right_child_ != nullptr) {
        current_node->right_child_->parent_ = new_node;
      }
      current_node->right_child_ = new_node;
      new_node->parent_ = current_node;

      FixAllAbove(new_node);
      last_node = new_node;
    }
  }

  void FixAllAbove(Node* node) {
    Node* tmp = node;
    while (tmp != nullptr) {
      FixNode(tmp);
      tmp = tmp->parent_;
    }
  }

  void Sum(int64_t left_child, int64_t right_child) {
    auto first = Split(root_, left_child);
    auto second = Split(first.second, right_child - left_child);
    root_ = Merge(Merge(second.first, first.first), second.second);
  }

  Node* Merge(Node* left, Node* right) {
    Node* result;
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }
    if (left->priority_ >= right->priority_) {
      right->left_child_ = Merge(left, right->left_child_);
      right->left_child_->parent_ = right;
      result = FixNode(right);
    } else {
      left->right_child_ = Merge(left->right_child_, right);
      left->right_child_->parent_ = left;
      result = FixNode(left);
    }
    return result;
  }

  Node* FixNode(Node* node) {
    if (node != nullptr) {
      node->tmp_sum_ = TmpSums(node->left_child_) + TmpSums(node->right_child_) + 1;
    }
    return node;
  }

  int64_t TmpSums(Node* node) {
    if (node != nullptr) {
      return (node->tmp_sum_);
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

    if (key > TmpSums(root->left_child_)) {
      auto split_node = Split(root->right_child_, key - TmpSums(root->left_child_) - 1);

      if (split_node.first != nullptr) {
        split_node.first->parent_ = root;
      }

      root->right_child_ = split_node.first;
      return std::pair(FixNode(root), split_node.second);
    }
    auto split_node = Split(root->left_child_, key);

    if (split_node.first != nullptr) {
      split_node.first->parent_ = root;
    }

    root->left_child_ = split_node.second;
    return std::pair(split_node.first, FixNode(root));
  }

  void DeleteTree(Node* root) {
    if (root != nullptr) {
      DeleteTree(root->left_child_);
      DeleteTree(root->right_child_);
      delete root;
    }
  }

  void InorderedWalk(Node* root) const {
    if (root != nullptr) {
      InorderedWalk(root->left_child_);
      std::cout << root->key_ << ' ';
      InorderedWalk(root->right_child_);
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
  int n, commands, left, right;
  std::cin >> n >> commands;
  CartesianTree tree(n);

  for (int i = 0; i < commands; ++i) {
    std::cin >> left >> right;
    left--;
    tree.Sum(left, right);
  }
  tree.InorderedWalk(tree.root_);
}