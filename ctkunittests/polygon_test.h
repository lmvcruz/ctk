#pragma once

#include "gtest/gtest.h"

#include <vector>

#include "ctk/geometry/polygon.h"

class CtkPolygonTest: public ::testing::Test {
public:
    const ctk::PointD p1_v1 = {0, 1};
    const ctk::PointD p1_v2 = {1, 1};
    const ctk::PointD p1_v3 = {1, 0};
    const ctk::PointD p1_v4 = {0, 0};
    const std::vector<ctk::PointD> p1 = {p1_v1, p1_v2, p1_v3, p1_v4};

    const cv::Point p1cv_v1 = {0, 1};
    const cv::Point p1cv_v2 = {1, 1};
    const cv::Point p1cv_v3 = {1, 0};
    const cv::Point p1cv_v4 = {0, 0};
    const std::vector<cv::Point> p1cv = {p1cv_v1,  p1cv_v2,p1cv_v3, p1cv_v4};

    const ctk::PointD p2_v1 = {2, 5};
    const ctk::PointD p2_v2 = {3, 5};
    const ctk::PointD p2_v3 = {4, 5};
    const ctk::PointD p2_v4 = {5, 5};
    const ctk::PointD p2_v5 = {5, 4};
    const ctk::PointD p2_v6 = {5, 3};
    const ctk::PointD p2_v7 = {5, 2};
    const ctk::PointD p2_v8 = {4, 2};
    const ctk::PointD p2_v9 = {3, 2};
    const ctk::PointD p2_v10 = {2, 2};

    const std::vector<ctk::PointD> p2 = {p2_v1, p2_v2, p2_v3, p2_v4, 
                                         p2_v5, p2_v6, p2_v7, p2_v8,
                                         p2_v9, p2_v10};

    const cv::Point p2cv_v1 = {2, 5};
    const cv::Point p2cv_v2 = {5, 5};
    const cv::Point p2cv_v3 = {5, 2};
    const cv::Point p2cv_v4 = {2, 2};
    const std::vector<cv::Point> p2cv = {p2cv_v1, p2cv_v2, p2cv_v3, p2cv_v4};
};
