#include <iostream>
#include <vector>
#include <algorithm>

class BigInt {
 private:
  std::vector<int> num_;

 public:
  BigInt() {
    num_.resize(1);
    num_[0] = 0;
  }
  explicit BigInt(std::string s) {
    for (auto digit : s) {
      num_.push_back(digit - '0');
    }
    reverse(num_.begin(), num_.end());
  }
  void Print() const {
    for (auto digit : num_) {
      std::cout << digit;
    }
    std::cout << '\n';
  }
  void PrintReversed() const {
    for (int i = num_.size() - 1; i >= 0; i--) {
      std::cout << num_[i];
    }
  }
  void operator+(const BigInt &a) {
    std::vector<int> result;
    int cap = 0;
    int min_size = std::min(a.num_.size(), this->num_.size());
    for (int i = 0; i < min_size; ++i) {
      int sum_tmp = cap + a.num_[i] + this->num_[i];
      cap = sum_tmp / 10;
      result.push_back(sum_tmp % 10);
    }
    min_size = std::min(a.num_.size(), this->num_.size());
    int max_size = std::max(a.num_.size(), this->num_.size());
    for (int i = min_size; i < max_size; ++i) {
      if (a.num_.size() > this->num_.size()) {
        int sum_tmp = cap + a.num_[i];
        cap = sum_tmp / 10;
        result.push_back(sum_tmp % 10);
      } else {
        int sum_tmp = cap + this->num_[i];
        cap = sum_tmp / 10;
        result.push_back(sum_tmp % 10);
      }
    }
    if (cap != 0) {
      result.push_back(cap);
    }
    for (int i = result.size() - 1; i > -1; i--) {
      std::cout << result[i];
    }
  }
};

int main() {
  std::string first, second;
  getline(std::cin, first);
  getline(std::cin, second);
  BigInt a(first);
  BigInt b(second);
  a + b;
  return 0;
}