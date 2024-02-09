//
// Created by Dylan Beharall on 17/01/2024.
//

#ifndef LA_MATRIX_H
#define LA_MATRIX_H
#include "columnVector.h"

class ColumnVector;

class Matrix {
public:
    int height;
    int width;
    std::vector<double> mat;

    Matrix(int h, int w, std::vector<double> m);
    Matrix(int h, int w);

    std::string toString();

    double determinant();

    std::vector<std::vector<double>> generateNested();

    std::vector<std::vector<double>> columns();

    Matrix operator+(Matrix const& obj);

    Matrix operator*(double lambda);

    Matrix r(int i, int j);

    Matrix r(int i, double lambda);

    Matrix r(int i, int j, double lambda);

    double element(int i, int j);

    void insert(double e, int i, int j);

    void print();

    Matrix transpose();

    std::pair<int, double> leadingEntry(int row);

    Matrix augment(ColumnVector v);

    bool isZero();

    Matrix forwardPhase();

    Matrix backwardPhase();

    Matrix rowReduce();

    bool operator==(Matrix const& obj);

    bool isDiagonal();

    bool invertible();

    Matrix inverse();

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
};


#endif //LA_MATRIX_H
