#pragma once

#include "gtest/gtest.h"

#include "ctk/image/image.h"

class CtkGrayImageTest : public ::testing::Test
{
public:
    void SetUp() override;

    std::string grayname;

    ctk::GrayImage grayimg;
};
