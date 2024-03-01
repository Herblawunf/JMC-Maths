//
// Created by Dylan Beharall on 25/01/2024.
//

#ifndef LA_OPERATIONS_H
#define LA_OPERATIONS_H
#include "matrix.h"
#include "columnVector.h"

template<class T>
Matrix<T> operator*(Matrix<T> mat1, Matrix<T> mat2) {
    if (mat1.width != mat2.height) {
        throw std::invalid_argument( "Wrong dimensions for matrix multiplication" );
    }

    std::vector<std::vector<T> > n1 = mat1.generateNested();
    std::vector<std::vector<T> > n2 = mat2.generateNested();
    std::vector<T> ret = {};

    for (int i = 0; i < mat1.height; i++) {
        for (int j = 0; j < mat2.width; j++) {
            T add = additiveIdentity<T>();

            for (int k = 0; k < mat1.width; k++) {
                add += n1[i][k] * n2[k][j];
            }

            ret.push_back(add);
        }
    }

    return {mat1.height, mat2.width, ret};
}

template<class T>
Matrix<T> operator*(Matrix<T> mat, ColumnVector<T> v) {
    return mat * v.toMatrix();
}

template<class T>
Matrix<T> operator*(ColumnVector<T> v, Matrix<T> mat) {
    return v.toMatrix() * mat;
}

template<class T>
Matrix<T> operator*(T lambda, Matrix<T> m) {
    return m * lambda;
}

template<class T>
inline double dotP(ColumnVector<T> c1, ColumnVector<T> c2) {
    if (c1.height != c2.height) {
        throw std::invalid_argument( "Vectors with different heights cannot have a dot product" );
    }
    if (!std::is_arithmetic_v<T>) {
        throw std::invalid_argument("Dot product can only be taken of vectors of arithmetic type");
    }
    double dot = 0;
    for(int i = 0; i < c1.height; i++) dot += c1.vector[i] * c2.vector[i];
    return dot;
}

template<class T>
ColumnVector<T> operator*(T lambda, ColumnVector<T> c) {
    return c * lambda;
}

#endif //LA_OPERATIONS_H
