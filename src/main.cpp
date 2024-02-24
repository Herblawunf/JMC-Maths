#include <iostream>
#include "../include/matrix.h"
#include "../include/columnVector.h"
#include "../include/utilities.h"
#include "../include/operations.h"
#include "../include/linearEquation.h"
#include "../include/LinearSystem.h"
#include "../include/vectorSets.h"
#include "../include/polynomial.h"
#include <string>

using namespace std;

int main() {
    Polynomial p = {{{2, 1}}};
    std::vector<Polynomial> v = {p, p, (p + p), p};

    Matrix<Polynomial> m = {2, 2, v};

    vector<double> v1 = {2.0, 3.0, 1.5, 4};
    Matrix<double> m1 = {2, 2, v1};

    print(m1.eigenvalues());

    return 0;
}
