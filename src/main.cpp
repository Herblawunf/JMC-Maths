#include "../include/include.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
   Polynomial p = {{{1, 3}, {-3, 2}, {3, 1}, {-5, 0}}};

   vector<std::complex<double>> solutions = p.solve(0);

   print(solutions);

   return 0;
}
