#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <bits/stdc++.h>

template <class T>
class UniquePtr {
  T *ptr_;

 public:
  UniquePtr(const UniquePtr &) = delete;
  UniquePtr &operator=(const UniquePtr &) = delete;

  UniquePtr() : ptr_(nullptr) {
  }

  UniquePtr(UniquePtr &&old_ptr) noexcept : ptr_(old_ptr.ptr_) {
    old_ptr.ptr_ = nullptr;
  }

  UniquePtr &operator=(T *new_ptr) {
    ptr_ = std::move(new_ptr);
    return *this;
  }
  explicit UniquePtr(T *new_ptr) : ptr_(new_ptr) {
  }

  UniquePtr &operator=(UniquePtr &&old_ptr) noexcept {
    if (this != &old_ptr) {
      delete ptr_;
      ptr_ = old_ptr.ptr_;
      old_ptr.ptr_ = nullptr;
    }
    return *this;
  }
  T *Release() {
    T *ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
  }
  void Reset(T *ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
  }
  void Swap(UniquePtr<T> &uniq_ptr) {
    UniquePtr<T> temp = std::move(uniq_ptr);
    uniq_ptr = std::move(*this);
    *this = std::move(temp);
  }
  T *Get() const {
    return ptr_;
  }
  T &operator*() const {
    return *ptr_;
  }
  T *operator->() const {
    return ptr_;
  }
  explicit operator bool() const {
    return ptr_ != nullptr;
  }
  ~UniquePtr() {
    delete ptr_;
  }
};
#endif
