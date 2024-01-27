#include <iostream>
#include "../include/matrix.h"
#include "../include/columnVector.h"
#include "../include/utilities.h"
#include "../include/operations.h"
#include "../include/linearEquation.h"
#include "../include/LinearSystem.h"

using namespace std;

int main() {
    std::vector<double> k = {0, 1, 2, 1, 0, 3, 4, -3, 8};
    Matrix a = Matrix(3, 3, k);
    ColumnVector cv = ColumnVector({1, 2});

    a.inverse().print();
    // cout << a.generateNested()[1][0] << '\n';

    // a.rowReduce().print();

    LinearEquation eq = LinearEquation({1, 0, 1, 2}, 6);
    LinearEquation eq2 = LinearEquation({0, 1, -2}, -3);
    LinearEquation eq3 = LinearEquation({1, 2, -1}, -2);
    LinearEquation eq4 = LinearEquation({2, 1, 3, -2});
    LinearSystem sys = LinearSystem({eq, eq2, eq3, eq4});

    // sys.printSolutions();
    // LinearSystem({eq, eq2}).augmentedMatrix().print();

    return 0;
}
