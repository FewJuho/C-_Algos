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
  void operator-(const BigInt &a) {
    std::vector<int> result;
    int cap = 0;
    for (uint64_t i = 0; i < a.num_.size(); ++i) {
      int dif = this->num_[i] - a.num_[i] - cap;
      if (dif < 0) {
        dif += 10;
        cap = 1;
      } else {
        cap = 0;
      }
      result.push_back(dif);
    }
    for (uint64_t i = a.num_.size(); i < this->num_.size(); ++i) {
      if (this->num_[i] - cap < 0) {
        result.push_back(this->num_[i] - cap + 10);
        cap = 1;
      } else {
        result.push_back(this->num_[i] - cap);
        cap = 0;
      }
    }
    bool no_to_print_zero = false;
    for (int i = result.size() - 1; i > -1; i--) {
      if (result[i] != 0 or i == 0) {
        no_to_print_zero = true;
      }
      if (no_to_print_zero) {
        std::cout << result[i];
      }
    }
  }
};

int main() {
  std::string first, second;
  getline(std::cin, first);
  getline(std::cin, second);
  BigInt a(first);
  BigInt b(second);
  a - b;
  return 0;
}