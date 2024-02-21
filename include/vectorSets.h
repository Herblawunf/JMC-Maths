//
// Created by Dylan Beharall on 27/01/2024.
//

#ifndef LA_VECTORSETS_H
#define LA_VECTORSETS_H
#include <set>
#include "columnVector.h"

//template<class T>
//bool orthogonal(std::set<ColumnVector<T> > vecs);
//
//template<class T>
//bool orthonormal(std::set<ColumnVector<T> > vecs);
//
//#include "../src/vectorSets.cpp"

template<class T>
bool orthogonal(std::set<ColumnVector<T> > vecs) {
    for (auto vec : vecs) {
        for (auto vec2 : vecs) {
            if (vec == vec2) continue;
            if (dotP<T>(vec, vec2) != 0) {
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

#endif //LA_VECTORSETS_H
