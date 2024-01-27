//
// Created by Dylan Beharall on 25/01/2024.
//

#include "../include/columnVector.h"
#include "../include/operations.h"
#include <string>

ColumnVector::ColumnVector(int h, std::vector<double> v) {
    height = h;
    vector = std::move(v);

    if (vector.size() != h) {
        throw std::invalid_argument( "Vector provided does not match height" );
    }
}

ColumnVector::ColumnVector(int h) {
    height = h;
    vector = std::vector<double>(h);
}

ColumnVector::ColumnVector(std::vector<double> v) {
    height = v.size();
    vector = std::move(v);
}

Matrix ColumnVector::toMatrix() {
    return Matrix(height, 1, vector);
}

std::string ColumnVector::toString() {
    std::string ret = std::to_string(height) + "{ ";
    for(auto v : vector) {
        ret += std::to_string(v) + ", ";
    }
    return ret + '}';
}

ColumnVector ColumnVector::operator+(const ColumnVector &obj) {
    if (height != obj.height) {
        throw std::invalid_argument( "Vectors must have the same height to add them" );
    }

    std::vector<double> newVect = {};

    for (int i = 0; i < height; i++) newVect.push_back(vector[i] + obj.vector[i]);

    return {height, newVect};
}

ColumnVector ColumnVector::operator*(double lambda) {
    std::vector<double> newVect = vector;
    for (int i = 0; i < height; i++) newVect[i] *= lambda;
    return {height, newVect};
}

double ColumnVector::length() {
    return sqrt(dotP(*this, *this));
}

bool ColumnVector::isUnit() {
    return this->length() == 1;
}

ColumnVector ColumnVector::normalise() {
    double len = this->length();

    if (len == 1 || len == 0) return *this;

    return (1 / len) * *this;
}