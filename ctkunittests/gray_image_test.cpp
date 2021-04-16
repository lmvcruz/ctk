#include "gray_image_test.h"

#include <iostream>

#include "ctk/image/binary_image.h"
#include "ctk/image/gray_image.h"
#include "ctk/image/rgb_image.h"
#include "ctk/misc/vector_aux.h"

#include "test_setup.h"

void CtkGrayImageTest::SetUp() {
    grayname = INPUT_DIR+"gray_img.jpg";
    //
    grayimg.Open(grayname);
}

#ifdef TEST_GRAY_IMAGE 
TEST_F(CtkGrayImageTest, Test_Setup) {
    EXPECT_EQ(CtkGrayImageTest::grayimg.GetWidth(), 640);
    EXPECT_EQ(CtkGrayImageTest::grayimg.GetHeight(), 427);
    EXPECT_EQ(CtkGrayImageTest::grayimg.GetChannels(), 1);
    EXPECT_EQ(CtkGrayImageTest::grayimg.CheckChannel(), true);
}

TEST_F(CtkGrayImageTest, Test_ConstructorCopy) {
    ctk::GrayImage img(CtkGrayImageTest::grayimg);
    //
    EXPECT_EQ(img.GetWidth(), CtkGrayImageTest::grayimg.GetWidth());
    EXPECT_EQ(img.GetHeight(), CtkGrayImageTest::grayimg.GetHeight());
    EXPECT_EQ(img.GetChannels(), CtkGrayImageTest::grayimg.GetChannels());
    EXPECT_EQ(img.CheckChannel(), true);
}

TEST_F(CtkGrayImageTest, Test_ConstructorMat) {
    cv::Mat matimg = cv::imread(CtkGrayImageTest::grayname, cv::IMREAD_UNCHANGED);
    ctk::GrayImage img(matimg);
    //
    EXPECT_EQ(img.GetWidth(), CtkGrayImageTest::grayimg.GetWidth());
    EXPECT_EQ(img.GetHeight(), CtkGrayImageTest::grayimg.GetHeight());
    EXPECT_EQ(img.GetChannels(), CtkGrayImageTest::grayimg.GetChannels());
    EXPECT_EQ(img.CheckChannel(), true);
}

TEST_F(CtkGrayImageTest, Test_CopyImg) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg;
    //
    EXPECT_EQ(img.GetWidth(), CtkGrayImageTest::grayimg.GetWidth());
    EXPECT_EQ(img.GetHeight(), CtkGrayImageTest::grayimg.GetHeight());
    EXPECT_EQ(img.GetChannels(), CtkGrayImageTest::grayimg.GetChannels());
    EXPECT_EQ(img.CheckChannel(), true);
}

TEST_F(CtkGrayImageTest, Test_CopyMat) {
    cv::Mat matimg = cv::imread(CtkGrayImageTest::grayname,
                                cv::IMREAD_UNCHANGED);
    ctk::GrayImage img = matimg;
    //
    EXPECT_EQ(img.GetWidth(), CtkGrayImageTest::grayimg.GetWidth());
    EXPECT_EQ(img.GetHeight(), CtkGrayImageTest::grayimg.GetHeight());
    EXPECT_EQ(img.GetChannels(), CtkGrayImageTest::grayimg.GetChannels());
    EXPECT_EQ(img.CheckChannel(), true);
}

TEST_F(CtkGrayImageTest, Test_OpenRgb) {
    cv::Mat matimg = cv::imread(INPUT_DIR+"rgb_img.jpg",
                                cv::IMREAD_UNCHANGED);
    ctk::GrayImage img = matimg;
    //
    EXPECT_EQ(img.GetWidth(), CtkGrayImageTest::grayimg.GetWidth());
    EXPECT_EQ(img.GetHeight(), CtkGrayImageTest::grayimg.GetHeight());
    EXPECT_EQ(img.GetChannels(), CtkGrayImageTest::grayimg.GetChannels());
    EXPECT_EQ(img.CheckChannel(), true);
}

TEST_F(CtkGrayImageTest, Test_Crop) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg.Crop(100, 100, 300, 200);
    //
    EXPECT_EQ(img.GetWidth(), 300);
    EXPECT_EQ(img.GetHeight(), 200);
    EXPECT_EQ(img.GetChannels(), 1);
    EXPECT_EQ(img.CheckChannel(), true);
}

TEST_F(CtkGrayImageTest, Test_SelfCrop) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg;
    img.SelfCrop(100, 100, 300, 200);
    //
    EXPECT_EQ(img.GetWidth(), 300);
    EXPECT_EQ(img.GetHeight(), 200);
    EXPECT_EQ(img.GetChannels(), 1);
    EXPECT_EQ(img.CheckChannel(), true);
}

TEST_F(CtkGrayImageTest, Test_startScanIndices) {
    ctk::GrayImage img;
    img.Create(40, 40);
    img.StartScanIndices();
    for (int i=0; i<img.GetSize(); i++) {
        img.ISet(i, i%255);
    }
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"gray-scan.png");
    EXPECT_EQ(img.Get(10, 2), 90);
    EXPECT_EQ(img.Get(10, 5), 210);
    EXPECT_EQ(img.Get(10, 10), 155);
    EXPECT_EQ(img.Get(10, 20), 45);
    EXPECT_EQ(img.Get(10, 25), 245);
    EXPECT_EQ(img.Get(10, 35), 135);
}

TEST_F(CtkGrayImageTest, Test_startScanIndices_Not_Init) {
    ctk::GrayImage img;
    img.Create(40, 40);
    for (int i=0; i<img.GetSize(); i++) {
        img.SafeISet(i, i%255);
    }
    EXPECT_EQ(img.Get(10, 2), 90);
    EXPECT_EQ(img.Get(10, 5), 210);
    EXPECT_EQ(img.Get(10, 10), 155);
    EXPECT_EQ(img.Get(10, 20), 45);
    EXPECT_EQ(img.Get(10, 25), 245);
    EXPECT_EQ(img.Get(10, 35), 135);
}

TEST_F(CtkGrayImageTest, Test_Safe_Set) {
    ctk::GrayImage img;
    img.Create(40, 40);
    for (int i=0; i<img.GetSize()+2; i++) {
        try {
            img.SafeISet(i, i%255);
        } catch (std::exception& e){
            std::cout << e.what() << std::endl;
        }
    }
    EXPECT_EQ(img.Get(10, 2), 90);
    EXPECT_EQ(img.Get(10, 5), 210);
    EXPECT_EQ(img.Get(10, 10), 155);
    EXPECT_EQ(img.Get(10, 20), 45);
    EXPECT_EQ(img.Get(10, 25), 245);
    EXPECT_EQ(img.Get(10, 35), 135);
}

TEST_F(CtkGrayImageTest, Test_startSnakeIndices) {
    ctk::GrayImage img;
    img.Create(40, 40);
    img.StartSnakeIndices();
    for (int i=0; i<img.GetSize(); i++) {
        img.ISet(i, i%255);
    }
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"gray-snake.png");
    EXPECT_EQ(img.Get(10, 2), 90);
    EXPECT_EQ(img.Get(10, 5), 229);
    EXPECT_EQ(img.Get(10, 10), 155);
    EXPECT_EQ(img.Get(10, 20), 45);
    EXPECT_EQ(img.Get(10, 25), 9);
    EXPECT_EQ(img.Get(10, 35), 154);
}

TEST_F(CtkGrayImageTest, Test_startSpiralIndices) {
    ctk::GrayImage img;
    img.Create(40, 40);
    img.StartSpiralIndices();
    for (int i=0; i<img.GetSize(); i++) {
        img.ISet(i, i%255);
    }
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"gray-spiral.png");
    EXPECT_EQ(img.Get(10, 2), 102);
    EXPECT_EQ(img.Get(10, 5), 105);
    EXPECT_EQ(img.Get(10, 10), 110);
    EXPECT_EQ(img.Get(10, 20), 175);
    EXPECT_EQ(img.Get(10, 25), 125);
    EXPECT_EQ(img.Get(10, 35), 215);
}

TEST_F(CtkGrayImageTest, Test_startSnailIndices) {
    ctk::GrayImage img;
    img.Create(40, 40);
    img.StartSnailIndices();
    for (int i=0; i<img.GetSize(); i++) {
        img.ISet(i, i%255);
    }
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"gray-snail.png");
    EXPECT_EQ(img.Get(10, 2), 57);
    EXPECT_EQ(img.Get(10, 5), 195);
    EXPECT_EQ(img.Get(10, 10), 180);
    EXPECT_EQ(img.Get(10, 20), 246);
    EXPECT_EQ(img.Get(10, 25), 241);
    EXPECT_EQ(img.Get(10, 35), 153);
}

TEST_F(CtkGrayImageTest, Test_startCustomIndices) {
    ctk::GrayImage img;
    img.Create(40, 40);
    std::vector<unsigned int> vec = ctk::RangeVectorUi(0, (40*40)-1);
    ctk::Shuffle(vec, 0);
    img.StartCustomIndices(vec);
    for (int i=0; i<img.GetSize(); i++) {
        img.ISet(i, i%255);
    }
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"gray-custom.png");
    EXPECT_EQ(static_cast<unsigned int>(img.Get(10, 2)), 158);
    EXPECT_EQ(static_cast<unsigned int>(img.Get(10, 5)), 8);
    EXPECT_EQ(static_cast<unsigned int>(img.Get(10, 10)), 78);
    EXPECT_EQ(static_cast<unsigned int>(img.Get(10, 20)), 176);
    EXPECT_EQ(static_cast<unsigned int>(img.Get(10, 25)), 253);
    EXPECT_EQ(static_cast<unsigned int>(img.Get(10, 35)), 20);
}

TEST_F(CtkGrayImageTest, Test_FlipHorizontally) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg.FlipHorizontally();
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"gray-FlipHor.png");
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkGrayImageTest::grayimg.Get(w-x, y));
        }
    }
}

TEST_F(CtkGrayImageTest, Test_SelfFlipHorizontally) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg;
    img.SelfFlipHorizontally();
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkGrayImageTest::grayimg.Get(w-x, y));
        }
    }
}

TEST_F(CtkGrayImageTest, Test_FlipVertically) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg.FlipVertically();
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"gray-FlipVer.png");
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkGrayImageTest::grayimg.Get(x,h-y));
        }
    }
}

TEST_F(CtkGrayImageTest, Test_SelfFlipVertically) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg;
    img.SelfFlipVertically();
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkGrayImageTest::grayimg.Get(x,h-y));
        }
    }
}

TEST_F(CtkGrayImageTest, Test_FlipBoth) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg.FlipBoth();
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"gray-FlipBoth.png");
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkGrayImageTest::grayimg.Get(w-x,h-y));
        }
    }
}

TEST_F(CtkGrayImageTest, Test_SelfFlipBoth) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg;
    img.SelfFlipBoth();
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkGrayImageTest::grayimg.Get(w-x,h-y));
        }
    }
}

TEST_F(CtkGrayImageTest, Test_Rotate90) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg.Rotate90();
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"gray-Rot90.png");
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkGrayImageTest::grayimg.Get(y,w-x));
        }
    }
}

TEST_F(CtkGrayImageTest, Test_SelfRotate90) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg;
    img.SelfRotate90();
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkGrayImageTest::grayimg.Get(y,w-x));
        }
    }
}

TEST_F(CtkGrayImageTest, Test_Rotate180) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg.Rotate180();
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"gray-Rot180.png");
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkGrayImageTest::grayimg.Get(w-x,h-y));
        }
    }
}

TEST_F(CtkGrayImageTest, Test_SelfRotate180) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg;
    img.SelfRotate180();
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkGrayImageTest::grayimg.Get(w-x,h-y));
        }
    }
}

TEST_F(CtkGrayImageTest, Test_Rotate270) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg.Rotate270();
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"gray-Rot270.png");
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkGrayImageTest::grayimg.Get(h-y,x));
        }
    }
}

TEST_F(CtkGrayImageTest, Test_SelfRotate270) {
    ctk::GrayImage img = CtkGrayImageTest::grayimg;
    img.SelfRotate270();
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkGrayImageTest::grayimg.Get(h-y,x));
        }
    }
}

TEST_F(CtkGrayImageTest, Test_ApplyBinaryThreshold) {
    ctk::GrayImage img;
    img.Open(INPUT_DIR+"gray-grad.png");
    ctk::BinaryImage bin = img.ApplyBinaryThreshold();
    if (SAVE_IMAGES) bin.Save(OUTPUT_DIR+"gray-grad-bin.png");
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            if (x<256) {
                EXPECT_EQ(bin.Get(x,y), false);
            }
            else {
                EXPECT_EQ(bin.Get(x,y), true);
            }
        }
    }
}

TEST_F(CtkGrayImageTest, Test_ApplyOtsuThreshold) {
    ctk::GrayImage img;
    img.Open(INPUT_DIR+"gray-grad.png");
    ctk::BinaryImage bin = img.ApplyOtsuThreshold();
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            if (x<256) {
                EXPECT_EQ(bin.Get(x,y), false);
            }
            else {
                EXPECT_EQ(bin.Get(x,y), true);
            }
        }
    }
}

TEST_F(CtkGrayImageTest, Test_ApplyAdaptativeThreshold) {
    ctk::GrayImage img;
    img.Open(INPUT_DIR+"gray_img.jpg");
    ctk::BinaryImage bin = img.ApplyAdaptativeThreshold(11, 5);
    EXPECT_EQ(bin.GetWidth(), img.GetWidth());
    EXPECT_EQ(bin.GetHeight(), img.GetHeight());
    EXPECT_EQ(bin.GetChannels(), 1);
    EXPECT_EQ(img.CheckChannel(), true);
    //
    int total = bin.GetSize();
    int tpx = static_cast<int>(static_cast<float>(total)*0.8);
    int fpx = static_cast<int>(static_cast<float>(total)*0.3);
    EXPECT_EQ(total, img.GetSize());
    EXPECT_LE(bin.CountTrues(), tpx);
    EXPECT_LE(bin.CountFalses(), fpx);
    EXPECT_EQ(total, bin.CountTrues()+bin.CountFalses());
}

TEST_F(CtkGrayImageTest, Test_toRgbImage) {
    ctk::GrayImage gray = CtkGrayImageTest::grayimg;
    ctk::RgbImage rgb = gray.ToRgbImage();
    if (SAVE_IMAGES) rgb.Save(OUTPUT_DIR+"gray2rgb.jpg");
    EXPECT_EQ(rgb.GetWidth(), gray.GetWidth());
    EXPECT_EQ(rgb.GetHeight(), gray.GetHeight());
    EXPECT_EQ(rgb.GetChannels(), 3);
    EXPECT_EQ(gray.CheckChannel(), true);
    //
    for (int x=0; x<rgb.GetWidth(); x++) {
        for (int y=0; y<rgb.GetHeight(); y++) {
            rgb.Set(x, y, rgb.Red(x,y), 0, 0);
        }
    }
    for (int x=0; x<rgb.GetWidth(); x++) {
        for (int y=0; y<rgb.GetHeight(); y++) {
            EXPECT_EQ(rgb.Red(x,y), gray.Get(x,y));
            EXPECT_EQ(rgb.Green(x,y), 0);
            EXPECT_EQ(rgb.Blue(x,y), 0);
        }
    }
    if (SAVE_IMAGES) rgb.Save(OUTPUT_DIR+"gray2rgb2red.jpg");
    //
    ctk::RgbImage color;
    color.Create(100, 100);
    for (int x=0; x<100; x++) {
        for (int y=0; y<100; y++) {
            color.Set(x, y, x+y, 0, 0);
        }
    }
    for (int x=0; x<color.GetWidth(); x++) {
        for (int y=0; y<color.GetHeight(); y++) {
            EXPECT_EQ(color.Red(x,y), x+y);
            EXPECT_EQ(color.Green(x,y), 0);
            EXPECT_EQ(color.Blue(x,y), 0);
        }
    }
    if (SAVE_IMAGES) color.Save(OUTPUT_DIR+"gray-red.png");
}
#endif
