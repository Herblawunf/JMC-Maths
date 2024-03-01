//
// Created by Dylan Beharall on 28/01/2024.
//

#include "../include/polynomial.h"
#include "../include/utilities.h"
#include <string>
#include <iostream>
#include <complex>


Polynomial::Polynomial(std::vector<std::pair<double, int> > cs) {
    poly = {};
    int highestExponent = 0;

    for (auto term : cs) {
        if (term.second > highestExponent) highestExponent = term.second;
    }

    for (int i = 0; i <= highestExponent; i++) {
        double summedCoefficient = findAllCoefficients(i, cs);

        if (summedCoefficient != 0) {
            poly.push_back({summedCoefficient, i});
        }
    }

    std::sort(poly.begin(),
              poly.end(),
              [](std::pair<double, int> &a, std::pair<double, int> &b){ return b.second > a.second; });
}

Polynomial Polynomial::differentiate() {
    std::vector<std::pair<double, int> > newPoly;

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

void Polynomial::print() {
    std::cout << this->toString() << std::endl;
}

int Polynomial::degree() {
    if (poly.empty()) return 0;
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

        double x1 = (- b + pow((pow(b, 2) - 4*a*c), 0.5)) / (2 * a);
        double x2 = (- b - pow((pow(b, 2) - 4*a*c), 0.5)) / (2 * a);

        return {x1, x2};
    } else if (degree() == 3) {
        // Here goes nothing
        double a = findAllCoefficients(3, poly);
        double b = findAllCoefficients(2, poly);
        double c = findAllCoefficients(1, poly);
        double d = findAllCoefficients(0, poly) - equals;

        double d0 = pow(b, 2) - 3*a*c;
        double d1 = 2*pow(b, 3) - 9*a*b*c + 27*pow(a, 2)*d;

        double bigC = pow(((d1 + pow((pow(d1, 2) - 4*pow(d0, 3)), 0.5)) / 2.0), 1.0/3.0);

        bigC = bigC == 0 ? pow(((d1 - pow((pow(d1, 2) - 4*pow(d0, 3)), 0.5)) / 2.0), 1.0/3.0) : bigC;

        // First root
        // double x0 = bigC == 0 ? - b / (3 * a) : (b + bigC + d0 / bigC) / (-3 * a);

        std::complex<double> epsilon = {-0.5, sqrt(3.0) / 2.0};

        std::complex<double> x0 = (-1 / (3*a)) * (b + bigC + d0 / bigC);
        std::complex<double> x1 = (-1 / (3*a)) * (b + epsilon * bigC + d0 / (epsilon * bigC));
        std::complex<double> x2 = (-1 / (3*a)) * (b + epsilon * epsilon * bigC + d0 / (epsilon * epsilon * bigC));

        return {x0, x1, x2};

        throw std::invalid_argument( "Order too high to solve" );
    }
    throw std::invalid_argument( "Order too high to solve" );
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
            adder.push_back(std::pair(term.first * term2.first, term.second + term2.second));
        }

        accumulator.insert(accumulator.end(), adder.begin(), adder.end());
    }

    return {accumulator};
}

std::ostream& operator<<(std::ostream& os, const Polynomial& obj) {
    return os << obj.toString();
}

Polynomial Polynomial::operator-(const Polynomial &obj) {
    return *this + (Polynomial({{-1, 0}}) * obj);
}