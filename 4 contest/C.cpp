#include <bits/stdc++.h>

class SparseTable {
 public:
  int64_t counts_ = 0;
  std::vector<std::vector<int64_t>> vector_;
  std::vector<int64_t> pow_;
  explicit SparseTable(int64_t len) {
    int64_t n = 1;
    int64_t pow = ceil(std::log2(len + 1)) + 1;
    pow_.reserve(pow);
    for (int64_t i = 0; i < pow; i++, n *= 2) {
      pow_.push_back(n);
    }
  }
};

void Build(const std::vector<int64_t>& arr, SparseTable& st) {
  st.counts_ = arr.size();
  int64_t pow = ceil(log2(st.counts_ + 1));
  st.vector_ = std::vector<std::vector<int64_t>>(pow, std::vector<int64_t>(st.counts_));
  st.vector_[0] = arr;
  int64_t n = 1;
  for (int64_t i = 0; i + 1 < pow; ++i) {
    for (int64_t j = 0; j + n < st.counts_; ++j) {
      st.vector_[i + 1][j] = std::min(st.vector_[i][j], st.vector_[i][j + n]);
    }
    n *= 2;
  }
}

int main() {
  std::vector<int64_t> arr;
  int64_t n = 0, q = 0, l = 0, r = 0, x;
  std::cin >> n >> q;
  arr.reserve(n + 1);

  for (int64_t i = 0; i < n; ++i) {
    std::cin >> x;
    arr.push_back(x);
  }

  SparseTable st(arr.size());
  Build(arr, st);
  for (int64_t i = 0; i < q; ++i) {
    std::cin >> l >> r;
    l--;
    int64_t k = 0, size = st.pow_.size();
    for (int64_t j = 1; j < size; ++j) {
      if (r - l >= st.pow_[j - 1] && r - l < st.pow_[j]) {
        k = j - 1;
        break;
      }
    }
    int64_t pow = st.pow_[k];
    std::cout << std::min(st.vector_[k][l], st.vector_[k][r - pow]) << "\n";
  }
  return 0;
}