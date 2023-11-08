#include <bits/stdc++.h>

class Node {
 public:
  int64_t key_;
  int64_t priority_;
  int64_t count_nodes_ = 1;
  Node* parent_ = nullptr;
  Node* left_child_ = nullptr;
  Node* right_child_ = nullptr;
};

int MakeRandom() {
  return rand() % 9999;
}

class CartesianTree {
 public:
  Node* root_ = nullptr;

  void Insert(int key) {
    if (!Exists(root_, key)) {
      std::pair<Node*, Node*> insert_node = Split(root_, key);
      root_ = Merge(Merge(insert_node.first, new Node{key, MakeRandom()}), insert_node.second);
    }
  }

  Node* Merge(Node* left, Node* right) {
    Node* result_node = right;
    if (left != nullptr) {
      if (right == nullptr) {
        result_node = left;
      } else if (left->priority_ >= right->priority_) {
        left->right_child_ = Merge(left->right_child_, right);
        left->right_child_->parent_ = left;
        result_node = FixNode(left);
      } else {
        right->left_child_ = Merge(left, right->left_child_);
        right->left_child_->parent_ = right;
        result_node = FixNode(right);
      }
    }
    return result_node;
  }

  Node* FixNode(Node* node) {
    node->count_nodes_ = 1;
    if (node->left_child_ != nullptr) {
      node->count_nodes_ += node->left_child_->count_nodes_;
    }
    if (node->right_child_ != nullptr) {
      node->count_nodes_ += node->right_child_->count_nodes_;
    }
    return node;
  }

  std::pair<Node*, Node*> Split(Node* root, int64_t key) {
    if (root != nullptr) {
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
    return std::pair(nullptr, nullptr);
  }

  void Next(int key) {
    auto current_node = root_;
    auto parent_node = root_;
    parent_node = nullptr;
    while (current_node) {
      if (key < current_node->key_) {
        parent_node = current_node;
        current_node = current_node->left_child_;
      } else {
        current_node = current_node->right_child_;
      }
    }
    if (parent_node != nullptr) {
      std::cout << parent_node->key_ << "\n";
    } else {
      std::cout << "none"
                << "\n";
    }
  }

  bool Exists(Node* root, int key) {
    if (root == nullptr) {
      return false;
    }
    if (root->key_ == key) {
      return true;
    }
    if (root->key_ > key) {
      return Exists(root->left_child_, key);
    }
    return Exists(root->right_child_, key);
  }

  void Prev(int key) {
    auto current_node = root_;
    auto parent_node = root_;
    parent_node = nullptr;
    while (current_node) {
      if (key > current_node->key_) {
        parent_node = current_node;
        current_node = current_node->right_child_;
      } else {
        current_node = current_node->left_child_;
      }
    }
    if (parent_node != nullptr) {
      std::cout << parent_node->key_ << "\n";
    } else {
      std::cout << "none"
                << "\n";
    }
  }

  void Kth(int key) {
    Node* tmp_node = root_;
    while (true) {
      if (tmp_node == nullptr) {
        break;
      }

      if (((tmp_node->left_child_ == nullptr) && (key == 0)) ||
          ((tmp_node->left_child_ != nullptr) && (tmp_node->left_child_->count_nodes_ == key))) {
        break;
      }

      if ((tmp_node->left_child_ != nullptr) && (tmp_node->left_child_->count_nodes_ > key)) {
        tmp_node = tmp_node->left_child_;
        continue;
      }

      if ((tmp_node->left_child_) != nullptr && (tmp_node->left_child_->count_nodes_ < key)) {
        key = key - tmp_node->left_child_->count_nodes_ - 1;
        tmp_node = tmp_node->right_child_;
        continue;
      }

      if (((tmp_node->left_child_) == nullptr) && (0 < key)) {
        key--;
        tmp_node = tmp_node->right_child_;
        continue;
      }
      break;
    }
    if (tmp_node != nullptr) {
      std::cout << tmp_node->key_ << "\n";
    } else {
      std::cout << "none"
                << "\n";
    }
  }

  void Delete(int key) {
    if ((Exists(root_, key))) {
      std::pair<Node*, Node*> split_node_first = Split(root_, key);
      std::pair<Node*, Node*> split_node_second = Split(split_node_first.second, key + 1);
      root_ = Merge(split_node_first.first, split_node_second.second);
      delete split_node_second.first;
    }
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
  int x;
  CartesianTree tree;
  std::string command;

  while (std::cin >> command) {
    if (command == "insert") {
      std::cin >> x;
      tree.Insert(x);
    } else if (command == "delete") {
      std::cin >> x;
      tree.Delete(x);
    } else if (command == "exists") {
      std::cin >> x;
      if (tree.Exists(tree.root_, x)) {
        std::cout << "true";
        std::cout << "\n";
      } else {
        std::cout << "false";
        std::cout << "\n";
      }
    } else if (command == "next") {
      std::cin >> x;
      tree.Next(x);
    } else if (command == "prev") {
      std::cin >> x;
      tree.Prev(x);
    } else if (command == "kth") {
      std::cin >> x;
      tree.Kth(x);
    } else if (command == "end") {
      break;
    }
  }
}