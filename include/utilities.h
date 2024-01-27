//
// Created by Dylan Beharall on 25/01/2024.
//

#ifndef LA_UTILITIES_H
#define LA_UTILITIES_H
#include "columnVector.h"
#include "matrix.h"
#include <string>
#include <set>

ColumnVector e(int e, int r);

double distance(ColumnVector u, ColumnVector v);

Matrix identity(int n);

std::string joinWith(std::vector<double> v, std::string j);

std::string joinWith(std::vector<std::string> v, std::string j);

std::vector<double> flatten(std::vector<std::vector<double>> v);

bool all(std::vector<double> v, bool (*func) (double));

std::vector<double> concat(std::vector<double> v1, std::vector<double> v2);

#endif //LA_UTILITIES_H
