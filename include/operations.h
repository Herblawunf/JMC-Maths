//
// Created by Dylan Beharall on 25/01/2024.
//

#ifndef LA_OPERATIONS_H
#define LA_OPERATIONS_H
#include "matrix.h"
#include "columnVector.h"

Matrix operator*(Matrix mat1, Matrix mat2);

Matrix operator*(Matrix mat, ColumnVector<double> v);

Matrix operator*(ColumnVector<double> v, Matrix mat);

Matrix operator*(double lambda, Matrix m);

//template<class T>
//inline double dotP(ColumnVector<T> c1, ColumnVector<T> c2);
//
//template<class T>
//ColumnVector<T> operator*(T lambda, ColumnVector<T> c);
//
//#include "../src/operations.cpp"

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
