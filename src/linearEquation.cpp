//
// Created by Dylan Beharall on 26/01/2024.
//

#include "../include/linearEquation.h"
#include "../include/utilities.h"

LinearEquation::LinearEquation(std::vector<double> cs) {
    n = cs.size();
    b = 0;
    coefficients = std::move(cs);
}

LinearEquation::LinearEquation(std::vector<double> cs, double bb) {
    n = cs.size();
    b = bb;
    coefficients = std::move(cs);
}

LinearEquation::LinearEquation(int nn, std::vector<double> cs, double bb) {
    if (nn != cs.size()) throw std::invalid_argument( "Number of variables doesn't match coefficients" );

    n = nn;
    b = bb;
    coefficients = std::move(cs);
}

LinearEquation LinearEquation::extendTo(int k) {
    if (k < n) {
        throw std::invalid_argument( "Cannot extend equation to a shorter length" );
    }

    std::vector<double> adder = std::vector<double>(k - n);
    std::vector<double> ret = coefficients;
    ret.insert(ret.end(), adder.begin(), adder.end());

    return {k, ret, b};
}

std::string LinearEquation::toString() {
    std::vector<std::string> strings = {};

    for(int i = 0; i < coefficients.size(); i++) {
        strings.push_back(std::to_string(coefficients[i]) + "x" + std::to_string(i + 1));
    }

    return joinWith(strings, " + ") + " = " + std::to_string(b);
}