//
// Created by Dylan Beharall on 28/01/2024.
//

#pragma once
#include <complex>
#include <string>
#include <vector>

class Polynomial {
private:
  // Polynomial is represented by a vector of (coefficient, exponent) pairs
  std::vector<std::pair<double, int>> poly;

public:
  Polynomial(std::vector<std::pair<double, int>> cs);

  Polynomial differentiate();

  std::string toString() const;

  void print();

  int degree();

  std::vector<std::complex<double>> solve(double equals);

  Polynomial operator+(Polynomial const &obj);

  Polynomial operator*(Polynomial const &obj);

  friend std::ostream &operator<<(std::ostream &os, const Polynomial &obj);

  Polynomial operator-(Polynomial const &obj);

  std::complex<double> evaluate(std::complex<double> x);
};

