#include <iostream>
#include "../include/matrix.h"
#include "../include/columnVector.h"
#include "../include/utilities.h"
#include "../include/operations.h"
#include "../include/linearEquation.h"
#include "../include/LinearSystem.h"
#include "../include/vectorSets.h"
#include <set>

using namespace std;

int main() {
    double x = 2.0/3.0, y = -1.0/3.0;
    std::vector<double> k = {1, x, 0, 1, y, 0.5, 1, y, -0.5};
    Matrix a = Matrix(3, 3, k);
    set<ColumnVector> vs;

    a.print();

    (a * a.transpose()).print();

    cout << a.isOrthogonal() << endl;

    LinearEquation eq = LinearEquation({1, 0, 1, 2}, 6);
    LinearEquation eq2 = LinearEquation({0, 1, -2}, -3);
    LinearEquation eq3 = LinearEquation({1, 2, -1}, -2);
    LinearEquation eq4 = LinearEquation({2, 1, 3, -2});
    LinearSystem sys = LinearSystem({eq, eq2, eq3, eq4});

    // sys.printSolutions();
    // LinearSystem({eq, eq2}).augmentedMatrix().print();

    return 0;
}
