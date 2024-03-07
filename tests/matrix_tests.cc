#include "../include/include.h"
#include <gtest/gtest.h>

Matrix<double> intMatrix1 = {2, 2, {1, 2, 3, 4}};
Matrix<double> intMatrix2 = {2, 2, {2, 4, 6, 8}};

TEST(MatrixTests, MatrixAddition) {
  EXPECT_EQ((intMatrix1 + intMatrix1), intMatrix2);
}

TEST(MatrixTests, MatrixSubtraction) {
  EXPECT_EQ((intMatrix2 - intMatrix1), intMatrix1);
}

TEST(MatrixTests, MatrixMultiplication) {
  Matrix<double> result = {2, 2, {14, 20, 30, 44}};
  EXPECT_EQ((intMatrix1 * intMatrix2), result);
}

TEST(MatrixTests, MatrixTranspose) {
  Matrix<double> result = {2, 2, {1, 3, 2, 4}};
  EXPECT_EQ(intMatrix1.transpose(), result);
}

TEST(MatrixTests, MatrixDeterminant) {
  EXPECT_EQ(intMatrix1.determinant(), -2);
}

TEST(MatrixTests, NestedMatrixConstructor) {
  Matrix<double> expected = {{{1, 2}, {3, 4}}};

  EXPECT_EQ(intMatrix1, expected);
}

TEST(MatrixTests, MatrixScalarMultiplication) {
  Matrix<double> result = {2, 2, {2, 4, 6, 8}};
  EXPECT_EQ(intMatrix1 * 2.0, result);
  EXPECT_EQ(2.0 * intMatrix1, result);
}

TEST(MatrixTests, MatrixInverse) {
  Matrix<double> result = {2, 2, {-2, 1, 1.5, -0.5}};
  EXPECT_EQ(intMatrix1.inverse(), result);
}

TEST(MatrixTests, MatrixDivision) {
  Matrix<double> result = {2, 2, {0.5, 1, 1.5, 2}};
  EXPECT_EQ(intMatrix1 / 2.0, result);
}
