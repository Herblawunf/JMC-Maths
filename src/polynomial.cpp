//
// Created by Dylan Beharall on 28/01/2024.
//

#include "../include/polynomial.h"
#include "../include/utilities.h"
#include <complex>
#include <iostream>
#include <string>

Polynomial::Polynomial(std::vector<std::pair<double, int>> cs) {
  poly = {};
  int highestExponent = 0;

  for (auto term : cs) {
    if (term.second > highestExponent)
      highestExponent = term.second;
  }

  for (int i = 0; i <= highestExponent; i++) {
    double summedCoefficient = findAllCoefficients(i, cs);

    if (summedCoefficient != 0) {
      poly.push_back({summedCoefficient, i});
    }
  }

  std::sort(poly.begin(), poly.end(),
            [](std::pair<double, int> &a, std::pair<double, int> &b) {
              return b.second > a.second;
            });
}

Polynomial Polynomial::differentiate() {
  std::vector<std::pair<double, int>> newPoly;

  for (auto pair : poly) {
    if (pair.second != 0) {
      std::pair<double, int> add = pair;
      add.first *= pair.second;
      add.second -= 1;
      newPoly.push_back(add);
    }
  }

  return {newPoly};
}

std::string Polynomial::toString() const {
  std::string ret = "";

  for (auto pair : poly) {
    ret += std::to_string(pair.first);
    if (pair.second != 0) {
      ret += "x^" + std::to_string(pair.second);
    }
    ret += " + ";
  }
  ret.pop_back();
  ret.pop_back();

  return ret;
}

void Polynomial::print() { std::cout << this->toString() << std::endl; }

int Polynomial::degree() {
  if (poly.empty())
    return 0;
  return poly.back().second;
}

std::vector<std::complex<double>> Polynomial::solve(double equals) {
  if (degree() == 0) {
    return {};
  } else if (degree() == 1) {
    // Form ax + b = equals
    double a = findAllCoefficients(1, poly);
    double b = findAllCoefficients(0, poly);
    return {(equals - b) / a};
  } else if (degree() == 2) {
    // Form ax^2 + bx + c = 0
    double a = findAllCoefficients(2, poly);
    double b = findAllCoefficients(1, poly);
    double c = findAllCoefficients(0, poly) - equals;

    double x1 = (-b + pow((pow(b, 2) - 4 * a * c), 0.5)) / (2 * a);
    double x2 = (-b - pow((pow(b, 2) - 4 * a * c), 0.5)) / (2 * a);

    return {x1, x2};
  } else if (degree() == 3) {
    // Here goes nothing
    double a = findAllCoefficients(3, poly);
    double b = findAllCoefficients(2, poly);
    double c = findAllCoefficients(1, poly);
    double d = findAllCoefficients(0, poly) - equals;

    std::complex<double> d0 = pow(b, 2) - 3.0 * a * c;
    std::complex<double> d1 = 2.0 * pow(b, 3) - 9.0 * a * b * c + 27.0 * pow(a, 2) * d;

    std::complex<double> bigC =
        pow(((d1 + pow((pow(d1, 2) - 4.0 * pow(d0, 3)), 0.5)) / 2.0), 1.0 / 3.0);

    bigC = bigC == 0.0
               ? pow(((d1 - pow((pow(d1, 2) - 4.0 * pow(d0, 3)), 0.5)) / 2.0),
                     1.0 / 3.0)
               : bigC;

    std::complex<double> epsilon = {-0.5, sqrt(3.0) / 2.0};

    std::cout << epsilon << bigC << static_cast<int>(bigC == 0.0) << std::endl;

    if (bigC == 0.0) {
      double root = -b / 3 * a;
      return {root, root, root};
    }

    std::complex<double> x0 = (-1 / (3 * a)) * (b + bigC + d0 / bigC);
    std::complex<double> x1 =
        (-1 / (3 * a)) * (b + epsilon * bigC + d0 / (epsilon * bigC));
    std::complex<double> x2 =
        (-1 / (3 * a)) *
        (b + epsilon * epsilon * bigC + d0 / (epsilon * epsilon * bigC));

    return {x0, x1, x2};

  } else {
    // Durand-Kerner method will be used to approximate polynomial roots

    Polynomial newPoly = *this - toPolynomial(equals);

    std::vector<std::vector<std::complex<double>>> iterations = {};
    std::complex<double> initial = {0.4, 0.9};

    for (int i = 0; i < degree(); i++) {
      iterations.push_back({});
      iterations[i].push_back(pow(initial, i));
    }

    for (int i = 0; i < 200; i++) {
      for (int j = 0; j < degree(); j++) {
        std::complex<double> numerator = newPoly.evaluate(iterations[j][i]);
        std::complex<double> denominator = 1;

        for (int k = 0; k < degree(); k++) {
          if (k != j) {
            denominator *= iterations[j][i] - iterations[k].back();
          }
        }
        std::complex<double> nextIteration =
            iterations[j][i] - (numerator / denominator);

        iterations[j].push_back(nextIteration);
      }
    }

    std::vector<std::complex<double>> ret = {};

    for (auto iter : iterations) {
      ret.push_back(iter.back());
    }

    return ret;
  }
  throw std::invalid_argument("Order too high to solve");
}

Polynomial Polynomial::operator+(const Polynomial &obj) {
  std::vector<std::pair<double, int>> concat = this->poly;

  concat.insert(concat.end(), obj.poly.begin(), obj.poly.end());
  return {concat};
}

Polynomial Polynomial::operator*(const Polynomial &obj) {
  std::vector<std::pair<double, int>> accumulator = {};

  for (auto term : poly) {
    std::vector<std::pair<double, int>> adder = {};

    for (auto term2 : obj.poly) {
      adder.push_back(
          std::pair(term.first * term2.first, term.second + term2.second));
    }

    accumulator.insert(accumulator.end(), adder.begin(), adder.end());
  }

  return {accumulator};
}

std::ostream &operator<<(std::ostream &os, const Polynomial &obj) {
  return os << obj.toString();
}

Polynomial Polynomial::operator-(const Polynomial &obj) {
  return *this + (Polynomial({{-1, 0}}) * obj);
}

std::complex<double> Polynomial::evaluate(std::complex<double> x) {
  std::complex<double> ret = 0;

  for (auto term : poly) {
    ret += term.first * pow(x, term.second);
  }

  return ret;
}
