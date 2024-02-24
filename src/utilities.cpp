//
// Created by Dylan Beharall on 25/01/2024.
//

#include "../include/utilities.h"
#include "../include/matrix.h"

ColumnVector<double> e(int e, int r) {
    if (e < 1 || e > r) {
        throw std::invalid_argument( "Standard basis out of bounds" );
    }

    std::vector<double> v = std::vector<double>(r);
    v[e - 1] = 1;

    return {r, v};
}

double distance(ColumnVector<double> u, ColumnVector<double> v) {
    return (u + (-1.0) * v).length();
}

Matrix<double> identityMatrix(int n){
    Matrix<double> retMat = Matrix<double>(n, n, std::vector<double>(n * n));

    for (int i = 1; i <= n; i++) {
        retMat.insert(1, i, i);
    }

    return retMat;
}

std::string joinWith(std::vector<double> v, std::string j) {
    std::string ret = "";

    for (int i = 1; i < v.size(); i++) {
        ret += std::to_string(v[i - 1]) + j;
    }
    ret += std::to_string(v[v.size() - 1]);

    return ret;
}

std::string joinWith(std::vector<std::string> v, std::string j) {
    std::string ret = "";

    for (int i = 1; i < v.size(); i++) {
        ret += v[i - 1] + j;
    }
    ret += v[v.size() - 1];

    return ret;
}

double findAllCoefficients(int x, std::vector<std::pair<double, int> > pairs) {
    double sum = 0;

    for (auto pair : pairs) {
        if (pair.second == x) sum += pair.first;
    }

    return sum;
};

