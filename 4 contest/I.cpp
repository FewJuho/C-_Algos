#include <bits/stdc++.h>

class Node {
 public:
  int key_;
  int priority_;
  int id_;
  Node* parent_ = nullptr;
  Node* left_child_ = nullptr;
  Node* right_child_ = nullptr;
};

class CartesianTree {
 public:
  Node* root_ = nullptr;
  explicit CartesianTree(const std::vector<std::pair<int, int>>& vector) {
    Node* last_node = nullptr;
    Node* curr_node;
    int id = 1;
    for (auto& i : vector) {
      curr_node = last_node;

      while (curr_node != nullptr && curr_node->priority_ > i.second) {
        curr_node = curr_node->parent_;
      }

      auto new_node = new Node{i.first, i.second, id};

      if (curr_node == nullptr) {
        new_node->left_child_ = root_;
        if (root_ != nullptr) {
          root_->parent_ = new_node;
        }
        root_ = new_node;
      } else {
        new_node->left_child_ = curr_node->right_child_;
        if (curr_node->right_child_ != nullptr) {
          curr_node->right_child_->parent_ = new_node;
        }
        curr_node->right_child_ = new_node;
        new_node->parent_ = curr_node;
      }
      last_node = new_node;
      id++;
    }
  }

  void PrintInorderedWalk(Node* root) const {
    if (root == nullptr) {
      return;
    }
    PrintInorderedWalk(root->left_child_);

    if (root->parent_ != nullptr) {
      std::cout << root->parent_->id_;
    } else {
      std::cout << '0';
    }
    std::cout << ' ';

    if (root->left_child_ != nullptr) {
      std::cout << root->left_child_->id_;
    } else {
      std::cout << '0';
    }
    std::cout << ' ';

    if (root->right_child_ != nullptr) {
      std::cout << root->right_child_->id_;
    } else {
      std::cout << '0';
    }
    std::cout << "\n";

    PrintInorderedWalk(root->right_child_);
  }

  void DeleteTree(Node* root) {
    if (root == nullptr) {
      return;
    }
    DeleteTree(root->left_child_);
    DeleteTree(root->right_child_);
    delete root;
  }

  ~CartesianTree() {
    PrintInorderedWalk(root_);
    DeleteTree(root_);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, a, b;
  std::cin >> n;
  std::vector<std::pair<int, int>> tree;
  tree.reserve(n + 1);
  for (auto i = 0; i < n; ++i) {
    std::cin >> a >> b;
    tree.emplace_back(std::pair<int, int>{a, b});
  }
  std::cout << "YES";
  std::cout << "\n";
  CartesianTree c_tree(tree);
}