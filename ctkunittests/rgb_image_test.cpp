#include "rgb_image_test.h"

#include <iostream>

#include "ctk/image/gray_image.h"
#include "ctk/misc/vector_aux.h"

#include "test_setup.h"

void CtkRgbImageTest::SetUp()
{
    rgbname = INPUT_DIR+"rgb_img.jpg";
    rgbimg.Open(rgbname);
}

#ifdef TEST_RGB_IMAGES
TEST_F(CtkRgbImageTest, Test_Setup) {
    EXPECT_EQ(CtkRgbImageTest::rgbimg.GetWidth(), 640);
    EXPECT_EQ(CtkRgbImageTest::rgbimg.GetHeight(), 427);
    EXPECT_EQ(CtkRgbImageTest::rgbimg.GetChannels(), 3);
    EXPECT_EQ(CtkRgbImageTest::rgbimg.CheckChannel(), true);
}

TEST_F(CtkRgbImageTest, Test_ConstructorCopy) {
    ctk::RgbImage img(CtkRgbImageTest::rgbimg);
    //
    EXPECT_EQ(img.GetWidth(), CtkRgbImageTest::rgbimg.GetWidth());
    EXPECT_EQ(img.GetHeight(), CtkRgbImageTest::rgbimg.GetHeight());
    EXPECT_EQ(img.GetChannels(), CtkRgbImageTest::rgbimg.GetChannels());
    EXPECT_EQ(img.CheckChannel(), true);
}

TEST_F(CtkRgbImageTest, Test_ConstructorMat) {
    cv::Mat matimg = cv::imread(CtkRgbImageTest::rgbname, cv::IMREAD_UNCHANGED);
    ctk::RgbImage img(matimg);
    //
    EXPECT_EQ(img.GetWidth(), CtkRgbImageTest::rgbimg.GetWidth());
    EXPECT_EQ(img.GetHeight(), CtkRgbImageTest::rgbimg.GetHeight());
    EXPECT_EQ(img.GetChannels(), CtkRgbImageTest::rgbimg.GetChannels());
    EXPECT_EQ(img.CheckChannel(), true);
}


TEST_F(CtkRgbImageTest, Test_CopyImg) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg;
    //
    EXPECT_EQ(img.GetWidth(), CtkRgbImageTest::rgbimg.GetWidth());
    EXPECT_EQ(img.GetHeight(), CtkRgbImageTest::rgbimg.GetHeight());
    EXPECT_EQ(img.GetChannels(), CtkRgbImageTest::rgbimg.GetChannels());
    EXPECT_EQ(img.CheckChannel(), true);
}

TEST_F(CtkRgbImageTest, Test_CopyMat) {
    cv::Mat matimg = cv::imread(CtkRgbImageTest::rgbname,
                                cv::IMREAD_UNCHANGED);
    ctk::RgbImage img = matimg;
    //
    EXPECT_EQ(img.GetWidth(), CtkRgbImageTest::rgbimg.GetWidth());
    EXPECT_EQ(img.GetHeight(), CtkRgbImageTest::rgbimg.GetHeight());
    EXPECT_EQ(img.GetChannels(), CtkRgbImageTest::rgbimg.GetChannels());
    EXPECT_EQ(img.CheckChannel(), true);
}

TEST_F(CtkRgbImageTest, Test_Crop) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg.Crop(100, 100, 300, 200);
    //
    EXPECT_EQ(img.GetWidth(), 300);
    EXPECT_EQ(img.GetHeight(), 200);
    EXPECT_EQ(img.GetChannels(), 3);
    EXPECT_EQ(img.CheckChannel(), true);
}

TEST_F(CtkRgbImageTest, Test_SelfCrop) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg;
    img.SelfCrop(100, 100, 300, 200);
    //
    EXPECT_EQ(img.GetWidth(), 300);
    EXPECT_EQ(img.GetHeight(), 200);
    EXPECT_EQ(img.GetChannels(), 3);
    EXPECT_EQ(img.CheckChannel(), true);
}

TEST_F(CtkRgbImageTest, Test_FlipHorizontally) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg.FlipHorizontally();
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"FlipHor.png");
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkRgbImageTest::rgbimg.Get(w-x, y));
        }
    }
}

TEST_F(CtkRgbImageTest, Test_SelfFlipHorizontally) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg;
    img.SelfFlipHorizontally();
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkRgbImageTest::rgbimg.Get(w-x, y));
        }
    }
}

TEST_F(CtkRgbImageTest, Test_FlipVertically) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg.FlipVertically();
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"FlipVer.png");
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkRgbImageTest::rgbimg.Get(x,h-y));
        }
    }
}

TEST_F(CtkRgbImageTest, Test_SelfFlipVertically) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg;
    img.SelfFlipVertically();
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkRgbImageTest::rgbimg.Get(x,h-y));
        }
    }
}

TEST_F(CtkRgbImageTest, Test_FlipBoth) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg.FlipBoth();
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"FlipBoth.png");
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkRgbImageTest::rgbimg.Get(w-x,h-y));
        }
    }
}

TEST_F(CtkRgbImageTest, Test_SelfFlipBoth) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg;
    img.SelfFlipBoth();
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkRgbImageTest::rgbimg.Get(w-x,h-y));
        }
    }
}

TEST_F(CtkRgbImageTest, Test_Rotate90) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg.Rotate90();
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"Rot90.png");
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkRgbImageTest::rgbimg.Get(y,w-x));
        }
    }
}

TEST_F(CtkRgbImageTest, Test_SelfRotate90) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg;
    img.SelfRotate90();
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkRgbImageTest::rgbimg.Get(y,w-x));
        }
    }
}

TEST_F(CtkRgbImageTest, Test_Rotate180) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg.Rotate180();
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"Rot180.png");
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkRgbImageTest::rgbimg.Get(w-x,h-y));
        }
    }
}

TEST_F(CtkRgbImageTest, Test_SelfRotate180) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg;
    img.SelfRotate180();
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkRgbImageTest::rgbimg.Get(w-x,h-y));
        }
    }
}

TEST_F(CtkRgbImageTest, Test_Rotate270) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg.Rotate270();
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"rgb-Rot270.png");
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkRgbImageTest::rgbimg.Get(h-y,x));
        }
    }
}

TEST_F(CtkRgbImageTest, Test_SelfRotate270) {
    ctk::RgbImage img = CtkRgbImageTest::rgbimg;
    img.SelfRotate270();
    //
    int w = img.GetWidth()-1;
    int h = img.GetHeight()-1;
    for (int x=0; x<=w; x++) {
        for (int y=0; y<=h; y++) {
            EXPECT_EQ(img.Get(x,y), CtkRgbImageTest::rgbimg.Get(h-y,x));
        }
    }
}

TEST_F(CtkRgbImageTest, Test_startScanIndices) {
    ctk::RgbImage img;
    img.Create(40, 40);
    img.StartScanIndices();
    for (int i=0; i<img.GetSize(); i++) {
        img.Set(i, i%255, 0, 0);
    }
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"rgb-red-scan.png");
    EXPECT_EQ(img.red(10, 2), 90);
    EXPECT_EQ(img.green(10, 2), 0);
    EXPECT_EQ(img.blue(10, 2), 0);
    EXPECT_EQ(img.red(10, 5), 210);
    EXPECT_EQ(img.green(10, 5), 0);
    EXPECT_EQ(img.blue(10, 5), 0);
    EXPECT_EQ(img.red(10, 10), 155);
    EXPECT_EQ(img.red(10, 20), 45);
    EXPECT_EQ(img.red(10, 25), 245);
    EXPECT_EQ(img.red(10, 35), 135);
}

TEST_F(CtkRgbImageTest, Test_startScanIndices_Not_Init) {
    ctk::RgbImage img;
    img.Create(40, 40);
    for (int i=0; i<img.GetSize(); i++) {
        img.safe_iset(i, i%255,0,0);
    }
    EXPECT_EQ(img.red(10, 2), 90);
    EXPECT_EQ(img.green(10, 2), 0);
    EXPECT_EQ(img.blue(10, 2), 0);
    EXPECT_EQ(img.red(10, 5), 210);
    EXPECT_EQ(img.green(10, 5), 0);
    EXPECT_EQ(img.blue(10, 5), 0);
    EXPECT_EQ(img.red(10, 10), 155);
    EXPECT_EQ(img.red(10, 20), 45);
    EXPECT_EQ(img.red(10, 25), 245);
    EXPECT_EQ(img.red(10, 35), 135);
}

TEST_F(CtkRgbImageTest, Test_Safe_Set) {
    ctk::RgbImage img;
    img.Create(40, 40);
    for (int i=0; i<img.GetSize()+2; i++) {
        try {
            img.safe_iset(i, i%255,0,0);
        } catch (std::exception& e){
            std::cout << e.what() << std::endl;
        }
    }
    EXPECT_EQ(img.red(10, 2), 90);
    EXPECT_EQ(img.green(10, 2), 0);
    EXPECT_EQ(img.blue(10, 2), 0);
    EXPECT_EQ(img.red(10, 5), 210);
    EXPECT_EQ(img.green(10, 5), 0);
    EXPECT_EQ(img.blue(10, 5), 0);
    EXPECT_EQ(img.red(10, 10), 155);
    EXPECT_EQ(img.red(10, 20), 45);
    EXPECT_EQ(img.red(10, 25), 245);
    EXPECT_EQ(img.red(10, 35), 135);
}

TEST_F(CtkRgbImageTest, Test_startSnakeIndices) {
    ctk::RgbImage img;
    img.Create(40, 40);
    img.StartSnakeIndices();
    for (int i=0; i<img.GetSize(); i++) {
        img.Set(i, i%255, 0, 0);
    }
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"rgb-red-snake.png");
    EXPECT_EQ(img.red(10, 2), 90);
    EXPECT_EQ(img.green(10, 2), 0);
    EXPECT_EQ(img.blue(10, 2), 0);
    EXPECT_EQ(img.red(10, 5), 229);
    EXPECT_EQ(img.red(10, 10), 155);
    EXPECT_EQ(img.red(10, 20), 45);
    EXPECT_EQ(img.red(10, 25), 9);
    EXPECT_EQ(img.red(10, 35), 154);
}

TEST_F(CtkRgbImageTest, Test_startSpiralIndices) {
    ctk::RgbImage img;
    img.Create(40, 40);
    img.StartSpiralIndices();
    for (int i=0; i<img.GetSize(); i++) {
        img.Set(i, i%255, 0, 0);
    }
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"rgb-red-spiral.png");
    EXPECT_EQ(img.red(10, 2), 102);
    EXPECT_EQ(img.green(10, 2), 0);
    EXPECT_EQ(img.blue(10, 2), 0);
    EXPECT_EQ(img.red(10, 5), 105);
    EXPECT_EQ(img.red(10, 10), 110);
    EXPECT_EQ(img.red(10, 20), 175);
    EXPECT_EQ(img.red(10, 25), 125);
    EXPECT_EQ(img.red(10, 35), 215);
}

TEST_F(CtkRgbImageTest, Test_startSnailIndices) {
    ctk::RgbImage img;
    img.Create(40, 40);
    img.StartSnailIndices();
    for (int i=0; i<img.GetSize(); i++) {
        img.Set(i, i%255, 0, 0);
    }
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"rgb-red-snail.png");
    EXPECT_EQ(img.red(10, 2), 57);
    EXPECT_EQ(img.green(10, 2), 0);
    EXPECT_EQ(img.blue(10, 2), 0);
    EXPECT_EQ(img.red(10, 5), 195);
    EXPECT_EQ(img.red(10, 10), 180);
    EXPECT_EQ(img.red(10, 20), 246);
    EXPECT_EQ(img.red(10, 25), 241);
    EXPECT_EQ(img.red(10, 35), 153);
}

TEST_F(CtkRgbImageTest, Test_startCustomIndices) {
    ctk::RgbImage img;
    img.Create(40, 40);
    std::vector<unsigned int> vec = ctk::RangeVectorUi(0, (40*40)-1);
    ctk::Shuffle(vec, 0);
    img.StartCustomIndices(vec);
    for (int i=0; i<img.GetSize(); i++) {
        img.Set(i, i%255, 0, 0);
    }
    if (SAVE_IMAGES) img.Save(OUTPUT_DIR+"rgb-red-custom.png");

    //TODO - verificar geração de num pseudo aleatorios em SO diferentes
    /**EXPECT_EQ(img.red(10, 2), 208);
    EXPECT_EQ(img.green(10, 2), 0);
    EXPECT_EQ(img.blue(10, 2), 0);
    EXPECT_EQ(img.red(10, 5), 64);
    EXPECT_EQ(img.red(10, 10), 96);
    EXPECT_EQ(img.red(10, 20), 192);
    EXPECT_EQ(img.red(10, 25), 138);
    EXPECT_EQ(img.red(10, 35), 214);**/
}

TEST_F(CtkRgbImageTest, Test_toGrayImage) {
    ctk::RgbImage rgb = CtkRgbImageTest::rgbimg;
    ctk::GrayImage gray = rgb.toGrayImage();
    if (SAVE_IMAGES) gray.Save(OUTPUT_DIR+"rgb2gray.jpg");
    EXPECT_EQ(gray.GetWidth(), rgb.GetWidth());
    EXPECT_EQ(gray.GetHeight(), rgb.GetHeight());
    EXPECT_EQ(gray.GetChannels(), 1);
    EXPECT_EQ(gray.CheckChannel(), true);
    //
    ctk::RgbImage color;
    color.Create(100, 100);
    for (int x=0; x<100; x++) {
        for (int y=0; y<100; y++) {
            color.Set(x, y, x+y, 0, 0);
        }
    }
    ctk::GrayImage color2gray = color.toGrayImage();
    for (int x=0; x<color2gray.GetWidth(); x++) {
        for (int y=0; y<color2gray.GetHeight(); y++) {
            int v = static_cast<int>(static_cast<float>(x+y)*0.299);
            EXPECT_LE(std::abs(color2gray.Get(x,y)-v),1);
        }
    }
    if (SAVE_IMAGES || 1) color.Save(OUTPUT_DIR+"rgb2gray-red.png");
}

TEST_F(CtkRgbImageTest, Test_CreateAndFill) {
    ctk::RgbImage rgb1;
    rgb1.CreateAndFill(200,200,255,255,255);
    EXPECT_EQ(rgb1.GetWidth(), 200);
    EXPECT_EQ(rgb1.GetHeight(), 200);
    EXPECT_EQ(rgb1.GetChannels(), 3);
    EXPECT_EQ(rgb1.CheckChannel(), true);
    int w = rgb1.GetWidth();
    int h = rgb1.GetHeight();
    cv::Mat data = rgb1.GetData();
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            EXPECT_EQ(rgb1.Get(x,y),cv::Vec3b(255,255,255));
        }
    }

    ctk::RgbImage rgb2;
    rgb2.CreateAndFill(200,200,255,200,100);
    EXPECT_EQ(rgb2.GetWidth(), 200);
    EXPECT_EQ(rgb2.GetHeight(), 200);
    EXPECT_EQ(rgb2.GetChannels(), 3);
    EXPECT_EQ(rgb2.CheckChannel(), true);
    int w2 = rgb2.GetWidth();
    int h2 = rgb2.GetHeight();
    cv::Mat data2 = rgb2.GetData();
    for (int x=0; x<w2; x++) {
        for (int y=0; y<h2; y++) {
            EXPECT_EQ(rgb2.Get(x,y),cv::Vec3b(255,200,100));
        }
    }

    ctk::RgbImage rgb0;
    rgb0.CreateAndFill(200,200,0,0,0);
    EXPECT_EQ(rgb0.GetWidth(), 200);
    EXPECT_EQ(rgb0.GetHeight(), 200);
    EXPECT_EQ(rgb0.GetChannels(), 3);
    EXPECT_EQ(rgb0.CheckChannel(), true);
    int w0 = rgb0.GetWidth();
    int h0 = rgb0.GetHeight();
    for (int x=0; x<w0; x++) {
        for (int y=0; y<h0; y++) {
            EXPECT_EQ(rgb0.Get(x,y),cv::Vec3b(0,0,0));
        }
    }

    ctk::RgbImage rgb_t1;
    ASSERT_ANY_THROW(rgb_t1.CreateAndFill(10,10,-1,5,5));
    try {
        rgb_t1.CreateAndFill(10,10,-1,5,5);
    } catch (std::exception &e) {
        EXPECT_EQ(std::string(e.what()),std::string("Parameters incompatible\n"));
    }
    ctk::RgbImage rgb_t2;
    ASSERT_ANY_THROW(rgb_t2.CreateAndFill(10,10,5,256,5));
    try {
        rgb_t2.CreateAndFill(10,10,5,256,5);
    } catch (std::exception &e) {
        EXPECT_EQ(std::string(e.what()),std::string("Parameters incompatible\n"));
    }

}
#endif
