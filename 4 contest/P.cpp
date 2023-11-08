#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

struct Node {
  int value = 0;
  int push = 0;
};

class ST {
 private:
  std::vector<Node> st_;

 public:
  explicit ST(const int &num) {
    st_.resize(2 * num);
  }
  int GetSum(const int &l, const int &r, const int &l_t, const int &r_t, const int &pos) {
    if (r_t <= l || l_t >= r) {
      return 0;
    }
    Push(pos, l_t, r_t);
    if (l <= l_t && r_t <= r) {
      return Get(pos, l_t, r_t);
    }
    int mid = (l_t + r_t) / 2;
    return GetSum(l, r, l_t, mid, 2 * pos) + GetSum(l, r, mid, r_t, 2 * pos + 1);
  }
  void AddVal(const int &l, const int &r, const int &l_t, const int &r_t, const int &value, const int &pos) {
    if (r_t <= l || l_t >= r) {
      return;
    }
    if (l <= l_t && r_t <= r) {
      st_[pos].push += value;
      return;
    }
    int mid = (l_t + r_t) / 2;
    AddVal(l, r, l_t, mid, value, 2 * pos);
    AddVal(l, r, mid, r_t, value, 2 * pos + 1);
    st_[pos].value = Get(2 * pos, l_t, mid) + Get(2 * pos + 1, mid, r_t);
  }
  void Push(const int &pos, const int &l, const int &r) {
    if (pos >= static_cast<int>(st_.size())) {
      return;
    }
    st_[pos].value += st_[pos].push * (r - l);
    if (r - l > 1) {
      st_[2 * pos].push += st_[pos].push;
      st_[2 * pos + 1].push += st_[pos].push;
    }
    st_[pos].push = 0;
  }
  int Get(const int &pos, const int &l, const int &r) {
    return st_[pos].value + st_[pos].push * (r - l);
  }
};

int main() {
  int n = 0, m = 0, com = 0;
  int l = 0, r = 0, add = 0;
  std::cin >> n >> m;
  int size = pow(2, ceil(log2(n)));
  ST st(size);
  for (int i = 0; i < m; ++i) {
    std::cin >> com >> l >> r;
    if (com == 1) {
      std::cin >> add;
      st.AddVal(l, r, 0, size, add, 1);
    } else if (com == 2) {
      std::cout << st.GetSum(l, r, 0, size, 1) << "\n";
    }
  }
  return 0;
}