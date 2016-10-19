#include <map>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cmath>

template<class InputIterator,class InputIterator2, class OutputIterT, class Function, class T2>
  OutputIterT for_each_copy(InputIterator first, InputIterator2 last, OutputIterT result, Function fn, T2 x)
{
  while (first!=last) {
    *result=fn(*first,x);
    ++first;
  }
  return result;
}

template<class InputIterT1, class InputIterT2, class OutputIterT, class Comparator, class Func, class Func2, class Sc>
OutputIterT merge_apply2(
    InputIterT1 first1, InputIterT1 last1,
    InputIterT2 first2, InputIterT2 last2,
    OutputIterT result, Comparator comp, Func func, Func2 func2, Sc n) {
  while (true)
  {
    if(first1==last1) return for_each_copy(first2, last2, result, func2,n);
    if(first2==last2) return for_each_copy(first1, last1, result,func2,n);

    if (comp(*first1, *first2)<0) {
      *result = *first1;
      ++first1;
    } else if (comp(*first1, *first2)>0) {
      *result=*first2;
      ++first2;
    } else {
      *result=func(*first1, *first2);
      ++first1;
      ++first2;
    }
    ++result;
  }
}


template<class InputIterT1, class InputIterT2, class OutputIterT, class Comparator, class Func>
OutputIterT merge_apply(
    InputIterT1 first1, InputIterT1 last1,
    InputIterT2 first2, InputIterT2 last2,
    OutputIterT result, Comparator comp, Func func) {
  while (true)
  {
    if(first1==last1) return std::copy(first2, last2, result);
    if(first2==last2) return std::copy(first1, last1, result);

    if (comp(*first1, *first2)<0) {
      *result = *first1;
      ++first1;
    } else if (comp(*first1, *first2)>0) {
      *result=*first2;
      ++first2;
    } else {
      *result=func(*first1, *first2);
      ++first1;
      ++first2;
    }
    ++result;
  }
}

template<class T, class V>
T mul_make_pair(T a, const V& b) {
  return std::make_pair(a.first, a.second *b);
}

template<class T>
int compare_first(const T& a, const T& b) {
  return a.first - b.first;
}

template<class T>
T sum_pairs(const T& a, const T& b) {
  return std::make_pair(a.first, a.second + b.second);
}
