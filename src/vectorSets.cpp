//
// Created by Dylan Beharall on 27/01/2024.
//

#include "../include/vectorSets.h"
#include "../include/operations.h"

bool orthogonal(std::set<ColumnVector> vecs) {
    for (auto vec : vecs) {
        for (auto vec2 : vecs) {
            if (vec == vec2) continue;
            if (dotP(vec, vec2) != 0) return false;
        }
    }
    return true;
}