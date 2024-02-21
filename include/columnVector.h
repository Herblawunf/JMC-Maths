//
// Created by Dylan Beharall on 25/01/2024.
//

#ifndef LA_COLUMNVECTOR_H
#define LA_COLUMNVECTOR_H
#include <vector>
#include "matrix.h"

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

    void print();

    ColumnVector<T> operator+(ColumnVector<T> const& obj);

    ColumnVector<T> operator*(T lambda);

    bool operator==(ColumnVector<T> const& obj);

    bool operator!=(ColumnVector<T> const& obj);

    double length() const;

    bool isUnit();

    ColumnVector<T> normalise();

    bool operator<(ColumnVector<T> const &obj) const;
};

#include "../src/columnVector.cpp"

#endif //LA_COLUMNVECTOR_H
