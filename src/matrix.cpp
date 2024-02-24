//
// Created by Dylan Beharall on 17/01/2024.
//

#ifndef MATRIX_FUNCTIONS
#define MATRIX_FUNCTIONS

#include "../include/matrix.h"
#include "../include/utilities.h"
#include "../include/operations.h"
#include "../include/vectorSets.h"
#include <iostream>
#include <utility>
#include <vector>
#include <sstream>

template<class T>
Matrix<Polynomial> matrixToPolynomial(Matrix<T> m) {
    if (!isArithmetic<T>()) {
        throw std::invalid_argument("Only matrices of arithmetic types can be converted to polynomial");
    }
    std::vector<Polynomial> poly;
    for (auto e : m.mat) {
        poly.push_back(toPolynomial(e));
    }
    return {m.height, m.width, poly};
}

template<class T>
Matrix<T>::Matrix(int h, int w, std::vector<T> m) {
    height = h;
    width = w;
    mat = std::move(m);

    if (mat.size() > (height * width)) {
        std::cout << mat.size() << std::endl;
        throw std::invalid_argument ( "Length of vector too long" );
    }
}

template<class T>
Matrix<T>::Matrix(int h, int w) {
    height = h;
    width = w;
    mat = std::vector<T>(h * w);
}

template<class T>
std::string Matrix<T>::toString() {
    std::string ret;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::stringstream ss;
            ss << mat[i * width + j];
            ret += ss.str() + " ";
        }
        ret += "\n";
    }

    return ret;
}

template<class T>
T Matrix<T>::determinant() {
    if (height != width) {
        throw std::invalid_argument ("Determinant can only be calculated of square matrix");
    } else if (height == 1) return mat[0];

    std::vector<std::vector<T> > nested = generateNested();
    std::vector<T> first = nested[0];
    nested.erase(nested.begin());
    T det = additiveIdentity<T>();

    for (int i = 0; i < first.size(); i++) {
        std::vector<T> m = {};
        for (auto v : nested) {
            v.erase(v.begin() + i);
            m.insert(m.end(), v.begin(), v.end());
        }

        Matrix<T> inside = Matrix<T>(height - 1, width - 1, m);

        if (i % 2 == 1) {
            det = det - first[i] * inside.determinant();
        } else {
            det = det + first[i] * inside.determinant();
        }

    }

    return det;
}

template<class T>
std::vector<std::vector<T> > Matrix<T>::generateNested() {
    std::vector<std::vector<T> > ret = {};

    for (int i = 0; i < height; i++) {
        std::vector<T> temp = {};
        for (int j = 0; j < width; j++) {
            temp.push_back(mat[i*width + j]);
        }
        ret.push_back(temp);
    }

    return ret;
}

template<class T>
std::vector<std::vector<T> > Matrix<T>::columns() {
    std::vector<std::vector<T> > ret = {};
    std::vector<std::vector<T> > nest = generateNested();

    for (int i = 0; i < width; i++) {
        std::vector<T> temp = {};
        for (int j = 0; j < height; j++) {
            temp.push_back(nest[j][i]);
        }
        ret.push_back(temp);
    }

    return ret;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &obj) {
    if (height != obj.height || width != obj.width) {
        throw std::invalid_argument( "Matrices must be the same dimensions to add" );
    }
    std::vector<T> result = obj.mat;

    for (int i = 0; i < result.size(); i++) {
        result[i] = result[i] + mat[i];
    }

    return {height, width, result};
}

template<class T>
Matrix<T> Matrix<T>::operator*(T lambda) {
    std::vector<T> newMat = mat;
    for (int i = 0; i < height * width; i++) newMat[i] = newMat[i] * lambda;
    return {height, width, newMat};
}

template<class T>
Matrix<T> Matrix<T>::r(int i, int j) {
    if (i < 1 || j < 1 || i > height || j > height) {
        throw std::invalid_argument
                ( "Rows out of bounds for matrix " + std::to_string(i) + " " + std::to_string(j));
    }
    std::vector<T> newMat = mat;

    for (int k = 0; k < width; k++) {
        newMat[(i - 1) * width + k] = mat[(j - 1) * width + k];
        newMat[(j - 1) * width + k] = mat[(i - 1) * width + k];
    }
    return {height, width, newMat};
}

template<class T>
Matrix<T> Matrix<T>::r(int i, T lambda) {
    if (i < 1 || i > height) throw std::invalid_argument
    ( "Row out of bounds for matrix " + std::to_string(i));

    std::vector<T> newMat = mat;
    for (int k = 0; k < width; k++) {
        newMat[(i - 1) * width + k] *= lambda;
    }
    return {height, width, newMat};
}

template<class T>
Matrix<T> Matrix<T>::r(int i, int j, T lambda) {
    if (i < 1 || j < 1 || i > height || j > height) {
        throw std::invalid_argument
        ( "Rows out of bounds for matrix " + std::to_string(i) + " " + std::to_string(j));
    }
    std::vector<T> newMat = mat;

    for (int k = 0; k < width; k++) {
        newMat[(j - 1) * width + k] = newMat[(j - 1) * width + k] + mat[(i - 1) * width + k] * lambda;
    }
    return {height, width, newMat};
}

template<class T>
T Matrix<T>::element(int i, int j) {
    int ind = (i - 1) * width + j - 1;

    if (i < 1 || j < 1 || ind >= height * width) {
        throw std::invalid_argument( "Accessing element out of bounds" );
    }

    return mat[ind];
}

template<class T>
void Matrix<T>::insert(T e, int i, int j) {
    int ind = (i - 1) * width + j - 1;

    if (i < 1 || j < 1 || ind >= height * width) {
        throw std::invalid_argument( "Inserting element position out of bounds" );
    }

    mat[ind] = e;
}

template<class T>
void Matrix<T>::print() {
    std::cout << toString() << std::endl;
}

template<class T>
Matrix<T> Matrix<T>::transpose() {
    Matrix<T> retMat = Matrix<T>(width, height, mat);

    for(int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            retMat.insert(this->element(i, j), j, i);
        }
    }

    return retMat;
}

template<class T>
Matrix<T> Matrix<T>::augment(ColumnVector<T> v) {
    if(v.height != height) {
        throw std::invalid_argument( "Can only augment matrix and vector of the same height" );
    }
    std::vector<T> newMat = {};
    std::vector<std::vector<T> > nest = generateNested();
    for(int i = 0; i < nest.size(); i++) {
        nest[i].push_back(v.vector[i]);
        newMat.insert(newMat.end(), nest[i].begin(), nest[i].end());
    }
    return {height, width + 1, newMat};
}

template<class T>
bool Matrix<T>::isZero() {
    for (auto element : mat) {
        if (element != additiveIdentity<T>()) return false;
    }
    return true;
}

template<class T>
std::pair<int, T> Matrix<T>::leadingEntry(int row) {
    std::vector<T> rw = generateNested()[row - 1];

    for (int i = 0; i < rw.size(); i++) {
        if (rw[i] != additiveIdentity<T>()) return {i + 1, rw[i]};
    }

    return {0, additiveIdentity<T>()};
}

template<class T>
Matrix<double> Matrix<T>::forwardPhase() {
    Matrix<double> ret = Matrix<double>(height, width, mat);

    // Base case
    if (isZero()) return ret;

    if (height == 1) {
        std::pair<int, T> p = leadingEntry(1);
        ret = ret.r(1, 1/p.second);
        return ret;
    }

    // Find pivot position
    std::pair<int, int> pivot = {0, width + 1};
    double pivotVal;
    for (int i = 1; i <= height; i++) {
        std::pair <int, double> lead = leadingEntry(i);
        if(lead.first < pivot.second) {
            pivot = {i, lead.first};
            pivotVal = lead.second;
        }
    }

    // Swapping pivot value to first row
    if (pivot.first == 0) return ret;
    ret = ret.r(1, pivot.first);

    // Multiply row 1 by 1 / pivotVal
    ret = ret.r(1, 1 / pivotVal);

    // Make zeroes below the pivotVal
    for (int j = 2; j <= height; j++) {
        double ele = ret.element(j, pivot.second);
        ret = ret.r(1, j, -ele);
    }

    if (width == 1) return ret;

    // Repeat for nested matrix
    std::vector<std::vector<double> > nest = ret.generateNested();
    std::vector<std::vector<double> > backup = nest;
    nest.erase(nest.begin());
    for (auto & i : nest) {
        i.erase(i.begin(), i.begin() + pivot.second);
    }
    Matrix b = Matrix(height - 1, width - pivot.second, flatten(nest));
    Matrix forwardB = b.forwardPhase();

    std::vector<std::vector<double> > newNest = forwardB.generateNested();

    for (int i = 1; i < height; i++) {
        for (int j = 0; j < forwardB.width; j++) {
            backup[i].pop_back();
        }

        backup[i] = concat(backup[i], newNest[i - 1]);
    }

    return {height, width, flatten(backup)};
}

template<class T>
Matrix<double> Matrix<T>::backwardPhase() {
    // Requires Matrix to already be in echelon form via forward phase
    Matrix<double> ret = Matrix<double>(height, width, mat);

    for(int i = 1; i <= height; i++) {
        std::pair<int, T> p = ret.leadingEntry(i);
        if(p.first == 0) return ret;
        int column = p.first;

        for(int j = 1; j < i; j++) {
            T ele = ret.element(j, column);

            ret = ret.r(i, j, -ele);
        }
    }
    return ret;
}

template<class T>
Matrix<double> Matrix<T>::rowReduce() {
    if(!isArithmetic<T>()) {
        throw std::invalid_argument( "Can only row reduce a matrix of arithmetic type" );
    }

    Matrix<T> ret = Matrix<T>(height, width, mat);

    return ret.forwardPhase().backwardPhase();
}

template<class T>
bool Matrix<T>::operator==(const Matrix<T> &obj) {
    bool checker = true;
    if(height != obj.height || width != obj.width) {
        return false;
    }

    for (int i = 0; i < height * width; i++) {
        if (mat[i] != obj.mat[i]) return false;
    }
    return true;
}

template<class T>
bool Matrix<T>::operator!=(const Matrix<T> &obj) {
    return !(*this == obj);
}

template<class T>
bool Matrix<T>::isDiagonal() {
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            if (i != j && element(i, j) != additiveIdentity<T>()) return false;
        }
    }

    return true;
}

template<class T>
bool Matrix<T>::invertible() {
    return height == width && determinant() != additiveIdentity<T>();
}

template<class T>
Matrix<double> Matrix<T>::inverse() {
    if (!isArithmetic<T>()) {
        throw std::invalid_argument("Can only calculate inverse of matrix of arithmetic type");
    }

    // First, compute the augmented matrix A | In
    if (!invertible()) {
        throw std::invalid_argument( "Matrix not invertible" );
    }

    Matrix<double> aug = {height, width, mat};
    Matrix<double> id = identityMatrix(height);

    for (auto col : id.columns()) {
        aug = aug.augment(ColumnVector<double>(col));
    }
    // Step 2, row reduce the augmented matrix
    Matrix<double> rowReduced = aug.rowReduce();

    // Step 3, obtain the final n columns as A-1
    Matrix<double> inv = {height, 0, {}};

    for(int i = width; i < 2 * width; i++) {
        inv = inv.augment(ColumnVector<double>(rowReduced.columns()[i]));
    }

    return inv;
}

// Freddie05: Implemented isSquare function
template<class T>
bool Matrix<T>::isSquare() {
    return height == width;
}

// Shaowy05: Implementing upper and lower triangular functions
template<class T>
bool Matrix<T>::isUpperTriangular() {
    if (!isSquare()) return false;

    bool isUpperTriangular = true;

    for (int i = 2; i <= height; i++) {
        for (int j = 1; j <= i - 1; j++) {
            if (element(i, j) != additiveIdentity<T>()) isUpperTriangular = false;
        }
    }

    return isUpperTriangular;
}

template<class T>
bool Matrix<T>::isStrictlyUpperTriangular() {

    if (!isSquare()) return false;

    bool isUpperTriangular = true;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= i; j++) {
            if (element(i, j) != additiveIdentity<T>()) isUpperTriangular = false;
        }
    }

    return isUpperTriangular;

}

// Using the transpose() method to define Lower Triangular methods
template<class T>
bool Matrix<T>::isLowerTriangular() {
    Matrix<T> t = this->transpose();
    return t.isUpperTriangular();
}

template<class T>
bool Matrix<T>::isStrictlyLowerTriangular() {
    Matrix<T> t = this->transpose();
    return t.isStrictlyUpperTriangular();
}

template<class T>
bool Matrix<T>::isOrthogonal() {
    // return (*this) * transpose() == identity(width);

    std::set<ColumnVector<T> > cs;
    for(auto col : columns()) {
        cs.insert(ColumnVector<T>(col));
    }
    return orthogonal<T>(cs);
}

template<class T>
bool Matrix<T>::isOrthonormal() {
    std::set<ColumnVector<T> > cs;
    for(auto col : columns()) {
        cs.insert(ColumnVector<T>(col));
    }
    return orthonormal<T>(cs);
}

template<class T>
bool Matrix<T>::isSymmetric() {
    return (*this) == transpose();
}

template<class T>
bool Matrix<T>::isEigenvalue(double lambda) {
    if (!isArithmetic<T>()) {
        throw std::invalid_argument("Can only check for eigenvalue if of arithmetic type");
    }

    Matrix<double> m = *this + (- lambda) * identityMatrix(height);
    return !m.invertible();
}

template<class T>
std::vector<double> Matrix<T>::eigenvalues() {
    if (!isSquare()) {
        throw std::invalid_argument("Only square matrices have eigenvalues");
    }
    if (!isArithmetic<T>()) {
        throw std::invalid_argument("Eigenvalues can only be calculated for matrix of arithmetic type");
    }
    Matrix<Polynomial> asPoly = matrixToPolynomial(*this);
    Matrix<Polynomial> id = matrixToPolynomial(identityMatrix(height));
    id = Polynomial({{-1, 1}}) * id;

    asPoly = asPoly + id;

    Polynomial characteristicPolynomial = asPoly.determinant();

    return characteristicPolynomial.solve(0);
}

#endif