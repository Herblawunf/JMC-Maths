//
// Created by Dylan Beharall on 25/01/2024.
//

#ifndef LA_OPERATIONS_H
#define LA_OPERATIONS_H
#include "matrix.h"
#include "columnVector.h"

Matrix operator*(Matrix mat1, Matrix mat2);

Matrix operator*(Matrix mat, ColumnVector v);

Matrix operator*(ColumnVector v, Matrix mat);

double dotP(ColumnVector c1, ColumnVector c2);

ColumnVector operator*(double lambda, ColumnVector c);

Matrix operator*(double lambda, Matrix m);

#endif //LA_OPERATIONS_H
