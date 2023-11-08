#ifndef BINARY_SEARCH
#define BINARY_SEARCH

template <class T>
bool BinarySearch(const T* begin, const T* end, const T& target) {
  int size = end - begin;
  int left = 0;
  int right = size - 1;
  int mid = size / 2;
  while (((begin[mid] < target) || (target < begin[mid])) && (left <= right)) {
    if (begin[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
    mid = (left + right) / 2;
  }
  return !(right < left);
}
#endif