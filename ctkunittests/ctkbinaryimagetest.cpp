#include "ctkbinaryimagetest.h"

#include "ctktestsetup.h"


void CtkBinaryImageTest::SetUp()
{
    binimg.Open(INPUT_DIR+"mask.png");
}

#ifdef TEST_BINARY_IMAGE
TEST_F(CtkBinaryImageTest, Test_Setup) {
    EXPECT_EQ(CtkBinaryImageTest::binimg.width(), 200);
    EXPECT_EQ(CtkBinaryImageTest::binimg.height(), 200);
    EXPECT_EQ(CtkBinaryImageTest::binimg.channels(), 1);
    EXPECT_EQ(CtkBinaryImageTest::binimg.CheckChannel(), true);
}

TEST_F(CtkBinaryImageTest, Test_Get) {
    int w = CtkBinaryImageTest::binimg.width();
    int h = CtkBinaryImageTest::binimg.height();
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            if (x<50 || x>=150 || y<50 || y>=150) {
                EXPECT_EQ(CtkBinaryImageTest::binimg.get(x,y), true);
            }
            else {
                EXPECT_EQ(CtkBinaryImageTest::binimg.get(x,y), false);
            }
        }
    }
}

TEST_F(CtkBinaryImageTest, Test_ConstructorCopy) {
    ctk::BinaryImage bin(CtkBinaryImageTest::binimg);
    EXPECT_EQ(bin.width(), 200);
    EXPECT_EQ(bin.height(), 200);
    EXPECT_EQ(bin.channels(), 1);
    EXPECT_EQ(bin.CheckChannel(), true);
    int w = bin.width();
    int h = bin.height();
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            if (x<50 || x>=150 || y<50 || y>=150) {
                EXPECT_EQ(bin.get(x,y), true);
            }
            else {
                EXPECT_EQ(bin.get(x,y), false);
            }
        }
    }
}

TEST_F(CtkBinaryImageTest, Test_ConstructorMat) {
    cv::Mat matbin = cv::imread(INPUT_DIR+"mask.png", cv::IMREAD_UNCHANGED);
    ctk::BinaryImage bin(matbin);
    EXPECT_EQ(bin.width(), 200);
    EXPECT_EQ(bin.height(), 200);
    EXPECT_EQ(bin.channels(), 1);
    EXPECT_EQ(bin.CheckChannel(), true);
    int w = bin.width();
    int h = bin.height();
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            if (x<50 || x>=150 || y<50 || y>=150) {
                EXPECT_EQ(bin.get(x,y), true);
            }
            else {
                EXPECT_EQ(bin.get(x,y), false);
            }
        }
    }
}

TEST_F(CtkBinaryImageTest, Test_OperatorCopy) {
    ctk::BinaryImage bin = CtkBinaryImageTest::binimg;
    EXPECT_EQ(bin.width(), 200);
    EXPECT_EQ(bin.height(), 200);
    EXPECT_EQ(bin.channels(), 1);
    EXPECT_EQ(bin.CheckChannel(), true);
    int w = bin.width();
    int h = bin.height();
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            if (x<50 || x>=150 || y<50 || y>=150) {
                EXPECT_EQ(bin.get(x,y), true);
            }
            else {
                EXPECT_EQ(bin.get(x,y), false);
            }
        }
    }
}

TEST_F(CtkBinaryImageTest, Test_CreateAndFill) {
    ctk::BinaryImage bin1;
    bin1.CreateAndFill(200,200,true);
    EXPECT_EQ(bin1.width(), 200);
    EXPECT_EQ(bin1.height(), 200);
    EXPECT_EQ(bin1.channels(), 1);
    EXPECT_EQ(bin1.CheckChannel(), true);
    int w = bin1.width();
    int h = bin1.height();
    cv::Mat data = bin1.get_data();
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            EXPECT_EQ(bin1.get(x,y),true);
        }
    }
    ctk::BinaryImage bin0;
    bin0.CreateAndFill(200,200,false);
    EXPECT_EQ(bin0.width(), 200);
    EXPECT_EQ(bin0.height(), 200);
    EXPECT_EQ(bin0.channels(), 1);
    EXPECT_EQ(bin0.CheckChannel(), true);
    int w0 = bin0.width();
    int h0 = bin0.height();
    for (int x=0; x<w0; x++) {
        for (int y=0; y<h0; y++) {
            EXPECT_EQ(bin0.get(x,y),false);
        }
    }
}

TEST_F(CtkBinaryImageTest, Test_OperatorNeg) {
    ctk::BinaryImage bin = CtkBinaryImageTest::binimg.Not();
    if (SAVE_IMAGES) bin.Save(OUTPUT_DIR+"maskinv.png");
    EXPECT_EQ(bin.width(), 200);
    EXPECT_EQ(bin.height(), 200);
    EXPECT_EQ(bin.channels(), 1);
    EXPECT_EQ(bin.CheckChannel(), true);
    int w = bin.width();
    int h = bin.height();
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            if (x<50 || x>=150 || y<50 || y>=150) {
                EXPECT_EQ(bin.get(x,y), false);
            }
            else {
                EXPECT_EQ(bin.get(x,y), true);
            }
        }
    }
}

TEST_F(CtkBinaryImageTest, Test_OperatorAnd) {
    ctk::BinaryImage m2;
    m2.Open(INPUT_DIR+"mask2.png");
    ctk::BinaryImage bin = CtkBinaryImageTest::binimg.And(m2);
    if (SAVE_IMAGES) bin.Save(OUTPUT_DIR+"maskM1AndM2.png");
    EXPECT_EQ(bin.width(), 200);
    EXPECT_EQ(bin.height(), 200);
    EXPECT_EQ(bin.channels(), 1);
    EXPECT_EQ(bin.CheckChannel(), true);
    int w = bin.width();
    int h = bin.height();
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            if (x>=150 && y>=150){
                EXPECT_EQ(bin.get(x,y), false);
            }
            else if (x<50 || x>=150 || y<50 || y>=150) {
                EXPECT_EQ(bin.get(x,y), true);
            }
            else {
                EXPECT_EQ(bin.get(x,y), false);
            }
        }
    }
}

TEST_F(CtkBinaryImageTest, Test_OperatorOr) {
    ctk::BinaryImage m2;
    m2.Open(INPUT_DIR+"mask2.png");
    ctk::BinaryImage bin = CtkBinaryImageTest::binimg.Or(m2);
    if (SAVE_IMAGES) bin.Save(OUTPUT_DIR+"maskM1orM2.png");
    EXPECT_EQ(bin.width(), 200);
    EXPECT_EQ(bin.height(), 200);
    EXPECT_EQ(bin.channels(), 1);
    EXPECT_EQ(bin.CheckChannel(), true);
    int w = bin.width();
    int h = bin.height();
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            if (x<50 || x>=150 || y<50 || y>=150) {
                EXPECT_EQ(bin.get(x,y), true);
            }
            else if (x>=50 && x<100 && y>=50 && y<100) {
                EXPECT_EQ(bin.get(x,y), true);
            }
            else {
                EXPECT_EQ(bin.get(x,y), false);
            }
        }
    }
}

TEST_F(CtkBinaryImageTest, Test_OperatorXor) {
    ctk::BinaryImage m2;
    m2.Open(INPUT_DIR+"mask2.png");
    ctk::BinaryImage bin = CtkBinaryImageTest::binimg.Xor(m2);
    if (SAVE_IMAGES) bin.Save(OUTPUT_DIR+"maskM1xorM2.png");
    EXPECT_EQ(bin.width(), 200);
    EXPECT_EQ(bin.height(), 200);
    EXPECT_EQ(bin.channels(), 1);
    EXPECT_EQ(bin.CheckChannel(), true);
    int w = bin.width();
    int h = bin.height();
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            if (x>=50 && x<100 && y>=50 && y<100) {
                EXPECT_EQ(bin.get(x,y), true);
            }
            else if (x>=150 && y>=150){
                EXPECT_EQ(bin.get(x,y), true);
            }
            else {
                EXPECT_EQ(bin.get(x,y), false);
            }
        }
    }
}

TEST_F(CtkBinaryImageTest, Test_CountTrues) {
    ctk::BinaryImage m1, m2, m3, m4, m5, m6;
    m1.Open(INPUT_DIR+"mask.png");
    m2.Open(INPUT_DIR+"mask2.png");
    m3.Open(INPUT_DIR+"maskM1AndM2.png");
    m4.Open(INPUT_DIR+"maskM1orM2.png");
    m5.Open(INPUT_DIR+"maskM1xorM2.png");
    m6.Open(INPUT_DIR+"maskinv.png");
    EXPECT_EQ(m1.countTrues(), 30000);
    EXPECT_EQ(m2.countTrues(), 30000);
    EXPECT_EQ(m3.countTrues(), 27500);
    EXPECT_EQ(m4.countTrues(), 32500);
    EXPECT_EQ(m5.countTrues(), 5000);
    EXPECT_EQ(m6.countTrues(), 10000);
}

TEST_F(CtkBinaryImageTest, Test_CountFalses) {
    ctk::BinaryImage m1, m2, m3, m4, m5, m6;
    m1.Open(INPUT_DIR+"mask.png");
    m2.Open(INPUT_DIR+"mask2.png");
    m3.Open(INPUT_DIR+"maskM1AndM2.png");
    m4.Open(INPUT_DIR+"maskM1orM2.png");
    m5.Open(INPUT_DIR+"maskM1xorM2.png");
    m6.Open(INPUT_DIR+"maskinv.png");
    EXPECT_EQ(m1.countFalses(), 10000);
    EXPECT_EQ(m2.countFalses(), 10000);
    EXPECT_EQ(m3.countFalses(), 12500);
    EXPECT_EQ(m4.countFalses(), 7500);
    EXPECT_EQ(m5.countFalses(), 35000);
    EXPECT_EQ(m6.countFalses(), 30000);
}
#endif
