//
// Created by Dylan Beharall on 25/01/2024.
//

#ifndef LA_COLUMNVECTOR_H
#define LA_COLUMNVECTOR_H
#include <vector>
#include "matrix.h"

class Matrix;

template<class T>
class ColumnVector {
public:
    int height;
    std::vector<T> vector;

    ColumnVector<T>(int h, std::vector<T> v);
    ColumnVector<T>(int h);
    ColumnVector<T>(std::vector<T> v);

    Matrix toMatrix();

    std::string toString();

    ColumnVector<T> operator+(ColumnVector<T> const& obj);

    ColumnVector<T> operator*(T lambda);

    bool operator==(ColumnVector<T> const& obj);

    double length();

    bool isUnit();

    ColumnVector<T> normalise();

    bool operator<(ColumnVector<T> const &obj) const;
};

#endif //LA_COLUMNVECTOR_H
