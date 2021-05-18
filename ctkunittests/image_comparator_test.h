#pragma once

#include "gtest/gtest.h"

#include "ctk/image/binary_image.h"
#include "ctk/image/gray_image.h"
#include "ctk/image/rgb_image.h"

#include "test_setup.h"


class CtkImageComparatorTest : public ::testing::Test {
public:
    void SetUp() override;

    const std::string rgbname = INPUT_DIR + "rgb_img.jpg";
    const std::string grayname = INPUT_DIR + "gray_img.jpg";
    const std::string binname = INPUT_DIR + "bin_img.png";
    ctk::RgbImage rgbimg;
    ctk::GrayImage grayimg;
    ctk::BinaryImage binimg;

};