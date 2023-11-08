#ifndef VECTOR
#define VECTOR
#include <iostream>

template <class T>
class Vector {
 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  T* array_ = nullptr;

 public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;
  using Iterator = T*;
  using ConstIterator = const T*;
  using ReverseIterator = std::reverse_iterator<T*>;
  using ConstReverseIterator = std::reverse_iterator<const T*>;
  // конструкторы
  Vector() {
    size_ = 0;
    capacity_ = 0;
    array_ = nullptr;
  }

  explicit Vector(const SizeType& size) {
    if (size != 0) {
      try {
        array_ = new ValueType[size];
      } catch (...) {
        size_ = 0;
        capacity_ = 0;
        delete[] array_;
        throw;
      }
      size_ = size;
      capacity_ = size;
    }
  }

  Vector(const SizeType& size, const ValueType& value) {
    if (size != 0) {
      try {
        array_ = new ValueType[size];
        for (SizeType i = 0; i < size; i++) {
          array_[i] = value;
        }
      } catch (...) {
        size_ = 0;
        capacity_ = 0;
        delete[] array_;
        throw;
      }
      size_ = size;
      capacity_ = size;
    }
  }

  template <class Iterator,
            class = std::enable_if_t<std::is_base_of_v<std::forward_iterator_tag, typename                   // NOLINT
                                                       std::iterator_traits<Iterator>::iterator_category>>>  // NOLINT

  Vector(Iterator begin, Iterator end) {
    SizeType size = end - begin;
    size_ = size;
    capacity_ = size_;
    if (size_ != 0) {
      try {
        array_ = new T[size_];
        SizeType id = 0;
        for (auto it = begin; it != end; ++it, ++id) {
          array_[id] = *it;
        }
      } catch (...) {
        size_ = 0;
        capacity_ = 0;
        delete[] array_;
        throw;
      }
    }
  }

  // список инициализации
  Vector(const std::initializer_list<ValueType>& list_init) {
    SizeType list_size = list_init.size();
    try {
      array_ = new ValueType[list_size];
      SizeType i = 0;
      for (auto& k : list_init) {
        array_[i++] = k;
      }
    } catch (...) {
      size_ = 0;
      capacity_ = 0;
      delete[] array_;
      throw;
    }
    size_ = list_size;
    capacity_ = list_size;
  }

  // правило пяти
  Vector& operator=(const Vector& old_vector) {
    if (array_ != old_vector.array_) {
      size_ = old_vector.size_;
      capacity_ = old_vector.capacity_;
      if (old_vector.capacity_ > 0) {
        ValueType* new_array;
        try {
          new_array = new ValueType[old_vector.capacity_];
          for (SizeType i = 0; i < old_vector.size_; i++) {
            new_array[i] = old_vector.array_[i];
          }
        } catch (...) {
          delete[] new_array;
          throw;
        }
        delete[] array_;
        array_ = std::move(new_array);
      }
    }
    return *this;
  }

  Vector(const Vector& old_vector) {
    if (old_vector.capacity_ != 0) {
      size_ = old_vector.size_;
      capacity_ = old_vector.capacity_;
      try {
        array_ = new ValueType[old_vector.capacity_];
        for (SizeType i = 0; i < old_vector.size_; ++i) {
          array_[i] = old_vector.array_[i];
        }
      } catch (...) {
        delete[] array_;
        array_ = nullptr;
        throw;
      }
    }
  }

  Vector& operator=(Vector&& old_vector) noexcept {
    if (array_ != old_vector.array_) {
      size_ = old_vector.size_;
      capacity_ = old_vector.capacity_;
      delete[] array_;
      array_ = nullptr;
      if (capacity_ > 0) {
        array_ = std::move(old_vector.array_);
      }
      old_vector.size_ = 0;
      old_vector.capacity_ = 0;
      old_vector.array_ = nullptr;
    }
    return *this;
  }

  Vector(Vector&& old_vector) noexcept {
    size_ = old_vector.size_;
    capacity_ = old_vector.capacity_;
    array_ = nullptr;
    if (capacity_ > 0) {
      array_ = std::move(old_vector.array_);
    }
    old_vector.array_ = nullptr;
    old_vector.size_ = 0;
    old_vector.capacity_ = 0;
  }

  ~Vector() {
    delete[] array_;
  }

  // Методы size, capacity, empty

  SizeType Size() const {
    return size_;
  }

  SizeType Capacity() const {
    return capacity_;
  }

  bool Empty() const {
    return size_ == 0;
  }

  // Константный и неконстантный оператор доступа по индексу []
  ConstReference operator[](const SizeType& id) const {
    return array_[id];
  }

  Reference operator[](const SizeType& id) {
    return array_[id];
  }

  // Константный и неконстантный метод доступа по индексу At
  ConstReference At(const SizeType& id) const {
    if (id < 0 or id > size_ - 1) {
      throw std::out_of_range("std::out_of_range");
    }
    return array_[id];
  }

  Reference At(const SizeType& id) {
    if (id < 0 or id > size_ - 1) {
      throw std::out_of_range("std::out_of_range");
    }
    return array_[id];
  }

  // Методы Front() и Back()
  ConstReference Front() const {
    return array_[0];
  }

  Reference Front() {
    return array_[0];
  }

  ConstReference Back() const {
    return array_[size_ - 1];
  }

  Reference Back() {
    return array_[size_ - 1];
  }

  // Метод Data()
  Pointer Data() {
    return array_;
  }

  ConstPointer Data() const {
    return array_;
  }

  // Метод Swap(other)
  void Swap(Vector& old_vector) {
    Vector<ValueType> tmp_vector = std::move(old_vector);
    old_vector = std::move(*this);
    *this = std::move(tmp_vector);
  }

  // Метод Resize(size_new)
  void Resize(const SizeType& size_new) {
    if (size_new == size_) {
      return;
    }
    if (size_new < capacity_) {
      size_ = size_new;
      return;
    }
    if (size_new > capacity_) {
      auto array_tmp = new ValueType[size_new];
      delete[] array_tmp;
      array_tmp = nullptr;

      try {
        array_tmp = new ValueType[size_new];
        for (SizeType i = 0; i < size_; i++) {
          array_tmp[i] = std::move(array_[i]);
        }
      } catch (...) {
        delete[] array_tmp;
        return;
      }
      delete[] array_;
      size_ = size_new;
      capacity_ = size_new;
      array_ = std::move(array_tmp);
    }
  }

  // Метод Resize(size_new, value)
  void Resize(const SizeType& size_new, const ValueType& value) {
    SizeType size_prev = size_;
    Resize(size_new);
    for (SizeType i = size_prev; i < size_; ++i) {
      array_[i] = value;
    }
  }

  // Метод Reserve(new_cap)
  void Reserve(const SizeType& new_cap) {
    if (new_cap > capacity_) {
      auto array_tmp = new ValueType[new_cap];
      delete[] array_tmp;
      array_tmp = nullptr;
      try {
        array_tmp = new ValueType[new_cap];
        for (SizeType i = 0; i < size_; ++i) {
          array_tmp[i] = std::move(array_[i]);
        }
      } catch (...) {
        delete[] array_tmp;
        return;
      }
      delete[] array_;
      capacity_ = new_cap;
      array_ = std::move(array_tmp);
    }
  }

  // Метод ShrinkToFit()
  void ShrinkToFit() {
    ValueType* new_array_pointer;
    try {
      new_array_pointer = new ValueType[size_];
    } catch (...) {
      delete[] new_array_pointer;
      return;
    }
    for (SizeType i = 0; i < size_; i++) {
      new_array_pointer[i] = std::move(array_[i]);
    }
    delete[] array_;
    array_ = nullptr;
    capacity_ = size_;
    if (capacity_ != 0) {
      array_ = std::move(new_array_pointer);
    }
  }

  // Метод Clear()
  void Clear() {
    size_ = 0;
  }

  // Методы PushBack(const T&) и PushBack(T&&)
  void PushBack(const ValueType& key) {
    if (size_ != 0 && size_ == capacity_) {
      Reserve(2 * size_);
    }
    if (size_ == 0) {
      Reserve(1);
    }
    array_[size_] = key;
    size_++;
  }

  void PushBack(ValueType&& key) {
    if (size_ != 0 && size_ == capacity_) {
      Reserve(2 * size_);
    }
    if (size_ == 0) {
      Reserve(1);
    }
    array_[size_] = std::move(key);
    size_++;
  }

  // Метод PopBack()
  void PopBack() {
    if (size_ != 0) {
      size_--;
    }
  }

  // Операции сравнения (<, >, <=, >=, ==, !=)

  bool operator<(const Vector& old_vector) const {
    SizeType size_min = std::min(size_, old_vector.size_);
    SizeType size_max = std::max(size_, old_vector.size_);
    for (SizeType i = 0; i < size_max; ++i) {
      if (i < size_min && array_[i] < old_vector.array_[i]) {
        return true;
      }
      if (i >= size_ && i < old_vector.size_) {
        return true;
      }
      if (i < size_min && array_[i] > old_vector.array_[i]) {
        return false;
      }
      if (i < size_ && i >= old_vector.size_) {
        return false;
      }
    }
    return false;
  }

  bool operator==(const Vector& old_vector) const {
    return !(old_vector < *this or *this < old_vector);
  }

  bool operator!=(const Vector& old_vector) const {
    return *this != old_vector;
  }

  bool operator<=(const Vector& old_vector) const {
    return (*this == old_vector) or (*this < old_vector);
  }

  bool operator>=(const Vector& old_vector) const {
    return !(*this < old_vector);
  }

  bool operator>(const Vector& old_vector) const {
    return !(*this <= old_vector);
  }

  // Iterators
  ConstIterator begin() const {  // NOLINT
    return array_;
  }

  ConstIterator end() const {  // NOLINT
    return array_ + size_;
  }

  Iterator begin() {  // NOLINT
    return array_;
  }

  Iterator end() {  // NOLINT
    return array_ + size_;
  }

  ConstIterator cbegin() const {  // NOLINT
    return array_;
  }

  ConstIterator cend() const {  // NOLINT
    return array_ + size_;
  }

  ConstReverseIterator rbegin() const {  // NOLINT
    return std::make_reverse_iterator(array_ + size_);
  }

  ConstReverseIterator rend() const {  // NOLINT
    return std::make_reverse_iterator(array_);
  }

  ReverseIterator rbegin() {  // NOLINT
    return std::make_reverse_iterator(array_ + size_);
  }

  ReverseIterator rend() {  // NOLINT
    return std::make_reverse_iterator(array_);
  }

  ConstReverseIterator crbegin() const {  // NOLINT
    return std::make_reverse_iterator(array_ + size_);
  }

  ConstReverseIterator crend() const {  // NOLINT
    return std::make_reverse_iterator(array_);
  }
};
#endif