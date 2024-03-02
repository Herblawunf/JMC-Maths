#include <gtest/gtest.h>
#include "../include/include.h"

Matrix<double> intMatrix1 = {2, 2, {1, 2, 3, 4}};
Matrix<double> intMatrix2 = {2, 2, {2, 4, 6, 8}};

TEST(MatrixTests, MatrixAddition) {
    EXPECT_EQ((intMatrix1 + intMatrix1), intMatrix2);
}