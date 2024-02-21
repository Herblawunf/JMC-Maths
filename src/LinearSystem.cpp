//
// Created by Dylan Beharall on 26/01/2024.
//

#include "../include/LinearSystem.h"
#include "../include/utilities.h"
#include <iostream>

LinearSystem::LinearSystem(std::vector<LinearEquation> es) {
    equations = std::move(es);

    int maxN = 0;

    for (auto e : equations) {
        if (e.n > maxN) maxN = e.n;
    }

    for(int i = 0; i < equations.size(); i++) {
        equations[i] = equations[i].extendTo(maxN);
    }
}

Matrix LinearSystem::coefficientMatrix() {
    std::vector<double> retMat = {};
    int mN = 0;

    for (auto e : equations) {
        mN = e.n;
        retMat.insert(retMat.end(), e.coefficients.begin(), e.coefficients.end());
    }

    return {static_cast<int>(equations.size()), mN, retMat};
}

ColumnVector<double> LinearSystem::results() {
    std::vector<double> v = {};

    for (auto e : equations) {
        v.push_back(e.b);
    }

    return {v};
}

Matrix LinearSystem::augmentedMatrix() {
    return coefficientMatrix().augment(results());
}

std::vector<double> LinearSystem::solutions() {
    Matrix augmented = augmentedMatrix();
    Matrix rowReduced = augmented.rowReduce();

    std::vector<std::vector<double> > nest = rowReduced.generateNested();
    std::vector<std::vector<double> > cols = rowReduced.columns();

    bool zeroRows = all(nest.back(), [](double x) {return x == 0;}) ;

    // No zero rows case
    if (!zeroRows) {
        // Only has one solution if the row reduced coefficient matrix == In
        if (coefficientMatrix().rowReduce() == identityMatrix(coefficientMatrix().width)) {
            return cols.back();
        } else return {NAN}; // Infinite solutions, needs extension for free variables
    } else {
        // If final b is 0, we will recurse, otherwise no solutions
        std::vector<double> res = results().vector;

        if (res.back() == 0) {
            std::vector<LinearEquation> eqs = equations;
            eqs.pop_back();
            return LinearSystem(eqs).solutions();
        } else {
            return {};
        }
    }
}

void LinearSystem::printSolutions() {
    std::vector<double> sols = solutions();

    if (sols[0] == NAN) {
        std::cout << "Infinite solutions" << std::endl;
    } else if (sols.empty()) {
        std::cout << "No solutions" << std::endl;
    } else {
        for (int i = 0; i < sols.size(); i++){
            std::cout << "x" << i + 1 << " = " << sols[i] << std::endl;
        }
    }
}