//
// Created by Dylan Beharall on 25/01/2024.
//

#ifndef OPERATIONS_FUNCTIONS
#define OPERATIONS_FUNCTIONS
#include "../include/operations.h"

Matrix operator*(Matrix mat1, Matrix mat2) {
    if (mat1.width != mat2.height) {
        throw std::invalid_argument( "Wrong dimensions for matrix multiplication" );
    }

    std::vector<std::vector<double> > n1= mat1.generateNested();
    std::vector<std::vector<double> > n2= mat2.generateNested();
    std::vector<double> ret = {};

    for (int i = 0; i < mat1.height; i++) {
        for (int j = 0; j < mat2.width; j++) {
            double add = 0;

            for (int k = 0; k < mat1.width; k++) {
                add += n1[i][k] * n2[k][j];
            }

            ret.push_back(add);
        }
    }

    return {mat1.height, mat2.width, ret};
}

Matrix operator*(Matrix mat, ColumnVector<double> v) {
    return mat * v.toMatrix();
}

Matrix operator*(ColumnVector<double> v, Matrix mat) {
    return v.toMatrix() * mat;
}

Matrix operator*(double lambda, Matrix m) {
    return m * lambda;
}

#endif