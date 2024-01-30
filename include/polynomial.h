//
// Created by Dylan Beharall on 28/01/2024.
//

#ifndef LA_POLYNOMIAL_H
#define LA_POLYNOMIAL_H
#include <vector>

class Polynomial {
private:
    // Polynomial is represented by a vector of (coefficient, exponent) pairs
    std::vector<std::pair<double, int>> poly;

public:
    Polynomial(std::vector<std::pair<double, int>> cs);

    Polynomial differentiate();

    void print();

    int degree();

    std::vector<double> solve(double equals);
};


#endif //LA_POLYNOMIAL_H
