//
// Created by Dylan Beharall on 17/01/2024.
//

#include "../include/matrix.h"
#include "../include/utilities.h"
#include "../include/operations.h"
#include "../include/vectorSets.h"
#include <iostream>
#include <utility>
#include <vector>

Matrix::Matrix(int h, int w, std::vector<double> m) {
    height = h;
    width = w;
    mat = std::move(m);

    if (mat.size() > (height * width)) {
        std::cout << mat.size() << std::endl;
        throw std::invalid_argument ( "Length of vector too long" );
    }
}

Matrix::Matrix(int h, int w) {
    height = h;
    width = w;
    mat = std::vector<double>(h * w);
}

std::string Matrix::toString() {
    std::string ret;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ret += std::to_string(mat[i * width + j]) + " ";
        }
        ret += "\n";
    }

    return ret;
}

double Matrix::determinant() {
    if (height != width) {
        return NAN;
    } else if (height == 0) return 1.0;

    std::vector<std::vector<double>> nested = generateNested();
    std::vector<double> first = nested[0];
    nested.erase(nested.begin());
    double det = 0.0;

    for (int i = 0; i < first.size(); i++) {
        std::vector<double> m = {};
        for (auto v : nested) {
            v.erase(v.begin() + i);
            m.insert(m.end(), v.begin(), v.end());
        }

        Matrix inside = Matrix(height - 1, width - 1, m);
        det += pow(-1, i) * first[i] * inside.determinant();
    }

    return det;
}

std::vector<std::vector<double>> Matrix::generateNested() {
    std::vector<std::vector<double>> ret = {};

    for (int i = 0; i < height; i++) {
        std::vector<double> temp = {};
        for (int j = 0; j < width; j++) {
            temp.push_back(mat[i*width + j]);
        }
        ret.push_back(temp);
    }

    return ret;
}

std::vector<std::vector<double>> Matrix::columns() {
    std::vector<std::vector<double>> ret = {};
    std::vector<std::vector<double>> nest = generateNested();

    for (int i = 0; i < width; i++) {
        std::vector<double> temp = {};
        for (int j = 0; j < height; j++) {
            temp.push_back(nest[j][i]);
        }
        ret.push_back(temp);
    }

    return ret;
}

Matrix Matrix::operator+(const Matrix &obj) {
    if (height != obj.height || width != obj.width) {
        throw std::invalid_argument( "Matrices must be the same dimensions to add" );
    }
    std::vector<double> result = obj.mat;

    for (int i = 0; i < result.size(); i++) {
        result[i] += mat[i];
    }

    return {height, width, result};
}

Matrix Matrix::operator*(double lambda) {
    std::vector<double> newMat = mat;
    for (int i = 0; i < height * width; i++) newMat[i] *= lambda;
    return {height, width, newMat};
}

Matrix Matrix::r(int i, int j) {
    if (i < 1 || j < 1 || i > height || j > height) {
        throw std::invalid_argument
                ( "Rows out of bounds for matrix " + std::to_string(i) + " " + std::to_string(j));
    }
    std::vector<double> newMat = mat;

    for (int k = 0; k < width; k++) {
        newMat[(i - 1) * width + k] = mat[(j - 1) * width + k];
        newMat[(j - 1) * width + k] = mat[(i - 1) * width + k];
    }
    return {height, width, newMat};
}

Matrix Matrix::r(int i, double lambda) {
    if (i < 1 || i > height) throw std::invalid_argument
    ( "Row out of bounds for matrix " + std::to_string(i));

    std::vector<double> newMat = mat;
    for (int k = 0; k < width; k++) {
        newMat[(i - 1) * width + k] *= lambda;
    }
    return {height, width, newMat};
}

Matrix Matrix::r(int i, int j, double lambda) {
    if (i < 1 || j < 1 || i > height || j > height) {
        throw std::invalid_argument
        ( "Rows out of bounds for matrix " + std::to_string(i) + " " + std::to_string(j));
    }
    std::vector<double> newMat = mat;

    for (int k = 0; k < width; k++) {
        newMat[(j - 1) * width + k] += mat[(i - 1) * width + k] * lambda;
    }
    return {height, width, newMat};
}

double Matrix::element(int i, int j) {
    int ind = (i - 1) * width + j - 1;

    if (i < 1 || j < 1 || ind >= height * width) {
        throw std::invalid_argument( "Accessing element out of bounds" );
    }

    return mat[ind];
}

void Matrix::insert(double e, int i, int j) {
    int ind = (i - 1) * width + j - 1;

    if (i < 1 || j < 1 || ind >= height * width) {
        throw std::invalid_argument( "Inserting element position out of bounds" );
    }

    mat[ind] = e;
}

void Matrix::print() {
    std::cout << toString() << std::endl;
}

Matrix Matrix::transpose() {
    Matrix retMat = Matrix(width, height);

    for(int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            retMat.insert(this->element(i, j), j, i);
        }
    }

    return retMat;
}

Matrix Matrix::augment(ColumnVector v) {
    if(v.height != height) {
        throw std::invalid_argument( "Can only augment matrix and vector of the same height" );
    }
    std::vector<double> newMat = {};
    std::vector<std::vector<double>> nest = generateNested();
    for(int i = 0; i < nest.size(); i++) {
        nest[i].push_back(v.vector[i]);
        newMat.insert(newMat.end(), nest[i].begin(), nest[i].end());
    }
    return {height, width + 1, newMat};
}

bool Matrix::isZero() {
    return all(mat, [](double x) {return x == 0;});
}

std::pair<int, double> Matrix::leadingEntry(int row) {
    std::vector<double> rw = generateNested()[row - 1];

    for (int i = 0; i < rw.size(); i++) {
        if (rw[i] != 0) return {i + 1, rw[i]};
    }
    return {0, 0};
}

Matrix Matrix::forwardPhase() {
    Matrix ret = Matrix(height, width, mat);

    // Base case
    if (isZero()) return ret;

    if (height == 1) {
        std::pair<int, double> p = leadingEntry(1);
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
    std::vector<std::vector<double>> nest = ret.generateNested();
    std::vector<std::vector<double>> backup = nest;
    nest.erase(nest.begin());
    for (auto & i : nest) {
        i.erase(i.begin(), i.begin() + pivot.second);
    }
    Matrix b = Matrix(height - 1, width - pivot.second, flatten(nest));
    Matrix forwardB = b.forwardPhase();

    std::vector<std::vector<double>> newNest = forwardB.generateNested();

    for (int i = 1; i < height; i++) {
        for (int j = 0; j < forwardB.width; j++) {
            backup[i].pop_back();
        }

        backup[i] = concat(backup[i], newNest[i - 1]);
    }

    return {height, width, flatten(backup)};
}

Matrix Matrix::backwardPhase() {
    // Requires Matrix to already be in echelon form via forward phase
    Matrix ret = Matrix(height, width, mat);

    for(int i = 1; i <= height; i++) {
        std::pair<int, double> p = ret.leadingEntry(i);
        if(p.first == 0) return ret;
        int column = p.first;

        for(int j = 1; j < i; j++) {
            double ele = ret.element(j, column);

            ret = ret.r(i, j, -ele);
        }
    }
    return ret;
}

Matrix Matrix::rowReduce() {
    Matrix ret = Matrix(height, width, mat);

    return ret.forwardPhase().backwardPhase();
}

bool Matrix::operator==(const Matrix &obj) {
    bool checker = true;
    if(height != obj.height || width != obj.width) {
        return false;
    }

    for (int i = 0; i < height * width; i++) {
        if (mat[i] != obj.mat[i]) return false;
    }
    return true;
}

bool Matrix::isDiagonal() {
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            if (i != j && element(i, j) != 0) return false;
        }
    }

    return true;
}

bool Matrix::invertible() {
    return determinant() != 0 && determinant() != NAN;
}

Matrix Matrix::inverse() {
    // First, compute the augmented matrix A | In
    if (!invertible()) {
        throw std::invalid_argument( "Matrix not invertible" );
    }

    Matrix aug = {height, width, mat};

    for (auto col : identity(height).columns()) {
        aug = aug.augment(ColumnVector(col));
    }
    // Step 2, row reduce the augmented matrix
    Matrix rowReduced = aug.rowReduce();

    // Step 3, obtain the final n columns as A-1
    Matrix inv = {height, 0, {}};

    for(int i = width; i < 2 * width; i++) {
        inv = inv.augment(ColumnVector(rowReduced.columns()[i]));
    }

    return inv;
}

// Shaowy05: Implemented isSquare function
bool Matrix::isSquare() {
    return height == width;
}

// Shaowy05: Implementing upper and lower triangular functions
bool Matrix::isUpperTriangular() {
    if (!isSquare()) return NAN;

    bool isUpperTriangular = true;

    for (int i = 2; i <= height; i++) {
        for (int j = 1; j <= i - 1; j++) {
            if (element(i, j) != 0) isUpperTriangular = false;
        }
    }

    return isUpperTriangular;
}

bool Matrix::isStrictlyUpperTriangular() {

    if (!isSquare()) return NAN;

    bool isUpperTriangular = true;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= i; j++) {
            if (element(i, j) != 0) isUpperTriangular = false;
        }
    }

    return isUpperTriangular;

}

// Using the transpose() method to define Lower Triangular methods
bool Matrix::isLowerTriangular() {
    Matrix t = this->transpose();
    return t.isUpperTriangular();
}

bool Matrix::isStrictlyLowerTriangular() {
    Matrix t = this->transpose();
    return t.isStrictlyUpperTriangular();
}

bool Matrix::isOrthogonal() {
    // return (*this) * transpose() == identity(width);

    std::set<ColumnVector> cs;
    for(auto col : columns()) {
        cs.insert(ColumnVector(col));
    }
    return orthogonal(cs);
}

bool Matrix::isOrthonormal() {
    std::set<ColumnVector> cs;
    for(auto col : columns()) {
        cs.insert(ColumnVector(col));
    }
    return orthonormal(cs);
}