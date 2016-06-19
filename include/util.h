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

template<class InputIterator,class InputIterator2, class OutputIterT, class Function, class T2, class T3>
  OutputIterT for_each_copy(InputIterator first, InputIterator2 last, OutputIterT result, Function fn, T2 x, T3 y)
{
  while (first!=last) {
    *result=fn(*first,x,y);
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

template<class T>
T mul_make_pair(T a, double b) {
  return std::make_pair(a.first, a.second *b);
}

template<class T>
int compare_first(T a, T b) {
  return a.first - b.first;
}

template<class T>
T sum_pairs(T a, T b) {
  return std::make_pair(a.first, a.second + b.second);
}

template<class T>
T sub_pairs(T a, T b) {
  return std::make_pair(a.first, a.second - b.second);
}

template<class T>
T pow(T a,  double b) {
  return std::make_pair(a.first, std::pow(a.second , b));
}

template<class T>
T powTimes(T a, double b, double x) {
  return std::make_pair(a.first, (x+1)*a.second*pow(b , x));
}

template<class T>
T sinus(T a) {
  return std::make_pair(a.first, std::sin(a.second));
}

template<class T>
T cosinus(T a) {
  return std::make_pair(a.first, std::cos(a.second));
}

template<class T>
T ln(T a) {
  return std::make_pair(a.first, std::log(a.second));
}

template<class T>
T expn(T a) {
  return std::make_pair(a.first, std::exp(a.second));
}
