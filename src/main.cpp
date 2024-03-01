#include "../include/LinearSystem.h"
#include "../include/columnVector.h"
#include "../include/linearEquation.h"
#include "../include/matrix.h"
#include "../include/operations.h"
#include "../include/polynomial.h"
#include "../include/utilities.h"
#include "../include/vectorSets.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
   Polynomial p = {{{2, 1}}};
   std::vector<Polynomial> v = {p, p, (p + p), p};

   Matrix<Polynomial> m = {2, 2, v};

   vector<double> v1 = {1, 0 , -1, 0, 5, 0, 1, 0, 1};
   Matrix<double> m1 = {3, 3, v1};

   print(m1.eigenvalues());

  return 0;
}
