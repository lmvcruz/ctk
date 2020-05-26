#ifndef CTKGRAYIMAGETEST_H
#define CTKGRAYIMAGETEST_H

#include "gtest/gtest.h"

#include "ctkimage.h"

class CtkGrayImageTest : public ::testing::Test
{
public:
    void SetUp() override;

    std::string grayname;

    ctk::GrayImage grayimg;
};

#endif // CTKGRAYIMAGETEST_H
