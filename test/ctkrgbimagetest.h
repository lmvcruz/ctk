#ifndef CTKRGBIMAGETEST_H
#define CTKRGBIMAGETEST_H

#include "gtest/gtest.h"

#include "ctkimage.h"

class CtkRgbImageTest : public ::testing::Test
{
public:
    void SetUp() override;

    std::string rgbname;

    ctk::RgbImage rgbimg;
};

#endif // CTKRGBIMAGETEST_H
