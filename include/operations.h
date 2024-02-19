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

template<class T>
double dotP(ColumnVector<T> c1, ColumnVector<T> c2);

template<class T>
ColumnVector<T> operator*(T lambda, ColumnVector<T> c);

Matrix operator*(double lambda, Matrix m);

#endif //LA_OPERATIONS_H
