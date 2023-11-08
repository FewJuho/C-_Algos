#ifndef MERGE
#define MERGE
template <class T, class U, class V>
void Merge(const T* first_begin, const T* first_end, const U* second_begin, const U* second_end, V* out) {
  int size_first = first_end - first_begin;
  int size_second = second_end - second_begin;
  int i = 0;
  int j = 0;
  while (i < size_first && j < size_second) {
    if (first_begin[i] < second_begin[j]) {
      V temporary = first_begin[i];
      out[i + j] = temporary;
      ++i;
    } else {
      V temporary = second_begin[j];
      out[i + j] = temporary;
      ++j;
    }
  }
  while (i < size_first) {
    V temporary = first_begin[i];
    out[i + j] = temporary;
    ++i;
  }
  while (j < size_second) {
    V temporary = second_begin[j];
    out[i + j] = temporary;
    ++j;
  }
}
#endif