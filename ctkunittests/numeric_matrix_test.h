#pragma once

#include <vector>

#include "gtest/gtest.h"

#include "ctk/matrix/numeric_matrix.h"

class CtkNumericMatrixTest : public ::testing::Test {
public:
    void SetUp() override;

    int mat1a_w, mat1a_h;
    std::vector<double> data1a;
    ctk::NumericMatrix mat1a;

    int mat1b_w, mat1b_h;
    std::vector<double> data1b;
    ctk::NumericMatrix mat1b;

    std::vector<double> data1c;
    ctk::NumericMatrix mat1c;

    int mat2_w, mat2_h;
    std::vector<double> data2a;
    ctk::NumericMatrix mat2a;
    std::vector<double> data2b;
    ctk::NumericMatrix mat2b;

    int mat3_w, mat3_h;
    std::vector<double> data3;
    ctk::NumericMatrix mat3;
    std::vector<double> data3i;
    ctk::NumericMatrix mat3i;

    int mat4_w, mat4_h;
    std::vector<double> data4;
    ctk::NumericMatrix mat4;

    ctk::NumericMatrix mat_4_div_3;
};
