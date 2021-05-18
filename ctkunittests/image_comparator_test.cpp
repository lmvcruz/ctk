#include "image_comparator_test.h"

#include "ctk/image/image_comparator.h"

ctk::RgbImage ReadRgbImage(std::string filename) {
    ctk::RgbImage img;
    img.Open(INPUT_DIR + filename);
    return img;
}

ctk::GrayImage ReadGrayImage(std::string filename) {
    ctk::GrayImage img;
    img.Open(INPUT_DIR + filename);
    return img;
}

ctk::BinaryImage ReadBinaryImage(std::string filename) {
    ctk::BinaryImage img;
    img.Open(INPUT_DIR + filename);
    return img;
}

void CtkImageComparatorTest::SetUp() {
    rgbimg.Open(INPUT_DIR + "rgb_img.jpg");
    grayimg.Open(INPUT_DIR + "gray_img.jpg");
    binimg.Open(INPUT_DIR + "bin_img.png");
}

TEST_F(CtkImageComparatorTest, Test_CompareAbsoluteImages) {
    ctk::RgbImage rgb1 = ReadRgbImage("rgb_img.jpg");
    ctk::RgbImage rgb2 = ReadRgbImage("dog.png");
    EXPECT_TRUE(ctk::CompareAbsoluteImages(rgb1, rgbimg));
    EXPECT_FALSE(ctk::CompareAbsoluteImages(rgb2, rgbimg));
    EXPECT_TRUE(ctk::IsEquals(rgb1, rgbimg));
    EXPECT_FALSE(ctk::IsEquals(rgb2, rgbimg));
    //
    ctk::GrayImage gray1 = ReadGrayImage("gray_img.jpg");
    ctk::GrayImage gray2 = ReadGrayImage("dog_gray.png");
    EXPECT_TRUE(ctk::CompareAbsoluteImages(gray1, grayimg));
    EXPECT_FALSE(ctk::CompareAbsoluteImages(gray2, grayimg));
    EXPECT_TRUE(ctk::IsEquals(gray1, grayimg));
    EXPECT_FALSE(ctk::IsEquals(gray2, grayimg));
    //
    ctk::BinaryImage bin1 = ReadBinaryImage("bin_img.png");
    ctk::BinaryImage bin2 = ReadBinaryImage("dog_bin.png");
    EXPECT_TRUE(ctk::CompareAbsoluteImages(bin1, binimg));
    EXPECT_FALSE(ctk::CompareAbsoluteImages(bin2, binimg));
    EXPECT_TRUE(ctk::IsEquals(bin1, binimg));
    EXPECT_FALSE(ctk::IsEquals(bin2, binimg));
}

TEST_F(CtkImageComparatorTest, Test_CountDifferentPixels) {
    ctk::RgbImage rgb1 = ReadRgbImage("rgb_img.jpg");
    ctk::RgbImage rgb2 = ReadRgbImage("dog.png");
    EXPECT_EQ(ctk::CountDifferentPixels(rgb1, rgbimg), 0);
    EXPECT_EQ(ctk::CountDifferentPixels(rgb2, rgbimg), 360000);
    //
    ctk::GrayImage gray1 = ReadGrayImage("gray_img.jpg");
    ctk::GrayImage gray2 = ReadGrayImage("dog_gray.png");
    EXPECT_EQ(ctk::CountDifferentPixels(gray1, grayimg), 0);
    EXPECT_EQ(ctk::CountDifferentPixels(gray2, grayimg), 272527);
    //
    ctk::BinaryImage bin1 = ReadBinaryImage("bin_img.png");
    ctk::BinaryImage bin2 = ReadBinaryImage("dog_bin.png");
    EXPECT_EQ(ctk::CountDifferentPixels(bin1, binimg), 0);
    EXPECT_EQ(ctk::CountDifferentPixels(bin2, binimg), 210778);
}

TEST_F(CtkImageComparatorTest, Test_CompareRelativeImages) {
    ctk::RgbImage rgb1 = ReadRgbImage("rgb_img.jpg");
    ctk::RgbImage rgb2 = ReadRgbImage("dog.png");
    EXPECT_GT(ctk::CompareRelativeImages(rgb1, rgbimg), 0.99);
    EXPECT_LT(ctk::CompareRelativeImages(rgb2, rgbimg), 0.01);
    //
    ctk::GrayImage gray1 = ReadGrayImage("gray_img.jpg");
    ctk::GrayImage gray2 = ReadGrayImage("dog_gray.png");
    EXPECT_GT(ctk::CompareRelativeImages(gray1, grayimg), 0.99);
    EXPECT_LT(ctk::CompareRelativeImages(gray2, grayimg), 0.01);
    //
    ctk::BinaryImage bin1 = ReadBinaryImage("bin_img.png");
    ctk::BinaryImage bin2 = ReadBinaryImage("dog_bin.png");
    EXPECT_GT(ctk::CompareRelativeImages(bin1, binimg), 0.99);
    EXPECT_GT(ctk::CompareRelativeImages(bin2, binimg), 0.2);
    EXPECT_LT(ctk::CompareRelativeImages(bin2, binimg), 0.5);
}

TEST_F(CtkImageComparatorTest, Test_PixelDistance) {
    ctk::RgbImage rgb1 = ReadRgbImage("red_square.png");
    EXPECT_EQ(ctk::PixelL1Distance(rgb1.Get(0, 0), rgb1.Get(0, 0)), 0);
    EXPECT_EQ(ctk::PixelL1Distance(rgb1.Get(0, 0), rgb1.Get(100, 100)), 255*2);
    EXPECT_EQ(ctk::PixelL1Distance(rgb1.Get(0, 0), rgb1.Get(0, 0)), 0);
    //
    ctk::GrayImage gray1 = ReadGrayImage("mask.png");
    EXPECT_EQ(ctk::PixelL1Distance(gray1.Get(0, 0), gray1.Get(0, 0)), 0);
    EXPECT_EQ(ctk::PixelL1Distance(gray1.Get(0, 0), gray1.Get(100, 100)), 255);
    EXPECT_EQ(ctk::PixelL1Distance(gray1.Get(0, 0), gray1.Get(0, 0)), 0);
    //
    ctk::BinaryImage bin1 = ReadBinaryImage("mask.png");
    EXPECT_EQ(ctk::PixelL1Distance(bin1.Get(0, 0), bin1.Get(0, 0)), 0);
    EXPECT_EQ(ctk::PixelL1Distance(bin1.Get(0, 0), bin1.Get(100, 100)), 1);
    EXPECT_EQ(ctk::PixelL1Distance(bin1.Get(0, 0), bin1.Get(0, 0)), 0);
}

TEST_F(CtkImageComparatorTest, Test_ComparePixelDistance) {
    ctk::RgbImage rgb1 = ReadRgbImage("red_square.png");
    ctk::RgbImage rgb2 = ReadRgbImage("red_black_square.png");
    ctk::RgbImage rgb3 = ReadRgbImage("cyan_square.png");
    //
    EXPECT_EQ(ctk::ComparePixelAbsoluteDistance(rgb1, rgb1), 0);
    EXPECT_EQ(ctk::ComparePixelAbsoluteDistance(rgb1, rgb2), 50*50*255*3);
    EXPECT_EQ(ctk::ComparePixelAbsoluteDistance(rgb1, rgb3), 200*200*255*3);
    //
    EXPECT_FLOAT_EQ(ctk::ComparePixelRelativeDistance(rgb1, rgb1), 0.0);
    EXPECT_FLOAT_EQ(ctk::ComparePixelRelativeDistance(rgb1, rgb2), 0.0625);
    EXPECT_FLOAT_EQ(ctk::ComparePixelRelativeDistance(rgb1, rgb3), 1.0);
    //
    ctk::GrayImage gray1 = ReadGrayImage("mask.png");
    ctk::GrayImage gray2 = ReadGrayImage("maskM1AndM2.png");
    ctk::GrayImage gray3 = ReadGrayImage("maskinv.png");
    //
    EXPECT_EQ(ctk::ComparePixelAbsoluteDistance(gray1, gray1), 0);
    EXPECT_EQ(ctk::ComparePixelAbsoluteDistance(gray1, gray2), 50*50*255);
    EXPECT_EQ(ctk::ComparePixelAbsoluteDistance(gray1, gray3), 200*200*255);
    //
    EXPECT_FLOAT_EQ(ctk::ComparePixelRelativeDistance(gray1, gray1), 0.0);
    EXPECT_FLOAT_EQ(ctk::ComparePixelRelativeDistance(gray1, gray2), 0.0625);
    EXPECT_FLOAT_EQ(ctk::ComparePixelRelativeDistance(gray1, gray3), 1.0);
    //
    ctk::BinaryImage bin1 = ReadBinaryImage("mask.png");
    ctk::BinaryImage bin2 = ReadBinaryImage("maskM1AndM2.png");
    ctk::BinaryImage bin3 = ReadBinaryImage("maskinv.png");
    //
    EXPECT_EQ(ctk::ComparePixelAbsoluteDistance(bin1, bin1), 0);
    EXPECT_EQ(ctk::ComparePixelAbsoluteDistance(bin1, bin2), 50*50);
    EXPECT_EQ(ctk::ComparePixelAbsoluteDistance(bin1, bin3), 200*200);
    //
    EXPECT_FLOAT_EQ(ctk::ComparePixelRelativeDistance(bin1, bin1), 0.0);
    EXPECT_FLOAT_EQ(ctk::ComparePixelRelativeDistance(bin1, bin2), 0.0625);
    EXPECT_FLOAT_EQ(ctk::ComparePixelRelativeDistance(bin1, bin3), 1.0);
}