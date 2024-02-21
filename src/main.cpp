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
    ColumnVector<int> v = {{1, 1}};
    ColumnVector<string> v1 = {{"Hello", "there"}};

    Polynomial p = {{{0.1, 3}, {2, 2}}};

    ColumnVector<Polynomial> vp = {{p, p}};

    (p * p).print();

    return 0;
}
