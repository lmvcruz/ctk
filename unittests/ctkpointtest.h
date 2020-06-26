#ifndef CTKPOINTTEST_H
#define CTKPOINTTEST_H

#include "gtest/gtest.h"
#include "ctkpoint.h"
#include <vector>
class CtkPointTest : public ::testing::Test
{
public:

    void SetUp() override;
    ctk::PointI Pi;
    ctk::PointI Pi_1;
    ctk::PointI Pi_2;
    ctk::PointI Pi_3;
    ctk::PointD Pd;
    ctk::PointD Pd_1;
    ctk::PointD Pd_2;
    ctk::Point<unsigned int> Pui;
    ctk::Point<long> Pl;
    ctk::Point<unsigned long> Pul;
    ctk::Point<long long> Pll;
    ctk::Point<unsigned long long> Pull;


};

#endif // CTKPOINTTEST_H
