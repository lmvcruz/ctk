#pragma once

#include "gtest/gtest.h"

#include "ctk/image/binary_image.h"

class CtkBinaryImageTest : public ::testing::Test
{
public:
    void SetUp() override;

    ctk::BinaryImage binimg;
};
