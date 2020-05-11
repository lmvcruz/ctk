#include "ctknumericmatrixtest.h"

void CtkNumericMatrixTest::SetUp()
{
    mat1a_w = 5;
    mat1a_h = 3;
    //
    data1a = {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 0,
        1, 2, 3, 4, 5
    };
    int i=-1;
    mat1a.Create(mat1a_w,mat1a_h);
    for (auto it=mat1a.begin(); it!=mat1a.end(); it++) {
        *it = data1a[++i];
    }
    mat1a.Save("teste_1a.tiff");
    //
    mat1b_w = 2;
    mat1b_h = mat1a_w;
    data1b = {
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 0
    };
    i=-1;
    mat1b.Create(mat1b_w,mat1b_h);
    for (auto it=mat1b.begin(); it!=mat1b.end(); it++) {
        *it = data1b[++i];
    }
    mat1b.Save("teste_1b.tiff");
    //
    data1c = {
        95, 60,
        130, 160,
        95, 60,
    };
    i=-1;
    mat1c.Create(mat1b_w,mat1a_h);
    for (auto it=mat1c.begin(); it!=mat1c.end(); it++) {
        *it = data1c[++i];
    }
    mat1c.Save("teste_1c.tiff");
    //
    mat2_w = 1000;
    mat2_h = 400;
    data2a.resize(mat2_w*mat2_h);
    mat2a.Create(mat2_w, mat2_h);
    double v;
    int idx;
    double imd = static_cast<double>(INT_MAX);
    for (int y=0; y<mat2_h; y++) {
        for (int x=0; x<mat2_w; x++) {
            idx = y*mat2_w + x;
            v = imd+static_cast<double>(-50+(rand()%100));
            data2a[idx] = v;
            mat2a.set(x,y, v);
        }
    }
    //
    data2b.resize(data2a.size());
    for (auto &v: data2b) v = static_cast<double>(-1000+(rand()%2000));
    //
    mat3_w = 3;
    mat3_h = 3;
    data3 = {
        1, 2, 3,
        3, 5, 3,
        1, 2, 1
    };
    i=-1;
    mat3.Create(mat3_w,mat3_h);
    for (auto it=mat3.begin(); it!=mat3.end(); it++) {
        *it = data3[++i];
    }
    data3i = {
        -0.5, 2, -4.5,
        0, -1, 3,
        0.5, 0, -0.5
    };
    i=-1;
    mat3i.Create(mat3_w,mat3_h);
    for (auto it=mat3i.begin(); it!=mat3i.end(); it++) {
        *it = data3i[++i];
    }
    //
    mat4_w = 3;
    mat4_h = 2;
    std::vector<double> data4 {
        1, 2, 3,
        4, 5, 6
    };
    i = -1;
    mat4.Create(mat4_w,mat4_h);
    for (auto it=mat4.begin(); it!=mat4.end(); it++) {
        *it = data4[++i];
    }
    //
    std::vector<double> data_4div3 {
        1, 0, 0,
        1, 3, -6
    };
    mat_4_div_3.Create(mat3_w,mat4_h);
    i=-1;
    for (auto it=mat_4_div_3.begin(); it!=mat_4_div_3.end(); it++) {
        *it = data_4div3[++i];
    }
}

TEST_F(CtkNumericMatrixTest, Test_Setup) {
    EXPECT_EQ(CtkNumericMatrixTest::data1a.size(), 15);
    EXPECT_EQ(CtkNumericMatrixTest::mat1a.width(), 5);
    EXPECT_EQ(CtkNumericMatrixTest::mat1a.cols(), 5);
    EXPECT_EQ(CtkNumericMatrixTest::mat1a.height(), 3);
    EXPECT_EQ(CtkNumericMatrixTest::mat1a.rows(), 3);
    EXPECT_EQ(CtkNumericMatrixTest::mat1a.size(), 15);
    EXPECT_EQ(CtkNumericMatrixTest::mat1a.channels(), 1);
    EXPECT_EQ(CtkNumericMatrixTest::mat1a.CheckChannel(), true);

    for (int y=0; y<CtkNumericMatrixTest::mat1a_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat1a_w; x++) {
            int idx = y*CtkNumericMatrixTest::mat1a_w + x;
            EXPECT_EQ(CtkNumericMatrixTest::mat1a.get(x,y),
                      CtkNumericMatrixTest::data1a[idx]);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_Setup2) {
    EXPECT_EQ(CtkNumericMatrixTest::data2a.size(),
              CtkNumericMatrixTest::mat2_w*CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(CtkNumericMatrixTest::mat2a.width(),
              CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(CtkNumericMatrixTest::mat2a.cols(),
              CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(CtkNumericMatrixTest::mat2a.height(),
              CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(CtkNumericMatrixTest::mat2a.rows(),
              CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(CtkNumericMatrixTest::mat2a.size(),
              CtkNumericMatrixTest::mat2_w*CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(CtkNumericMatrixTest::mat2a.channels(), 1);
    EXPECT_EQ(CtkNumericMatrixTest::mat2a.CheckChannel(), true);
    //
    int idx;
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            idx = y*CtkNumericMatrixTest::mat2_w + x;
            EXPECT_EQ(CtkNumericMatrixTest::mat2a.get(x,y),
                      CtkNumericMatrixTest::data2a[idx]);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_OpenSave) {
    ctk::NumericMatrix mat_b;
    mat_b.Open("teste_1a.tiff");
    //
    EXPECT_EQ(mat_b.width(), 5);
    EXPECT_EQ(mat_b.cols(), 5);
    EXPECT_EQ(mat_b.height(), 3);
    EXPECT_EQ(mat_b.rows(), 3);
    EXPECT_EQ(mat_b.size(), 15);
    EXPECT_EQ(mat_b.channels(), 1);
    EXPECT_EQ(mat_b.CheckChannel(), true);
    for (int y=0; y<CtkNumericMatrixTest::mat1a_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat1a_w; x++) {
            int idx = y*CtkNumericMatrixTest::mat1a_w + x;
            EXPECT_EQ(mat_b.get(x,y),
                      CtkNumericMatrixTest::data1a[idx]);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_ContructorCopy) {
    ctk::NumericMatrix mat_b(CtkNumericMatrixTest::mat2a);
    //
    EXPECT_EQ(mat_b.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_b.cols(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_b.height(), CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(mat_b.rows(), CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(mat_b.size(),
              CtkNumericMatrixTest::mat2_w*CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(mat_b.channels(), 1);
    EXPECT_EQ(mat_b.CheckChannel(), true);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            int idx = y*CtkNumericMatrixTest::mat2_w + x;
            EXPECT_EQ(mat_b.get(x,y),
                      CtkNumericMatrixTest::data2a[idx]);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_OperatorAtt) {
    ctk::NumericMatrix mat_b = CtkNumericMatrixTest::mat2a;
    //
    EXPECT_EQ(mat_b.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_b.cols(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_b.height(), CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(mat_b.rows(), CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(mat_b.size(),
              CtkNumericMatrixTest::mat2_w*CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(mat_b.channels(), 1);
    EXPECT_EQ(mat_b.CheckChannel(), true);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            int idx = y*CtkNumericMatrixTest::mat2_w + x;
            EXPECT_EQ(mat_b.get(x,y),
                      CtkNumericMatrixTest::data2a[idx]);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_ConstructorMat) {
    ctk::NumericMatrix mat_b(CtkNumericMatrixTest::mat2a.get_data());
    //
    EXPECT_EQ(mat_b.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_b.cols(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_b.height(), CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(mat_b.rows(), CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(mat_b.size(),
              CtkNumericMatrixTest::mat2_w*CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(mat_b.channels(), 1);
    EXPECT_EQ(mat_b.CheckChannel(), true);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            int idx = y*CtkNumericMatrixTest::mat2_w + x;
            EXPECT_EQ(mat_b.get(x,y),
                      CtkNumericMatrixTest::data2a[idx]);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_ConstructorVector) {
    ctk::NumericMatrix mat_b(CtkNumericMatrixTest::mat2_w,
                             CtkNumericMatrixTest::mat2_h,
                             CtkNumericMatrixTest::data2a);
    //
    EXPECT_EQ(mat_b.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_b.cols(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_b.height(), CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(mat_b.rows(), CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(mat_b.size(),
              CtkNumericMatrixTest::mat2_w*CtkNumericMatrixTest::mat2_h);
    EXPECT_EQ(mat_b.channels(), 1);
    EXPECT_EQ(mat_b.CheckChannel(), true);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            int idx = y*CtkNumericMatrixTest::mat2_w + x;
            EXPECT_EQ(mat_b.get(x,y),
                      CtkNumericMatrixTest::data2a[idx]);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_Equals) {
    ctk::NumericMatrix mat_b;
    int i=-1;
    mat_b.Create(mat1a_w,mat1a_h);
    for (auto it=mat_b.begin(); it!=mat_b.end(); it++) {
        *it = data1a[++i];
    }
    //
    EXPECT_EQ(mat_b==CtkNumericMatrixTest::mat1a, true);
    EXPECT_EQ(mat_b==CtkNumericMatrixTest::mat2a, false);
    EXPECT_EQ(mat_b!=CtkNumericMatrixTest::mat1a, false);
    EXPECT_EQ(mat_b!=CtkNumericMatrixTest::mat2a, true);
}

TEST_F(CtkNumericMatrixTest, Test_Sum) {
    ctk::NumericMatrix mat_b(CtkNumericMatrixTest::mat2_w,
                             CtkNumericMatrixTest::mat2_h,
                             CtkNumericMatrixTest::data2b);
    ctk::NumericMatrix mat_c = CtkNumericMatrixTest::mat2a + mat_b;
    //
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            int idx = y*CtkNumericMatrixTest::mat2_w + x;
            EXPECT_EQ(mat_c.get(x,y),
                      CtkNumericMatrixTest::data2a[idx]
                      +CtkNumericMatrixTest::data2b[idx]);
            EXPECT_EQ(mat_c.get(x,y),
                      CtkNumericMatrixTest::mat2a.get(x,y)
                      +mat_b.get(x,y));
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_SelfSum) {
    ctk::NumericMatrix mat_a(CtkNumericMatrixTest::mat2a);
    ctk::NumericMatrix mat_b(CtkNumericMatrixTest::mat2_w,
                             CtkNumericMatrixTest::mat2_h,
                             CtkNumericMatrixTest::data2b);
    //
    mat_a += mat_b;
    //
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            int idx = y*CtkNumericMatrixTest::mat2_w + x;
            EXPECT_EQ(mat_a.get(x,y),
                      CtkNumericMatrixTest::data2a[idx]
                      +CtkNumericMatrixTest::data2b[idx]);
            EXPECT_EQ(mat_a.get(x,y),
                      CtkNumericMatrixTest::mat2a.get(x,y)
                      +mat_b.get(x,y));
        }
    }
}


TEST_F(CtkNumericMatrixTest, Test_Diff) {
    ctk::NumericMatrix mat_b(CtkNumericMatrixTest::mat2_w,
                             CtkNumericMatrixTest::mat2_h,
                             CtkNumericMatrixTest::data2b);
    ctk::NumericMatrix mat_c = CtkNumericMatrixTest::mat2a - mat_b;
    //
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            int idx = y*CtkNumericMatrixTest::mat2_w + x;
            EXPECT_EQ(mat_c.get(x,y),
                      CtkNumericMatrixTest::data2a[idx]
                      - CtkNumericMatrixTest::data2b[idx]);
            EXPECT_EQ(mat_c.get(x,y),
                      CtkNumericMatrixTest::mat2a.get(x,y)
                      - mat_b.get(x,y));
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_SelfDiff) {
    ctk::NumericMatrix mat_a(CtkNumericMatrixTest::mat2a);
    ctk::NumericMatrix mat_b(CtkNumericMatrixTest::mat2_w,
                             CtkNumericMatrixTest::mat2_h,
                             CtkNumericMatrixTest::data2b);
    //
    mat_a -= mat_b;
    //
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            int idx = y*CtkNumericMatrixTest::mat2_w + x;
            EXPECT_EQ(mat_a.get(x,y),
                      CtkNumericMatrixTest::data2a[idx]
                      - CtkNumericMatrixTest::data2b[idx]);
            EXPECT_EQ(mat_a.get(x,y),
                      CtkNumericMatrixTest::mat2a.get(x,y)
                      - mat_b.get(x,y));
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_Mult) {
    ctk::NumericMatrix mat_c = CtkNumericMatrixTest::mat1a
            * CtkNumericMatrixTest::mat1b;
    //
    EXPECT_EQ(mat_c.width(), CtkNumericMatrixTest::mat1b_w);
    EXPECT_EQ(mat_c.height(), CtkNumericMatrixTest::mat1a_h);
    for (int y=0; y<mat_c.height(); y++) {
        for (int x=0; x<mat_c.width(); x++) {
            EXPECT_EQ(mat_c.get(x,y),
                      CtkNumericMatrixTest::mat1c.get(x,y));
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_SelfMult) {
    ctk::NumericMatrix mat_a(CtkNumericMatrixTest::mat1a);
    mat_a *= CtkNumericMatrixTest::mat1b;
    //
    EXPECT_EQ(mat_a.width(), CtkNumericMatrixTest::mat1b_w);
    EXPECT_EQ(mat_a.height(), CtkNumericMatrixTest::mat1a_h);
    for (int y=0; y<mat_a.height(); y++) {
        for (int x=0; x<mat_a.width(); x++) {
            EXPECT_EQ(mat_a.get(x,y),
                      CtkNumericMatrixTest::mat1c.get(x,y));
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_Div) {
    ctk::NumericMatrix mat_c = CtkNumericMatrixTest::mat4
            / CtkNumericMatrixTest::mat3;
    //
    EXPECT_EQ(mat_c.width(), CtkNumericMatrixTest::mat3_w);
    EXPECT_EQ(mat_c.height(), CtkNumericMatrixTest::mat4_h);
    for (int y=0; y<mat_c.height(); y++) {
        for (int x=0; x<mat_c.width(); x++) {
            EXPECT_EQ(mat_c.get(x,y),
                      CtkNumericMatrixTest::mat_4_div_3.get(x,y));
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_SelfDiv) {
    ctk::NumericMatrix mat_c(CtkNumericMatrixTest::mat4);
    mat_c /= CtkNumericMatrixTest::mat3;
    //
    EXPECT_EQ(mat_c.width(), CtkNumericMatrixTest::mat3_w);
    EXPECT_EQ(mat_c.height(), CtkNumericMatrixTest::mat4_h);
    for (int y=0; y<mat_c.height(); y++) {
        for (int x=0; x<mat_c.width(); x++) {
            EXPECT_EQ(mat_c.get(x,y),
                      CtkNumericMatrixTest::mat_4_div_3.get(x,y));
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_SumNumDouble) {
    double v = 10.;
    ctk::NumericMatrix mat_a = CtkNumericMatrixTest::mat2a + v;
    //
    EXPECT_EQ(mat_a.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_a.height(), CtkNumericMatrixTest::mat2_h);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            EXPECT_EQ(mat_a.get(x,y),
                      CtkNumericMatrixTest::mat2a.get(x,y) + v);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_SumNumInt) {
    int v = 10;
    ctk::NumericMatrix mat_a = CtkNumericMatrixTest::mat2a + v;
    //
    EXPECT_EQ(mat_a.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_a.height(), CtkNumericMatrixTest::mat2_h);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            EXPECT_EQ(mat_a.get(x,y),
                      CtkNumericMatrixTest::mat2a.get(x,y) + v);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_SumNumBig) {
    double v = FLT_MAX;
    ctk::NumericMatrix mat_a = CtkNumericMatrixTest::mat2a + v;
    //
    EXPECT_EQ(mat_a.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_a.height(), CtkNumericMatrixTest::mat2_h);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            EXPECT_LE(fabs( mat_a.get(x,y) -
                            (CtkNumericMatrixTest::mat2a.get(x,y) + v)
                          ), FLT_EPSILON);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_SelfSumNum) {
    double v = FLT_MAX;
    ctk::NumericMatrix mat_a(CtkNumericMatrixTest::mat2a);
    mat_a += v;
    //
    EXPECT_EQ(mat_a.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_a.height(), CtkNumericMatrixTest::mat2_h);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            EXPECT_LE(fabs( mat_a.get(x,y) -
                            (CtkNumericMatrixTest::mat2a.get(x,y) + v)
                          ), FLT_EPSILON);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_DiffNum) {
    double v = FLT_MAX;
    ctk::NumericMatrix mat_a = CtkNumericMatrixTest::mat2a - v;
    //
    EXPECT_EQ(mat_a.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_a.height(), CtkNumericMatrixTest::mat2_h);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            EXPECT_LE(fabs( mat_a.get(x,y) -
                            (CtkNumericMatrixTest::mat2a.get(x,y) - v)
                          ), FLT_EPSILON);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_SelfDiffNum) {
    double v = FLT_MAX;
    ctk::NumericMatrix mat_a(CtkNumericMatrixTest::mat2a);
    mat_a -= v;
    //
    EXPECT_EQ(mat_a.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_a.height(), CtkNumericMatrixTest::mat2_h);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            EXPECT_LE(fabs( mat_a.get(x,y) -
                            (CtkNumericMatrixTest::mat2a.get(x,y) - v)
                          ), FLT_EPSILON);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_MultNum) {
    double v = FLT_MAX;
    ctk::NumericMatrix mat_a = CtkNumericMatrixTest::mat2a * v;
    //
    EXPECT_EQ(mat_a.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_a.height(), CtkNumericMatrixTest::mat2_h);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            EXPECT_LE(fabs( mat_a.get(x,y) -
                            (CtkNumericMatrixTest::mat2a.get(x,y) * v)
                          ), FLT_EPSILON);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_SelfMultNum) {
    double v = FLT_MAX;
    ctk::NumericMatrix mat_a(CtkNumericMatrixTest::mat2a);
    mat_a *= v;
    //
    EXPECT_EQ(mat_a.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_a.height(), CtkNumericMatrixTest::mat2_h);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            EXPECT_LE(fabs( mat_a.get(x,y) -
                            (CtkNumericMatrixTest::mat2a.get(x,y) * v)
                          ), FLT_EPSILON);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_DivNum) {
    double v = 10.;
    ctk::NumericMatrix mat_a = CtkNumericMatrixTest::mat2a / v;
    //
    EXPECT_EQ(mat_a.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_a.height(), CtkNumericMatrixTest::mat2_h);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            EXPECT_LE(fabs( mat_a.get(x,y) -
                            (CtkNumericMatrixTest::mat2a.get(x,y) / v)
                          ), FLT_EPSILON);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_SelfDivNum) {
    double v = 10.;
    ctk::NumericMatrix mat_a(CtkNumericMatrixTest::mat2a);
    mat_a /= v;
    //
    EXPECT_EQ(mat_a.width(), CtkNumericMatrixTest::mat2_w);
    EXPECT_EQ(mat_a.height(), CtkNumericMatrixTest::mat2_h);
    for (int y=0; y<CtkNumericMatrixTest::mat2_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat2_w; x++) {
            EXPECT_LE(fabs( mat_a.get(x,y) -
                            (CtkNumericMatrixTest::mat2a.get(x,y) / v)
                          ), FLT_EPSILON);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_Determinant) {
    EXPECT_LE(std::fabs(CtkNumericMatrixTest::mat3.determinant()-2.0),
              FLT_EPSILON);
    EXPECT_LE(std::fabs(CtkNumericMatrixTest::mat3i.determinant()-0.5),
              FLT_EPSILON);
    ctk::NumericMatrix mat = CtkNumericMatrixTest::mat3 *
            CtkNumericMatrixTest::mat3i;
    EXPECT_LE(std::fabs(mat.determinant()-1.0), FLT_EPSILON);
}

TEST_F(CtkNumericMatrixTest, Test_Inv) {
    ctk::NumericMatrix mat_a = CtkNumericMatrixTest::mat3.Invert();
    for (int y=0; y<CtkNumericMatrixTest::mat3_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat3_w; x++) {
            EXPECT_LE(fabs( mat_a.get(x,y) -
                            CtkNumericMatrixTest::mat3i.get(x,y)
                          ), FLT_EPSILON);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_SelfInv) {
    ctk::NumericMatrix mat_a = CtkNumericMatrixTest::mat3;
    mat_a.SelfInvert();
    for (int y=0; y<CtkNumericMatrixTest::mat3_h; y++) {
        for (int x=0; x<CtkNumericMatrixTest::mat3_w; x++) {
            EXPECT_LE(fabs( mat_a.get(x,y) -
                            CtkNumericMatrixTest::mat3i.get(x,y)
                          ), FLT_EPSILON);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_Transpose) {
    ctk::NumericMatrix mat_a = CtkNumericMatrixTest::mat4.Transpose();
    EXPECT_EQ(mat_a.width(), CtkNumericMatrixTest::mat4_h);
    EXPECT_EQ(mat_a.height(), CtkNumericMatrixTest::mat4_w);
    for (int y=0; y<mat_a.height(); y++) {
        for (int x=0; x<mat_a.width(); x++) {
            EXPECT_LE(fabs( mat_a.get(x,y) -
                            CtkNumericMatrixTest::mat4.get(y,x)
                          ), FLT_EPSILON);
        }
    }
}

TEST_F(CtkNumericMatrixTest, Test_SelfTranspose) {
    ctk::NumericMatrix mat_a = CtkNumericMatrixTest::mat4;
    mat_a.SelfTranspose();
    for (int y=0; y<mat_a.height(); y++) {
        for (int x=0; x<mat_a.width(); x++) {
            EXPECT_LE(fabs( mat_a.get(x,y) -
                            CtkNumericMatrixTest::mat4.get(y,x)
                          ), FLT_EPSILON);
        }
    }
}
