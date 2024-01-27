//
// Created by Dylan Beharall on 25/01/2024.
//

#ifndef LA_COLUMNVECTOR_H
#define LA_COLUMNVECTOR_H
#include <vector>
#include "matrix.h"

class Matrix;

class ColumnVector {
public:
    int height;
    std::vector<double> vector;

    ColumnVector(int h, std::vector<double> v);
    ColumnVector(int h);
    ColumnVector(std::vector<double> v);

    Matrix toMatrix();

    std::string toString();

    ColumnVector operator+(ColumnVector const& obj);

    ColumnVector operator*(double lambda);

    double length();

    bool isUnit();

    ColumnVector normalise();
};

#endif //LA_COLUMNVECTOR_H
