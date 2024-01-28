//
// Created by Dylan Beharall on 28/01/2024.
//

#include "../include/polynomial.h"

Polynomial::Polynomial(std::vector<double> cs) {
    coefficients = std::move(cs);
}