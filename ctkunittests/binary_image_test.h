#pragma once

#include "ctk/image/binary_image.h"
#include "gtest/gtest.h"

class CtkBinaryImageTest : public ::testing::Test {
public:
    void SetUp() override;

    ctk::BinaryImage binimg;
};
