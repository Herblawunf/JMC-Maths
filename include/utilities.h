//
// Created by Dylan Beharall on 25/01/2024.
//

#ifndef LA_UTILITIES_H
#define LA_UTILITIES_H
#include "polynomial.h"
// #include "matrix.h"
#include <iostream>
#include <set>
#include <string>
#include <type_traits>

template <class T> class Matrix;
template <class T> class ColumnVector;

ColumnVector<double> e(int e, int r);

double distance(ColumnVector<double> u, ColumnVector<double> v);

Matrix<double> identityMatrix(int n);

std::string joinWith(std::vector<double> v, std::string j);

std::string joinWith(std::vector<std::string> v, std::string j);

double findAllCoefficients(int x, std::vector<std::pair<double, int>> pairs);

template <class T> Polynomial toPolynomial(T x) {
  if (!std::is_arithmetic_v<T>) {
    throw std::invalid_argument(
        "Only arithmetic types can be converted to polynomial");
  }

  return {{{static_cast<double>(x), 0}}};
}

template <class T> std::vector<T> concat(std::vector<T> v1, std::vector<T> v2) {
  std::vector<T> r = {};
  for (auto v : v1)
    r.push_back(v);

  for (auto v : v2)
    r.push_back(v);

  return r;
}

template <class T> std::vector<T> flatten(std::vector<std::vector<T>> v) {
  std::vector<T> ret = {};

  for (auto vec : v) {
    ret.insert(ret.end(), vec.begin(), vec.end());
  }

  return ret;
}

template <typename T> void print(std::vector<T> vec) {
  std::cout << "[ ";
  for (int i = 0; i < vec.size() - 1; i++) {
    std::cout << vec[i] << ", ";
  }
  std::cout << vec.back() << " ]" << std::endl;
}

template <class T> constexpr bool isArithmetic() {
  return std::is_arithmetic_v<T>;
}

template <class T> bool all(std::vector<T> v, bool (*func)(T)) {
  std::vector<T> copy = v;
  if (v.size() == 0)
    return true;
  T last = v.back();
  copy.pop_back();
  return func(last) && all(copy, func);
}

// template <class T>
// std::enable_if_t<std::is_same_v<T, Polynomial>, T> additiveIdentity() {
//     return T({});  // Construct an empty Polynomial
// }

template <class T> T additiveIdentity() {
  if constexpr (std::is_same_v<T, Polynomial>) {
    return Polynomial({});
  }
  if constexpr (isArithmetic<T>()) {
    return 0.0;
  }

  throw std::invalid_argument("Additive identity cannot be found");
}

#endif // LA_UTILITIES_H
