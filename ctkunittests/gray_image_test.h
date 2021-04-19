#pragma once

#include "gtest/gtest.h"

#include "ctk/image/gray_image.h"

#include "test_setup.h"

class CtkGrayImageTest : public ::testing::Test
{
public:
    void SetUp() override;

    const std::string grayname = INPUT_DIR + "gray_img.jpg";
    ctk::GrayImage grayimg;
};
