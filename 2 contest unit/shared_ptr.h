#ifndef UNTITLED23_UNIQUE_PTR_H
#define UNTITLED23_UNIQUE_PTR_H
#include <iostream>

template <class T>
class SharedPtr {
 private:
  T *ptr_ = nullptr;
  int64_t *strong_counter_ = nullptr;

 public:
  SharedPtr() = default;

  explicit SharedPtr(T *new_ptr) : ptr_(new_ptr) {
    if (new_ptr != nullptr) {
      strong_counter_ = new int64_t;
      *strong_counter_ = 1;
    } else {
      strong_counter_ = nullptr;
    }
  }

  SharedPtr(const SharedPtr &sptr) : ptr_(sptr.ptr_), strong_counter_(sptr.strong_counter_) {
    if (strong_counter_ != nullptr) {
      *strong_counter_ += 1;
    }
  }

  SharedPtr(SharedPtr &&sptr) noexcept : ptr_(sptr.ptr_), strong_counter_(sptr.strong_counter_) {
    sptr.ptr_ = nullptr;
    sptr.strong_counter_ = nullptr;
  }

  SharedPtr &operator=(T *new_ptr) {
    if (ptr_ != new_ptr && strong_counter_ != nullptr) {
      if (*strong_counter_ == 1) {
        delete ptr_;
        delete strong_counter_;
      } else {
        *strong_counter_ -= 1;
      }
    }
    ptr_ = new_ptr;
    if (new_ptr != nullptr) {
      strong_counter_ = new int64_t;
      *strong_counter_ = 1;
    } else {
      strong_counter_ = nullptr;
    }
    return *this;
  }

  SharedPtr &operator=(SharedPtr &&sptr) noexcept {
    if (ptr_ != sptr.ptr_) {
      if (strong_counter_ != nullptr) {
        if (*strong_counter_ == 1) {
          delete ptr_;
          delete strong_counter_;
        } else {
          *strong_counter_ -= 1;
        }
      }
    }
    ptr_ = sptr.ptr_;
    strong_counter_ = sptr.strong_counter_;
    if (this != &sptr) {
      sptr.ptr_ = nullptr;
      sptr.strong_counter_ = nullptr;
    }
    return *this;
  }

  SharedPtr &operator=(const SharedPtr &sptr) {
    if (ptr_ != sptr.ptr_) {
      if (strong_counter_ != nullptr) {
        if (*strong_counter_ == 1) {
          delete ptr_;
          delete strong_counter_;
        } else {
          *strong_counter_ -= 1;
        }
      }
    }
    ptr_ = sptr.ptr_;
    strong_counter_ = sptr.strong_counter_;
    if (strong_counter_ != nullptr && this != &sptr) {
      *strong_counter_ += 1;
    }
    return *this;
  }

  void Reset(T *ptr = nullptr) {
    if (ptr != ptr_ && strong_counter_ != nullptr) {
      if (*strong_counter_ == 1) {
        delete strong_counter_;
        delete ptr_;
      } else {
        *strong_counter_ -= 1;
      }
    }
    ptr_ = ptr;
    if (ptr_ != nullptr) {
      strong_counter_ = new int64_t;
      *strong_counter_ = 1;
    } else {
      strong_counter_ = nullptr;
    }
  }

  void Swap(SharedPtr<T> &sptr) {
    SharedPtr<T> tmp = std::move(sptr);
    sptr = std::move(*this);
    *this = std::move(tmp);
  }

  int64_t UseCount() const {
    if (strong_counter_ != nullptr) {
      return *strong_counter_;
    }
    return 0;
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

  ~SharedPtr() {
    if (strong_counter_ != nullptr) {
      *strong_counter_ -= 1;
      if (*strong_counter_ == 0) {
        delete ptr_;
        delete strong_counter_;
      }
    }
  }
};
#endif