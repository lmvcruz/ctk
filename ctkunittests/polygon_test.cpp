#include "polygon_test.h"

#include "test_setup.h"

#ifdef TEST_POLYGON
TEST_F(CtkPolygonTest, Test_Setup) {
    EXPECT_EQ(CtkPolygonTest::p1.size(),4);
    EXPECT_EQ(CtkPolygonTest::p1cv.size(),4);

    EXPECT_EQ(CtkPolygonTest::p2.size(),10);
    EXPECT_EQ(CtkPolygonTest::p2cv.size(),4);
}

TEST_F(CtkPolygonTest,Test_GetData) {
    ctk::Polygon Poly1(CtkPolygonTest::p1);

    std::vector<ctk::PointD> data = Poly1.GetData();
    EXPECT_DOUBLE_EQ(data[0].GetX(), 0);
    EXPECT_DOUBLE_EQ(data[0].GetY(), 1);
    EXPECT_DOUBLE_EQ(data[1].GetX(), 1);
    EXPECT_DOUBLE_EQ(data[1].GetY(), 1);
    EXPECT_DOUBLE_EQ(data[2].GetX(), 1);
    EXPECT_DOUBLE_EQ(data[2].GetY(), 0);
    EXPECT_DOUBLE_EQ(data[3].GetX(), 0);
    EXPECT_DOUBLE_EQ(data[3].GetY(), 0);
}

TEST_F(CtkPolygonTest,Test_GetCVData) {
    ctk::Polygon Poly1(CtkPolygonTest::p1);

    std::vector<cv::Point> cvData = Poly1.GetCvData();
    EXPECT_DOUBLE_EQ(cvData[0].x, 0);
    EXPECT_DOUBLE_EQ(cvData[0].y, 1);
    EXPECT_DOUBLE_EQ(cvData[1].x, 1);
    EXPECT_DOUBLE_EQ(cvData[1].y, 1);
    EXPECT_DOUBLE_EQ(cvData[2].x, 1);
    EXPECT_DOUBLE_EQ(cvData[2].y, 0);
    EXPECT_DOUBLE_EQ(cvData[3].x, 0);
    EXPECT_DOUBLE_EQ(cvData[3].y, 0);
}

TEST_F(CtkPolygonTest,Test_ConstructorPointD) {
     ctk::Polygon Poly1(CtkPolygonTest::p1);

    EXPECT_EQ(Poly1.GetData().size(), 4);
    EXPECT_EQ(Poly1.GetCvData().size(), 4);
}

TEST_F(CtkPolygonTest,Test_ConstructorCopy) {
    ctk::Polygon Poly1(CtkPolygonTest::p1);

    ctk::Polygon polC(Poly1);
    std::vector<ctk::PointD> data = polC.GetData();
    std::vector<cv::Point> cvData = polC.GetCvData();

    EXPECT_EQ(data.size(), 4);
    EXPECT_EQ(cvData.size(), 4);

    EXPECT_DOUBLE_EQ(data[0].GetX(), 0);
    EXPECT_DOUBLE_EQ(data[0].GetY(), 1);
    EXPECT_DOUBLE_EQ(data[1].GetX(), 1);
    EXPECT_DOUBLE_EQ(data[1].GetY(), 1);
    EXPECT_DOUBLE_EQ(data[2].GetX(), 1);
    EXPECT_DOUBLE_EQ(data[2].GetY(), 0);
    EXPECT_DOUBLE_EQ(data[3].GetX(), 0);
    EXPECT_DOUBLE_EQ(data[3].GetY(), 0);

    EXPECT_EQ(cvData[0].x, 0);
    EXPECT_EQ(cvData[0].y, 1);
    EXPECT_EQ(cvData[1].x, 1);
    EXPECT_EQ(cvData[1].y, 1);
    EXPECT_EQ(cvData[2].x, 1);
    EXPECT_EQ(cvData[2].y, 0);
    EXPECT_EQ(cvData[3].x, 0);
    EXPECT_EQ(cvData[3].y, 0);
}

TEST_F(CtkPolygonTest,Test_OperatorCopyPolygon) {

    ctk::Polygon Poly1(CtkPolygonTest::p1);
    ctk::Polygon polC=Poly1;

    std::vector<ctk::PointD> data = polC.GetData();
    std::vector<cv::Point> cvData = polC.GetCvData();

    EXPECT_EQ(data.size(), 4);
    EXPECT_EQ(cvData.size(), 4);

    EXPECT_DOUBLE_EQ(data[0].GetX(), 0);
    EXPECT_DOUBLE_EQ(data[0].GetY(), 1);
    EXPECT_DOUBLE_EQ(data[1].GetX(), 1);
    EXPECT_DOUBLE_EQ(data[1].GetY(), 1);
    EXPECT_DOUBLE_EQ(data[2].GetX(), 1);
    EXPECT_DOUBLE_EQ(data[2].GetY(), 0);
    EXPECT_DOUBLE_EQ(data[3].GetX(), 0);
    EXPECT_DOUBLE_EQ(data[3].GetY(), 0);

    EXPECT_EQ(cvData[0].x, 0);
    EXPECT_EQ(cvData[0].y, 1);
    EXPECT_EQ(cvData[1].x, 1);
    EXPECT_EQ(cvData[1].y, 1);
    EXPECT_EQ(cvData[2].x, 1);
    EXPECT_EQ(cvData[2].y, 0);
    EXPECT_EQ(cvData[3].x, 0);
    EXPECT_EQ(cvData[3].y, 0);
}

TEST_F(CtkPolygonTest,Test_OperatorCopyPointD) {
    ctk::Polygon polC=CtkPolygonTest::p1;

    std::vector<ctk::PointD> data = polC.GetData();
    std::vector<cv::Point> cvData = polC.GetCvData();

    EXPECT_EQ(data.size(), 4);
    EXPECT_EQ(cvData.size(), 4);

    EXPECT_DOUBLE_EQ(data[0].GetX(), 0);
    EXPECT_DOUBLE_EQ(data[0].GetY(), 1);
    EXPECT_DOUBLE_EQ(data[1].GetX(), 1);
    EXPECT_DOUBLE_EQ(data[1].GetY(), 1);
    EXPECT_DOUBLE_EQ(data[2].GetX(), 1);
    EXPECT_DOUBLE_EQ(data[2].GetY(), 0);
    EXPECT_DOUBLE_EQ(data[3].GetX(), 0);
    EXPECT_DOUBLE_EQ(data[3].GetY(), 0);

    EXPECT_EQ(cvData[0].x, 0);
    EXPECT_EQ(cvData[0].y, 1);
    EXPECT_EQ(cvData[1].x, 1);
    EXPECT_EQ(cvData[1].y, 1);
    EXPECT_EQ(cvData[2].x, 1);
    EXPECT_EQ(cvData[2].y, 0);
    EXPECT_EQ(cvData[3].x, 0);
    EXPECT_EQ(cvData[3].y, 0);
}

TEST_F(CtkPolygonTest,Test_OperatorCopyCVPoint) {
    ctk::Polygon polC=CtkPolygonTest::p1cv;

    std::vector<ctk::PointD> data = polC.GetData();
    std::vector<cv::Point> cvData = polC.GetCvData();

    EXPECT_EQ(data.size(),4);
    EXPECT_EQ(cvData.size(),4);

    EXPECT_DOUBLE_EQ(data[0].GetX(), 0);
    EXPECT_DOUBLE_EQ(data[0].GetY(), 1);
    EXPECT_DOUBLE_EQ(data[1].GetX(), 1);
    EXPECT_DOUBLE_EQ(data[1].GetY(), 1);
    EXPECT_DOUBLE_EQ(data[2].GetX(), 1);
    EXPECT_DOUBLE_EQ(data[2].GetY(), 0);
    EXPECT_DOUBLE_EQ(data[3].GetX(), 0);
    EXPECT_DOUBLE_EQ(data[3].GetY(), 0);

    EXPECT_EQ(cvData[0].x, 0);
    EXPECT_EQ(cvData[0].y, 1);
    EXPECT_EQ(cvData[1].x, 1);
    EXPECT_EQ(cvData[1].y, 1);
    EXPECT_EQ(cvData[2].x, 1);
    EXPECT_EQ(cvData[2].y, 0);
    EXPECT_EQ(cvData[3].x, 0);
    EXPECT_EQ(cvData[3].y, 0);
}

TEST_F(CtkPolygonTest,Test_AddPointPointD) {
    ctk::Polygon polC=CtkPolygonTest::p1cv;
    ctk::PointD n_point(2, 3);

    polC.AddPoint(n_point);

    std::vector<ctk::PointD> data = polC.GetData();
    std::vector<cv::Point> cvData = polC.GetCvData();

    EXPECT_EQ(data.size(), 5);
    EXPECT_EQ(cvData.size(), 5);

    EXPECT_DOUBLE_EQ(data[4].GetX(), 2);
    EXPECT_DOUBLE_EQ(data[4].GetY(), 3);
    EXPECT_EQ(cvData[4].x, 2);
    EXPECT_EQ(cvData[4].y, 3);
}

TEST_F(CtkPolygonTest,Test_AddPointPointxy) {
    ctk::Polygon polC=CtkPolygonTest::p1cv;
    polC.AddPoint(2,3);

    std::vector<ctk::PointD> data = polC.GetData();
    std::vector<cv::Point> cvData = polC.GetCvData();

    EXPECT_EQ(data.size(), 5);
    EXPECT_EQ(cvData.size(), 5);

    EXPECT_DOUBLE_EQ(data[4].GetX(), 2);
    EXPECT_DOUBLE_EQ(data[4].GetY(), 3);
    EXPECT_EQ(cvData[4].x, 2);
    EXPECT_EQ(cvData[4].y, 3);
}

TEST_F(CtkPolygonTest,Test_SetPointPointD) {
    ctk::PointD n_point(2,3);
    ctk::Polygon polC = CtkPolygonTest::p1cv;
    polC.SetPoint(0,n_point);

    std::vector<ctk::PointD> data = polC.GetData();
    std::vector<cv::Point> cvData = polC.GetCvData();

    EXPECT_EQ(data.size(), 4);
    EXPECT_EQ(cvData.size(), 4);

    EXPECT_DOUBLE_EQ(data[0].GetX(), 2);
    EXPECT_DOUBLE_EQ(data[0].GetY(), 3);
    EXPECT_EQ(cvData[0].x, 2);
    EXPECT_EQ(cvData[0].y, 3);
}

TEST_F(CtkPolygonTest,Test_SetPointPointxy) {
    ctk::Polygon polC=CtkPolygonTest::p1cv;
    polC.SetPoint(0, 2, 3);

    std::vector<ctk::PointD> data = polC.GetData();
    std::vector<cv::Point> cvData = polC.GetCvData();

    EXPECT_EQ(data.size(), 4);
    EXPECT_EQ(cvData.size(), 4);

    EXPECT_DOUBLE_EQ(data[0].GetX(), 2);
    EXPECT_DOUBLE_EQ(data[0].GetY(), 3);
    EXPECT_EQ(cvData[0].x, 2);
    EXPECT_EQ(cvData[0].y, 3);
}

TEST_F(CtkPolygonTest,Test_GetPoint) {
    ctk::Polygon polC=CtkPolygonTest::p1cv;
    ctk::PointD point=polC.GetPoint(0);

    EXPECT_EQ(point.GetX(), 0);
    EXPECT_EQ(point.GetY(), 1);
}

TEST_F(CtkPolygonTest,Test_Resize) {
    ctk::Polygon polC = CtkPolygonTest::p1cv;
    polC.Resize(6);

    std::vector<ctk::PointD> data = polC.GetData();
    std::vector<cv::Point> cvData = polC.GetCvData();

    EXPECT_EQ(data.size(), 6);
    EXPECT_EQ(cvData.size(), 6);

    polC.Resize(2);

    std::vector<ctk::PointD> Data_1 = polC.GetData();
    std::vector<cv::Point> cvData_1 = polC.GetCvData();

    EXPECT_EQ(Data_1.size(), 2);
    EXPECT_EQ(cvData_1.size(), 2);
}

TEST_F(CtkPolygonTest,Test_Size) {
    ctk::Polygon polC = CtkPolygonTest::p1cv;
    EXPECT_EQ(polC.size(), 4);
}

TEST_F(CtkPolygonTest,Test_Area) {
    ctk::Polygon pol1 = CtkPolygonTest::p1cv;
    ctk::Polygon pol1cv = CtkPolygonTest::p1cv;
    ctk::Polygon pol2 = CtkPolygonTest::p2;
    ctk::Polygon pol2cv = CtkPolygonTest::p2cv;

    EXPECT_DOUBLE_EQ(pol1.Area(), 1);
    EXPECT_DOUBLE_EQ(pol2.Area(), 9);
    EXPECT_DOUBLE_EQ(pol1cv.Area(), 1);
    EXPECT_DOUBLE_EQ(pol2cv.Area(), 9);
}

TEST_F(CtkPolygonTest,Test_Perimeter) {
    ctk::Polygon pol1=CtkPolygonTest::p1cv;
    ctk::Polygon pol1cv=CtkPolygonTest::p1cv;
    ctk::Polygon pol2=CtkPolygonTest::p2;
    ctk::Polygon pol2cv=CtkPolygonTest::p2cv;

    EXPECT_DOUBLE_EQ(pol1.Perimeter(),4);
    EXPECT_DOUBLE_EQ(pol2.Perimeter(),12);
    EXPECT_DOUBLE_EQ(pol1cv.Perimeter(),4);
    EXPECT_DOUBLE_EQ(pol2cv.Perimeter(),12);
}

TEST_F(CtkPolygonTest,Test_Reduce) {
    ctk::Polygon pol2=CtkPolygonTest::p2;

    ctk::Polygon red2 =pol2.Reduce(1);

    EXPECT_TRUE(red2.size() < pol2.size());
    EXPECT_DOUBLE_EQ(red2.Perimeter(), 12);
    EXPECT_DOUBLE_EQ(red2.Area(), 9);
}

TEST_F(CtkPolygonTest,Test_SelfReduce) {
    ctk::Polygon pol2 = CtkPolygonTest::p2;
    pol2.SelfReduce(1);

    EXPECT_TRUE(pol2.size() < 10);
    EXPECT_DOUBLE_EQ(pol2.Perimeter(), 12);
    EXPECT_DOUBLE_EQ(pol2.Area(), 9);
}


TEST_F(CtkPolygonTest,Test_Shift) {
    ctk::Polygon pol1 = CtkPolygonTest::p1;
    ctk::Polygon pol1s = pol1.Shift(1);
    EXPECT_EQ(pol1.size(), pol1s.size());

    std::vector<cv::Point> datacv = pol1.GetCvData();
    std::vector<cv::Point> datascv = pol1s.GetCvData();

    std::vector<ctk::PointD> data = pol1.GetData();
    std::vector<ctk::PointD> datas = pol1s.GetData();

    for(int i = 0; i < pol1.size(); ++i) {
        if (i == 0) {
            EXPECT_EQ(datacv[i].x, datascv[pol1.size()-1].x);
            EXPECT_EQ(datacv[i].y, datascv[pol1.size()-1].y);

            EXPECT_DOUBLE_EQ(data[i].GetX(), datas[pol1.size()-1].GetX());
            EXPECT_DOUBLE_EQ(data[i].GetY(), datas[pol1.size()-1].GetY());
        }
        else{
            EXPECT_EQ(datacv[i].x, datascv[i-1].x);
            EXPECT_EQ(datacv[i].y, datascv[i-1].y);
            EXPECT_DOUBLE_EQ(data[i].GetX(), datas[i-1].GetX());
            EXPECT_DOUBLE_EQ(data[i].GetY(), datas[i-1].GetY());
        }
    }
}

TEST_F(CtkPolygonTest,SelfShift) {
    ctk::Polygon pol1 = CtkPolygonTest::p1;
    ctk::Polygon pol1s = pol1;

    pol1s.SelfShift(1);
    EXPECT_EQ(pol1.size(), pol1s.size());
    std::vector<cv::Point> datacv = pol1.GetCvData();
    std::vector<cv::Point> datascv = pol1s.GetCvData();

    std::vector<ctk::PointD> data = pol1.GetData();
    std::vector<ctk::PointD> datas = pol1s.GetData();
    for (int i = 0; i < pol1.size(); ++i) {
        if (i == 0) {
            EXPECT_EQ(datacv[i].x, datascv[pol1.size()-1].x);
            EXPECT_EQ(datacv[i].y, datascv[pol1.size()-1].y);
            EXPECT_DOUBLE_EQ(data[i].GetX(), datas[pol1.size()-1].GetX());
            EXPECT_DOUBLE_EQ(data[i].GetY(), datas[pol1.size()-1].GetY());
        }
        else {
            EXPECT_EQ(datacv[i].x, datascv[i-1].x);
            EXPECT_EQ(datacv[i].y, datascv[i-1].y);
            EXPECT_DOUBLE_EQ(data[i].GetX(), datas[i-1].GetX());
            EXPECT_DOUBLE_EQ(data[i].GetY(), datas[i-1].GetY());
        }
    }
}
#endif // TEST_POLYGON
