//
// Created by Dylan Beharall on 27/01/2024.
//

#include "../include/vectorSets.h"
#include "../include/operations.h"
#include <iostream>

using namespace std;

bool orthogonal(std::set<ColumnVector> vecs) {
    for (auto vec : vecs) {
        for (auto vec2 : vecs) {
            if (vec == vec2) continue;
            if (dotP(vec, vec2) != 0) {
                cout << vec.toString() << vec2.toString() << endl;
                cout << dotP(vec, vec2) <<endl;
                return false;
            }
        }
    }
    return true;
}

bool orthonormal(std::set<ColumnVector> vecs) {
    if (!orthogonal(vecs)) return false;

    for (auto i : vecs) {
        if (!i.isUnit()) return false;
    }
    return true;
}