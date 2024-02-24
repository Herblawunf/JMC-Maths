//
// Created by Dylan Beharall on 28/01/2024.
//

#ifndef LA_POLYNOMIAL_H
#define LA_POLYNOMIAL_H
#include <vector>
#include <string>

class Polynomial {
private:
    // Polynomial is represented by a vector of (coefficient, exponent) pairs
    std::vector<std::pair<double, int> > poly;

public:
    Polynomial(std::vector<std::pair<double, int> > cs);

    Polynomial differentiate();

    std::string toString() const;

    void print();

    int degree();

    std::vector<double> solve(double equals);

    Polynomial operator+(Polynomial const& obj);

    Polynomial operator*(Polynomial const& obj);

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& obj);

    Polynomial operator-(Polynomial const& obj);
};


#endif //LA_POLYNOMIAL_H
