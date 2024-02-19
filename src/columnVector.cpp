//
// Created by Dylan Beharall on 25/01/2024.
//

#include "../include/columnVector.h"
#include <string>

template<class T>
ColumnVector<T>::ColumnVector(int h, std::vector<T> v) {
    height = h;
    vector = std::move(v);

    if (vector.size() != h) {
        throw std::invalid_argument( "Vector provided does not match height" );
    }
}

template<class T>
ColumnVector<T>::ColumnVector(int h) {
    height = h;
    vector = std::vector<T>(h);
}

template<class T>
ColumnVector<T>::ColumnVector(std::vector<T> v) {
    height = v.size();
    vector = std::move(v);
}

template<class T>
Matrix ColumnVector<T>::toMatrix() {
    return Matrix(height, 1, vector);
}

template<class T>
std::string ColumnVector<T>::toString() {
    std::string ret = std::to_string(height) + "{ ";
    for(auto v : vector) {
        ret += std::to_string(v) + ", ";
    }
    return ret + '}';
}

template<class T>
ColumnVector<T> ColumnVector<T>::operator+(const ColumnVector<T> &obj) {
    if (height != obj.height) {
        throw std::invalid_argument( "Vectors must have the same height to add" );
    }

    std::vector<T> newVect = {};

    for (int i = 0; i < height; i++) newVect.push_back(vector[i] + obj.vector[i]);

    return {height, newVect};
}

template<class T>
ColumnVector<T> ColumnVector<T>::operator*(T lambda) {
    std::vector<T> newVect = vector;
    for (int i = 0; i < height; i++) newVect[i] *= lambda;
    return {height, newVect};
}

template<class T>
bool ColumnVector<T>::operator==(const ColumnVector<T> &obj) {
    return vector == obj.vector;
}

template<class T>
double ColumnVector<T>::length() {
    if (!std::is_arithmetic_v<T>) {
        throw std::invalid_argument("Can only find length of vector of arithmetic type");
    }

    return sqrt(dotP(*this, *this));
}

template<class T>
bool ColumnVector<T>::isUnit() {
    return this->length() == 1;
}

template<class T>
ColumnVector<T> ColumnVector<T>::normalise() {
    double len = this->length();

    if (len == 1 || len == 0) return *this;

    return (1 / len) * *this;
}

template<class T>
bool ColumnVector<T>::operator<(ColumnVector<T> const &obj) const {
    return length() < obj.length();
}