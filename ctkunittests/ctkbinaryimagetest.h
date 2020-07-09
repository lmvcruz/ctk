#ifndef CTKBINARYMATRIXTEST_H
#define CTKBINARYMATRIXTEST_H

#include "gtest/gtest.h"

#include "ctkimage.h"

class CtkBinaryImageTest : public ::testing::Test
{
public:
    void SetUp() override;

    ctk::BinaryImage binimg;
};

#endif // CTKBINARYMATRIXTEST_H
