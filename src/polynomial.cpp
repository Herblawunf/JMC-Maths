//
// Created by Dylan Beharall on 28/01/2024.
//

#include "../include/polynomial.h"
#include <string>
#include <iostream>

Polynomial::Polynomial(std::vector<std::pair<double, int>> cs) {
    poly = std::move(cs);

    std::sort(poly.begin(),
              poly.end(),
              [](std::pair<double, int> &a, std::pair<double, int> &b){ return b.second > a.second; });
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

void Polynomial::print() {
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

    std::cout << ret << std::endl;
}