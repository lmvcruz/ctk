#pragma once

#include "gtest/gtest.h"

#include "ctk/image/image.h"

class CtkRgbImageTest : public ::testing::Test
{
public:
    void SetUp() override;

    std::string rgbname;

    ctk::RgbImage rgbimg;
};
