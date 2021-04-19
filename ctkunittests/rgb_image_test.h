#pragma once

#include "gtest/gtest.h"

#include "ctk/image/rgb_image.h"

#include "test_setup.h"

class CtkRgbImageTest : public ::testing::Test
{
public:
    void SetUp() override;

    const std::string rgbname = INPUT_DIR + "rgb_img.jpg";
    ctk::RgbImage rgbimg;
};
