//
// Created by Dylan Beharall on 27/01/2024.
//

#include "../include/vectorSets.h"
#include "../include/operations.h"
#include <iostream>

using namespace std;

template<class T>
bool orthogonal(std::set<ColumnVector<T> > vecs) {
    for (auto vec : vecs) {
        for (auto vec2 : vecs) {
            if (vec == vec2) continue;
            if (dotP(vec, vec2) != 0) {
                return false;
            }
        }
    }
    return true;
}

template<class T>
bool orthonormal(std::set<ColumnVector<T> > vecs) {
    if (!orthogonal(vecs)) return false;

    for (auto i : vecs) {
        if (!i.isUnit()) return false;
    }
    return true;
}