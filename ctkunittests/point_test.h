#pragma once

#include "gtest/gtest.h"

#include <vector>

#include "ctk/geometry/point.h"

class CtkPointTest : public ::testing::Test {
public:
    const ctk::PointI Pi = {1, 2, 3};
    const ctk::PointI Pi_1 = {2, 2};
    const ctk::PointI Pi_2 = {4, 5, 3};
    const ctk::Point<unsigned int> Pui = {1, 2, 3};
    const ctk::Point<long> Pl = {1, 2, 3};
    const ctk::Point<unsigned long> Pul = {1, 2, 3};
    const ctk::Point<long long> Pll = {1, 2, 3};
    const ctk::Point<unsigned long long> Pull = {1, 2, 3};
    const ctk::PointD Pd = {1.1, 2.1, 3.1};
    const ctk::PointD Pd_1 = {1, 1, 1};
    const ctk::PointD Pd_2 = {1.1, 5.5, 6.6};
};
