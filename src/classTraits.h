//
// Created by Dylan Beharall on 06/03/2024.
//
#include "../include/polynomial.h"
#include "../include/utilities.h"

#pragma once
#include <type_traits>

template <class T> T additiveIdentity() {
    if constexpr (std::is_same_v<T, Polynomial>) {
        return Polynomial({});
    }
    if constexpr (isArithmetic<T>()) {
        return 0.0;
    }

    throw std::invalid_argument("Additive identity cannot be found");
}
