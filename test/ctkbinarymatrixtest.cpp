#include "ctkbinarymatrixtest.h"

extern std::string INPUT_DIR;
extern std::string OUTPUT_DIR;
extern bool SAVE_IMAGES;

void CtkBinaryMatrixTest::SetUp()
{
    binimg.Open(INPUT_DIR+"mask.png");
}

TEST_F(CtkBinaryMatrixTest, Test_Setup) {
    EXPECT_EQ(CtkBinaryMatrixTest::binimg.width(), 200);
    EXPECT_EQ(CtkBinaryMatrixTest::binimg.height(), 200);
    EXPECT_EQ(CtkBinaryMatrixTest::binimg.channels(), 1);
    EXPECT_EQ(CtkBinaryMatrixTest::binimg.CheckChannel(), true);
}

TEST_F(CtkBinaryMatrixTest, Test_Get) {
    int w = CtkBinaryMatrixTest::binimg.width();
    int h = CtkBinaryMatrixTest::binimg.height();
    for (int x=0; x<w; x++) {
        for (int y=0; y<h; y++) {
            if (x<50 || x>=150 || y<50 || y>=150) {
                EXPECT_EQ(CtkBinaryMatrixTest::binimg.get(x,y), true);
            }
            else {
                EXPECT_EQ(CtkBinaryMatrixTest::binimg.get(x,y), false);
            }
        }
    }
}

TEST_F(CtkBinaryMatrixTest, Test_ConstructorCopy) {
    ctk::BinaryMatrix bin(CtkBinaryMatrixTest::binimg);
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

TEST_F(CtkBinaryMatrixTest, Test_ConstructorMat) {
    cv::Mat matbin = cv::imread(INPUT_DIR+"mask.png", cv::IMREAD_UNCHANGED);
    ctk::BinaryMatrix bin(matbin);
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

TEST_F(CtkBinaryMatrixTest, Test_OperatorCopy) {
    ctk::BinaryMatrix bin = CtkBinaryMatrixTest::binimg;
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

TEST_F(CtkBinaryMatrixTest, Test_OperatorNeg) {
    ctk::BinaryMatrix bin = CtkBinaryMatrixTest::binimg.Not();
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

TEST_F(CtkBinaryMatrixTest, Test_OperatorAnd) {
    ctk::BinaryMatrix m2;
    m2.Open(INPUT_DIR+"mask2.png");
    ctk::BinaryMatrix bin = CtkBinaryMatrixTest::binimg.And(m2);
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

TEST_F(CtkBinaryMatrixTest, Test_OperatorOr) {
    ctk::BinaryMatrix m2;
    m2.Open(INPUT_DIR+"mask2.png");
    ctk::BinaryMatrix bin = CtkBinaryMatrixTest::binimg.Or(m2);
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

TEST_F(CtkBinaryMatrixTest, Test_OperatorXor) {
    ctk::BinaryMatrix m2;
    m2.Open(INPUT_DIR+"mask2.png");
    ctk::BinaryMatrix bin = CtkBinaryMatrixTest::binimg.Xor(m2);
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

TEST_F(CtkBinaryMatrixTest, Test_CountTrues) {
    ctk::BinaryMatrix m1, m2, m3, m4, m5, m6;
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

TEST_F(CtkBinaryMatrixTest, Test_CountFalses) {
    ctk::BinaryMatrix m1, m2, m3, m4, m5, m6;
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
