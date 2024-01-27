//
// Created by Dylan Beharall on 26/01/2024.
//

#ifndef LA_LINEARSYSTEM_H
#define LA_LINEARSYSTEM_H
#include "linearEquation.h"
#include "matrix.h"
#include "columnVector.h"
#include "utilities.h"

class LinearSystem {
public:
    std::vector<LinearEquation> equations;

    LinearSystem(std::vector<LinearEquation> es);

    Matrix coefficientMatrix();

    ColumnVector results();

    Matrix augmentedMatrix();

    std::vector<double> solutions();

    void printSolutions();
};


#endif //LA_LINEARSYSTEM_H
