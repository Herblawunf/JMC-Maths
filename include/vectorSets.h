//
// Created by Dylan Beharall on 27/01/2024.
//

#ifndef LA_VECTORSETS_H
#define LA_VECTORSETS_H
#include <set>
#include "columnVector.h"

template<class T>
bool orthogonal(std::set<ColumnVector<T> > vecs);

template<class T>
bool orthonormal(std::set<ColumnVector<T> > vecs);

#endif //LA_VECTORSETS_H
