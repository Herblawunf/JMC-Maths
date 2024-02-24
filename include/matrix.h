//
// Created by Dylan Beharall on 17/01/2024.
//

#ifndef LA_MATRIX_H
#define LA_MATRIX_H
#include <vector>
#include "polynomial.h"

template<class T> class ColumnVector;

template<class T>
class Matrix {
public:
    int height;
    int width;
    std::vector<T> mat;

    Matrix(int h, int w, std::vector<T> m);
    Matrix(int h, int w);

    std::string toString();

    T determinant();

    std::vector<std::vector<T> > generateNested();

    std::vector<std::vector<T> > columns();

    Matrix<T> operator+(Matrix<T> const& obj);

    Matrix<T> operator*(T lambda);

    Matrix<T> r(int i, int j);

    Matrix<T> r(int i, T lambda);

    Matrix<T> r(int i, int j, T lambda);

    T element(int i, int j);

    void insert(T e, int i, int j);

    void print();

    Matrix<T> transpose();

    std::pair<int, T> leadingEntry(int row);

    Matrix<T> augment(ColumnVector<T> v);

    bool isZero();

    Matrix<double> forwardPhase();

    Matrix<double> backwardPhase();

    Matrix<double> rowReduce();

    bool operator==(Matrix<T> const& obj);

    bool operator!=(Matrix<T> const& obj);

    bool isDiagonal();

    bool invertible();

    Matrix<double> inverse();

    // Shaowy05: Is Square
    bool isSquare();

    // Shaowy05: Upper and Lower Triangular Matrices
    bool isUpperTriangular();

    bool isStrictlyUpperTriangular();

    bool isLowerTriangular();

    bool isStrictlyLowerTriangular();

    // Herblawunf: Orthonormal and Orthogonal

    bool isOrthogonal();

    bool isOrthonormal();

    bool isSymmetric();

    bool isEigenvalue(double lambda);

    std::vector<double> eigenvalues();
};


#include "../src/matrix.cpp"

#endif //LA_MATRIX_H
