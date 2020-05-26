#ifndef CTKBINARYMATRIXTEST_H
#define CTKBINARYMATRIXTEST_H

#include "gtest/gtest.h"

#include "ctkbinarymatrix.h"

class CtkBinaryMatrixTest : public ::testing::Test
{
public:
    void SetUp() override;

    ctk::BinaryMatrix binimg;
};

#endif // CTKBINARYMATRIXTEST_H
