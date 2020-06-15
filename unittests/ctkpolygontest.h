#ifndef CTKPOLYGONTEST_H
#define CTKPOLYGONTEST_H


#include <vector>

#include "gtest/gtest.h"

#include "ctkpolygon.h"

class CtkPolygonTest: public ::testing::Test
{
public:
    CtkPolygonTest();

    void SetUp() override;
    ctk::PointD p1_v1,p1_v2,p1_v3,p1_v4;
    std::vector<ctk::PointD> p1 = {p1_v1, p1_v2, p1_v3, p1_v4} ;

    cv::Point p1cv_v1,p1cv_v2,p1cv_v3,p1cv_v4;
    std::vector<cv::Point> p1cv = {p1cv_v1, p1cv_v2, p1cv_v3, p1cv_v4 };

    ctk::PointD p2_v1,p2_v2,p2_v3,p2_v4;
    std::vector<ctk::PointD> p2 = {p2_v1, p2_v2, p2_v3, p2_v4 };
    cv::Point p2cv_v1,p2cv_v2,p2cv_v3,p2cv_v4;
    std::vector<cv::Point> p2cv = {p2cv_v1, p2cv_v2, p2cv_v3, p2cv_v4 };

    ctk::Polygon Poly1;
    ctk::Polygon Poly1_cv;
    ctk::Polygon Poly2;
    ctk::Polygon Poly2_cv;


};

#endif // CTKPOLYGONTEST_H
