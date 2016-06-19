#ifndef UTIL_H
#define UTIL_H

#include <iterator>
#include <algorithm>

template<class InputIterT1, class InputIterT2, class OutputIterT, class Comparator, class Func>
OutputIterT merge_apply(
    InputIterT1 first1, InputIterT1 last1,
    InputIterT2 first2, InputIterT2 last2,
    OutputIterT result, Comparator comp, Func func) {
  while (true)
  {
    if (first1 == last1) return std::copy(first2, last2, result);
    if (first2 == last2) return std::copy(first1, last1, result);

    if (comp(*first1, *first2) < 0) {
      *result = *first1;
      ++first1;
    } else if (comp(*first1, *first2) > 0) {
      *result = *first2;
      ++first2;
    } else {
      *result = func(*first1, *first2);
      ++first1;
      ++first2;
    }
    ++result;
  }
}

template<class T>
int compare_first(T a, T b) {
  return a.first - b.first;
}

template<class T>
T sum_pairs(T a, T b) {
  return std::make_pair(a.first, a.second + b.second);
}

#endif // UTIL_H
