#include <iostream>
#ifndef KTH
#define KTH
template <class T>
int Partition(T* array, int left, int right) {
  T pivot_value = array[left];
  int point_pivot = left;
  for (int i = left + 1; i < right; ++i) {
    if (array[i] < pivot_value) {
      ++point_pivot;
      std::swap(array[i], array[point_pivot]);
    }
  }
  std::swap(array[left], array[point_pivot]);
  return point_pivot;
}
template <class T>
void KthElement(T* begin, T* kth, T* end) {
  int left = 0, right = end - begin;
  auto pivot = Partition(begin, left, right);
  while ((pivot < kth - begin) || (kth - begin < pivot)) {
    pivot = Partition(begin, left, right);
    if (*kth < begin[pivot]) {
      right = pivot;
    } else {
      left = pivot + 1;
    }
  }
}
#endif