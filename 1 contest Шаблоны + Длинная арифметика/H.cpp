#include <iostream>
#include <vector>
#include <algorithm>

class BigInt {
 private:
  std::vector<int> num_;
  int base_ = 1000;

 public:
  BigInt() {
    num_.resize(1);
    num_[0] = 0;
  }
  explicit BigInt(std::string &s) {
    num_.resize(s.size() / 3 + 2, 0);
    int base = 1;
    for (auto i = static_cast<int>(s.size()) - 1, pos = 0; i > -1; --i) {
      num_[pos] += (s[i] - '0') * base;
      base *= 10;
      if (base == base_) {
        base = 1;
        ++pos;
      }
    }
    while (num_.back() == 0 && num_.size() > 1) {
      num_.pop_back();
    }
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
  void operator*(BigInt &a) {
    int64_t result[7000]{};
    uint64_t tmp_size = a.num_.size(), this_size = num_.size();
    for (uint64_t i = 0; i < this_size; ++i) {
      for (uint64_t j = 0; j < tmp_size; ++j) {
        result[i + j] += num_[i] * a.num_[j];
      }
    }
    uint64_t res_size = 6999;
    for (uint64_t i = 0; i < res_size; ++i) {
      result[i + 1] += result[i] / base_;
      result[i] %= base_;
    }
    int64_t pos = res_size;
    while (result[pos] == 0 && pos > 0) {
      --pos;
    }
    int null_count = 0, tmp = 0;
    for (int i = pos; i > -1; --i) {
      if (i != pos && result[i] < 100) {
        tmp = result[i];
        while (tmp != 0) {
          tmp /= 10;
          ++null_count;
        }
        null_count = 2 - null_count;
        if (result[i] == 0) {
          null_count = 1;
        }
        for (int j = 0; j <= null_count; ++j) {
          std::cout << 0;
        }
        null_count = 0;
      }
      std::cout << result[i];
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string first, second;
  std::cin >> first >> second;
  std::cerr << second;
  BigInt a(first);
  BigInt b(second);
  a *b;
  return 0;
}