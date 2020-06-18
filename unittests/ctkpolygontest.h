#ifndef CTKPOLYGONTEST_H
#define CTKPOLYGONTEST_H

#include "gtest/gtest.h"

#include <vector>

#include "gtest/gtest.h"

#include "ctkpolygon.h"

class CtkPolygonTest: public ::testing::Test
{
public:

    void SetUp() override;
    ctk::PointD p1_v1,p1_v2,p1_v3,p1_v4;
    std::vector<ctk::PointD> p1;

    cv::Point p1cv_v1,p1cv_v2,p1cv_v3,p1cv_v4,p1cv_v5,p1cv_v6,p1cv_v7,p1cv_v8;
    std::vector<cv::Point> p1cv;

    ctk::PointD p2_v1,p2_v2,p2_v3,p2_v4,p2_v5,p2_v6,p2_v7,p2_v8,p2_v9,p2_v10;
    std::vector<ctk::PointD> p2;
    cv::Point p2cv_v1,p2cv_v2,p2cv_v3,p2cv_v4;
    std::vector<cv::Point> p2cv;

    ctk::Polygon Poly1;
    ctk::Polygon Poly1_cv;
    ctk::Polygon Poly2;
    ctk::Polygon Poly2_cv;

};


#endif // CTKPOLYGONTEST_H
