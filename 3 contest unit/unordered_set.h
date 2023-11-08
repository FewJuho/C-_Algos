#ifndef OOP_ASSIGNMENTS_UNORDERED_SET
#define OOP_ASSIGNMENTS_UNORDERED_SET

#include <vector>
#include <forward_list>
#include <algorithm>
#include <list>

template <class KeyT, class Hash = std::hash<KeyT>, class Equal = std::equal_to<KeyT>>
class UnorderedSet {
 private:
  Hash hash_;
  Equal equal_;
  size_t elems_num_;
  size_t buckets_num_;
  std::vector<std::list<KeyT>> unordered_set_;
  const static int kIncreaseFactor = 2;
  const static int kCollisionFactor = 2;

 public:
  UnorderedSet() : elems_num_(0), buckets_num_(0) {
  }
  explicit UnorderedSet(size_t count) : elems_num_(0), buckets_num_(count) {
    unordered_set_ = std::vector<std::list<KeyT>>(count);
  }
  UnorderedSet(typename std::forward_list<KeyT>::iterator begin, typename std::forward_list<KeyT>::iterator end)
      : elems_num_(0), buckets_num_(0) {
    std::vector<KeyT> temp(begin, end);
    for (auto& elem : temp) {
      Insert(elem);
    }
  }
  UnorderedSet(const UnorderedSet<KeyT>& other) noexcept {  // NOLINT
    elems_num_ = other.elems_num_;
    buckets_num_ = other.buckets_num_;
    unordered_set_ = other.unordered_set_;
  }
  UnorderedSet<KeyT>& operator=(const UnorderedSet<KeyT>& other) noexcept {
    elems_num_ = other.elems_num_;
    buckets_num_ = other.buckets_num_;
    unordered_set_ = other.unordered_set_;
    return *this;
  }
  UnorderedSet(UnorderedSet<KeyT>&& other) noexcept {  // NOLINT
    elems_num_ = other.elems_num_;
    buckets_num_ = other.buckets_num_;
    unordered_set_ = std::move(other.unordered_set_);
    other.elems_num_ = 0;
    other.buckets_num_ = 0;
  }
  UnorderedSet<KeyT>& operator=(UnorderedSet<KeyT>&& other) noexcept {
    elems_num_ = other.elems_num_;
    buckets_num_ = other.buckets_num_;
    unordered_set_ = std::move(other.unordered_set_);
    other.elems_num_ = 0;
    other.buckets_num_ = 0;
    return *this;
  }
  size_t Size() const {
    return elems_num_;
  }
  bool Empty() const {
    return Size() == 0;
  }
  void Clear() {
    elems_num_ = 0;
    buckets_num_ = 1;
    unordered_set_.clear();
  }
  void Insert(const KeyT& elem) {
    if (Find(elem)) {
      return;
    }
    if (elems_num_ >= buckets_num_) {
      if (buckets_num_ == 0) {
        Rehash(1);
      } else {
        Rehash(buckets_num_ * kIncreaseFactor);
      }
    }
    auto idx = hash_(elem) % buckets_num_;
    unordered_set_[idx].push_back(std::move(elem));
    elems_num_++;
  }
  void Insert(const KeyT&& elem) {
    if (Find(elem)) {
      return;
    }
    if (elems_num_ >= buckets_num_) {
      if (buckets_num_ == 0) {
        Rehash(1);
      } else {
        Rehash(buckets_num_ * kIncreaseFactor);
      }
    }
    auto idx = hash_(elem) % buckets_num_;
    unordered_set_[idx].push_back(std::move(elem));
    elems_num_++;
  }
  void Erase(const KeyT& elem) {
    if (!Find(elem)) {
      return;
    }
    auto idx = hash_(elem) % buckets_num_;
    auto to_erase = std::find_if(unordered_set_[idx].begin(), unordered_set_[idx].end(),
                                 [this, &elem](const KeyT& curr) { return equal_(curr, elem); });
    if (to_erase == unordered_set_[idx].end()) {
      return;
    }
    unordered_set_[idx].erase(to_erase);
    if (elems_num_ * kCollisionFactor < buckets_num_) {
      Rehash(elems_num_ * kIncreaseFactor);
    }
    elems_num_--;
  }
  bool Find(const KeyT& elem) const {
    if (Empty()) {
      return false;
    }
    auto idx = hash_(elem) % buckets_num_;
    return std::any_of(unordered_set_[idx].begin(), unordered_set_[idx].end(),
                       [this, &elem](const KeyT& curr) { return equal_(elem, curr); });
  }
  void Rehash(size_t new_bucket_count) {
    if (new_bucket_count == buckets_num_) {
      return;
    }
    if (new_bucket_count < elems_num_) {
      return;
    }
    std::vector<std::list<KeyT>> temp(new_bucket_count);
    for (auto& bucket : unordered_set_) {
      for (auto& elem : bucket) {
        auto idx = hash_(elem) % new_bucket_count;
        temp[idx].push_back(std::move(elem));
      }
    }
    buckets_num_ = new_bucket_count;
    unordered_set_ = temp;
  }
  void Reserve(size_t new_bucket_count) {
    if (new_bucket_count > buckets_num_) {
      Rehash(new_bucket_count);
    }
  }
  size_t BucketCount() const {
    return buckets_num_;
  }
  size_t BucketSize(size_t id) const {
    if (id >= buckets_num_) {
      return 0;
    }
    return unordered_set_[id].size();
  }
  size_t Bucket(const KeyT& key) const {
    return hash_(key) % buckets_num_;
  }
  double LoadFactor() const {
    if (buckets_num_ == 0) {
      return 0;
    }
    return static_cast<double>(elems_num_) / static_cast<double>(buckets_num_);
  }
};

#endif  // OOP_ASSIGNMENTS_UNORDERED_SET