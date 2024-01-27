//
// Created by Dylan Beharall on 26/01/2024.
//

#ifndef LA_LINEAREQUATION_H
#define LA_LINEAREQUATION_H
#include <vector>
#include <string>

class LinearEquation {
public:
    int n;
    std::vector<double> coefficients;
    double b;

    LinearEquation(int nn, std::vector<double> cs, double bb);
    LinearEquation(std::vector<double> cs, double bb);
    LinearEquation(std::vector<double> cs);

    LinearEquation extendTo(int k);

    std::string toString();
};


#endif //LA_LINEAREQUATION_H
