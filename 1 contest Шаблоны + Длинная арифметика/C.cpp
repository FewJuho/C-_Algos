#ifndef MERGE
#define MERGE
template <class T>
void Merge(T* first_begin, const T* first_end, const T* second_begin, const T* second_end) {
  int size_first = first_end - first_begin;
  int size_second = second_end - second_begin;
  auto* tmp_array = new T[size_first + size_second];
  int i = 0;
  int j = 0;
  while (i < size_first && j < size_second) {
    if (first_begin[i] < second_begin[j]) {
      auto temporary = first_begin[i];
      tmp_array[i + j] = temporary;
      ++i;
    } else {
      auto temporary = second_begin[j];
      tmp_array[i + j] = temporary;
      ++j;
    }
  }
  while (i < size_first) {
    auto temporary = first_begin[i];
    tmp_array[i + j] = temporary;
    ++i;
  }
  while (j < size_second) {
    auto temporary = second_begin[j];
    tmp_array[i + j] = temporary;
    ++j;
  }
  for (int i = 0; i < size_first + size_second; ++i) {
    first_begin[i] = tmp_array[i];
  }
  delete[] tmp_array;
}
template <class T>
void Sort(T* begin, T* end) {
  if (end - begin < 2) {
    return;
  }
  int mid = (end - begin) / 2;
  Sort(begin, begin + mid);
  Sort(begin + mid, end);
  Merge(begin, begin + mid, begin + mid, end);
}
#endif