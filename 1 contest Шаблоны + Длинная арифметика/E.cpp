#include <iostream>
#ifndef QUEUE
#define QUEUE
template <class T>
void PushHeap(T* begin, T* end) {
  int size = end - begin - 1;
  int parent = (size - 1) / 2;
  while ((0 < size) && (begin[parent] < begin[size])) {
    std::swap(begin[parent], begin[size]);
    size = (size - 1) / 2;
    parent = (size - 1) / 2;
  }
}

template <class T>
void PopHeap(T* begin, T* end) {
  int size = end - begin - 1;
  int i = 0, child = 0;
  std::swap(begin[i], begin[size]);
  while (i * 2 + 1 < size) {
    child = i * 2 + 1;
    if ((child + 1 < size) && begin[child] < begin[child + 1]) {
      child += 1;
    }
    if (begin[i] < begin[child]) {
      std::swap(begin[child], begin[i]);
      i = child;
    } else {
      break;
    }
  }
}
#endif