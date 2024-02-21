//
// Created by Dylan Beharall on 25/01/2024.
//

#include "../include/utilities.h"
#include "../include/operations.h"

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

Matrix identityMatrix(int n){
    Matrix retMat = Matrix(n, n);

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

std::vector<double> flatten(std::vector<std::vector<double> > v) {
    std::vector<double> ret = {};

    for (auto vec : v) {
        ret.insert(ret.end(), vec.begin(), vec.end());
    }

    return ret;
}

bool all(std::vector<double> v, bool (*func) (double)) {
    if (v.size() == 0) return true;
    double last = v[v.size() - 1];
    v.pop_back();
    return func(last) && all(v, func);
}

std::vector<double> concat(std::vector<double> v1, std::vector<double> v2) {
    std::vector<double> r = {};
    for (auto v : v1) r.push_back(v);

    for (auto v : v2) r.push_back(v);

    return r;
}

double findAllCoefficients(int x, std::vector<std::pair<double, int> > pairs) {
    double sum = 0;

    for (auto pair : pairs) {
        if (pair.second == x) sum += pair.first;
    }

    return sum;
};